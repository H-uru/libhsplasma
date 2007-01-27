#include "pnSingletons.h"
hsResMgr * hsgResMgr::fResMgr;





//this is line 8
plDispatchBase * plgDispatch::Dispatch(void)
{
	return hsgResMgr::fResMgr->Dispatch();
}
