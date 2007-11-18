//Author: Dodji Seketeli
/*
 *This file is part of the Nemiver project
 *
 *Nemiver is free software; you can redistribute
 *it and/or modify it under the terms of
 *the GNU General Public License as published by the
 *Free Software Foundation; either version 2,
 *or (at your option) any later version.
 *
 *Nemiver is distributed in the hope that it will
 *be useful, but WITHOUT ANY WARRANTY;
 *without even the implied warranty of
 *MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *See the GNU General Public License for more details.
 *
 *You should have received a copy of the
 *GNU General Public License along with Nemiver;
 *see the file COPYING.
 *If not, write to the Free Software Foundation,
 *Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 *
 *See COPYRIGHT file copyright information.
 */
#ifndef __NMV_VAR_WALKER_LIST_H__
#define __NMV_I_VAR_WALKER_LIST_H__

#include "nmv-i-var-walker.h"

NEMIVER_BEGIN_NAMESPACE (nemiver)

using nemiver::common::ObjectRef ;
using nemiver::common::ObjectUnref ;
using nemiver::common::SafePtr ;
using nemiver::common::DynModIface ;
using nemiver::common::DynModIfaceSafePtr ;

class IVarWalkerList;
typedef SafePtr<IVarWalkerList, ObjectRef, ObjectUnref> IVarWalkerListSafePtr ;

class NEMIVER_API IVarWalkerList : public DynModIface {

    //non copyable
    IVarWalkerList () ;
    IVarWalkerList (const IVarWalkerList&) ;

protected:
    IVarWalkerList (DynamicModule *a_dynmod) :
        DynModIface (a_dynmod)
    {
    }

public:

    /// \name signals
    ///@{
    virtual sigc::signal<void,
                         const IVarWalkerSafePtr&>& variable_visited_signal () const = 0;
    ///@}

    virtual void initialize (IDebuggerSafePtr &a_debugger) = 0 ;

    virtual void append_variable (const IDebugger::VariableSafePtr a_var) = 0;

    virtual void append_variables
                            (const list<IDebugger::VariableSafePtr> a_vars) = 0;

    virtual void remove_variables () = 0;

    virtual void do_walk_variables () = 0 ;
};//end class IVarWalkerList

NEMIVER_END_NAMESPACE (nemiver)

#endif //__NMV_I_VAR_WALKER_LIST_H__

