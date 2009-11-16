/**********************************************************\ 
Original Author: Richard Bateman (taxilian)

Created:    Sept 17, 2009
License:    Eclipse Public License - Version 1.0
            http://www.eclipse.org/legal/epl-v10.html

Copyright 2009 Richard Bateman, Firebreath development team
\**********************************************************/

// dllmain.h : Declaration of module class.

#include "FireBreathWin_i.h"
#include "TypeIDMap.h"
#include "resource.h"

#ifndef H_AXMAIN
#define H_AXMAIN

class CFireBreathWinModule : public CAtlDllModuleT< CFireBreathWinModule >
{
public :
    CFireBreathWinModule();
    DECLARE_LIBID(LIBID_FireBreathWinLib)
    DECLARE_REGISTRY_APPID_RESOURCEID(IDR_FIREBREATHWIN, "{B415CD14-B45D-4BCA-B552-B06175C38606}")
};

extern class CFireBreathWinModule _AtlModule;

extern FB::TypeIDMap<DISPID> AxIdMap;

#endif H_AXMAIN