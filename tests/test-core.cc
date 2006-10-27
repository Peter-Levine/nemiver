#include <iostream>
#include <glibmm.h>
#include "nmv-i-debugger.h"
#include "nmv-initializer.h"
#include "nmv-safe-ptr-utils.h"
#include "nmv-dynamic-module.h"

using namespace nemiver;
using namespace nemiver::common ;

Glib::RefPtr<Glib::MainLoop> loop =
    Glib::MainLoop::create (Glib::MainContext::get_default ()) ;
static int gv_cur_frame=-1 ;

void
display_help ()
{
    std::cout << "runtestcore <prog-file> <core-file>\n" ;
}

void
on_engine_died_signal ()
{
    std::cout << "engine died\n" ;
    loop->quit () ;
}

void
on_stopped_signal (const UString &a_reason,
                   bool a_has_frame,
                   const IDebugger::Frame &a_frame,
                   int a_thread_id)
{
    std::cout << "stopped, reason: " << a_reason << " " ;
    if (a_has_frame) {
        std::cout << "in frame: " << a_frame.function () ;
    }
    std::cout << "thread-id: '" << a_thread_id << "'\n" ;
}
void
on_current_frame_signal (const IDebugger::Frame &a_frame)
{
    gv_cur_frame = a_frame.level ();
}

void
on_frames_listed_signal (const std::vector<IDebugger::Frame> &a_frames)
{
    std::cout << "frame stack list: \n" ;
    vector<IDebugger::Frame>::size_type i = 0 ;
    for (i = 0 ; i < a_frames.size () ; ++i) {
        std::cout << a_frames[i].function () << "() ";
        if ((int) i == gv_cur_frame) {
            std::cout << "<---" ;
        }
        std::cout << "\n" ;
    }
    gv_cur_frame = -1 ;
    std::cout << "end of frame stack list\n" ;
    loop->quit () ;

}

void
on_frames_params_listed_signal
    (const std::map< int, std::list<IDebugger::VariableSafePtr> >& a_frame_params)
{
    if (a_frame_params.empty ()) {}
}

void
on_program_finished_signal ()
{
    std::cout << "program finished" ;
    loop->quit () ;
}

void
on_console_message_signal (const UString &a_msg)
{
    cout << "(gdb) " << a_msg << "\n";
}

void
on_error_message_signal (const UString &a_msg)
{
    cout << "(gdb error) " << a_msg << "\n";
}

int
main (int a_argc, char *a_argv[])
{
    if (a_argc < 3) {
        display_help () ;
        return -1 ;
    }
    try {

        Initializer::do_init () ;

        THROW_IF_FAIL (loop) ;

        DynamicModuleManager module_manager ;
        IDebuggerSafePtr debugger =
                    module_manager.load<IDebugger> ("gdbengine") ;

        debugger->set_event_loop_context (loop->get_context ()) ;

        //*********************************************
        //<connect to the events emited by the debugger>
        //*********************************************
        debugger->engine_died_signal ().connect
            (sigc::ptr_fun (&on_engine_died_signal)) ;

        debugger->program_finished_signal ().connect
            (sigc::ptr_fun (&on_program_finished_signal)) ;

        debugger->stopped_signal ().connect
            (sigc::ptr_fun (&on_stopped_signal)) ;

        debugger->current_frame_signal ().connect
            (sigc::ptr_fun (&on_current_frame_signal)) ;

        debugger->frames_listed_signal ().connect
            (sigc::ptr_fun (&on_frames_listed_signal)) ;

        debugger->frames_params_listed_signal ().connect
            (sigc::ptr_fun (&on_frames_params_listed_signal)) ;

        debugger->console_message_signal ().connect
            (sigc::ptr_fun (&on_console_message_signal)) ;

        debugger->log_message_signal ().connect
            (sigc::ptr_fun (&on_error_message_signal)) ;
        //*********************************************
        //</connect to the events emited by the debugger>
        //*********************************************

        debugger->load_core_file (a_argv[1], a_argv[2]) ;
        debugger->list_frames () ;
        loop->run () ;
    } catch (Glib::Exception &e) {
        LOG_ERROR ("Got error: " << e.what ()) ;
        return -1 ;
    } catch (exception &e) {
        LOG_ERROR ("got error: " << e.what ()) ;
        return -1 ;
    } catch (...) {
        LOG_ERROR ("got an unkown error\n") ;
    }
    return 0 ;
}
