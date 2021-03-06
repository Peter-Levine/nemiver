/* -*- Mode: C++; indent-tabs-mode:nil; c-basic-offset:4 -*- */

/*
 *This file is part of the Nemiver Project.
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
#ifndef __NMV_SQLITE_CNX_MGR_DRV_H__
#define __NMV_SQLITE_CNX_MGR_DRV_H__

#include "common/nmv-i-connection-manager-driver.h"
#include "common/nmv-i-connection-driver.h"

namespace nemiver {
namespace common {
namespace sqlite {

struct SqliteCnxMgrDrvPriv;
class SqliteCnxMgrDrv : public common::IConnectionManagerDriver {
    friend struct SqliteCnxMgrDrvPriv;
    friend class SqliteCnxMgrModule;
    struct SqliteCnxMgrDrvPriv *m_priv;

    //forbid copy
    SqliteCnxMgrDrv (const SqliteCnxMgrDrv&);
    SqliteCnxMgrDrv& operator= (const SqliteCnxMgrDrv&);

    SqliteCnxMgrDrv (DynamicModule *a_dynmod);
    virtual ~SqliteCnxMgrDrv ();

public:

    common::IConnectionDriverSafePtr connect_to_db
                                    (const common::DBDesc &a_desc,
                                     const common::UString &a_user,
                                     const common::UString &a_pass);
};//end SqliteCnxMgrDrv

}//end namespace sqlite
}//end namespace dbd
}//end namespace nemiver

#endif //__NMV_SQLITE_CNX_MGR_DRV_H__

