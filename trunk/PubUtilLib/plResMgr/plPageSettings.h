#ifndef _PLPAGESETTINGS_H
#define _PLPAGESETTINGS_H

#include "../../DynLib/PlasmaVersions.h"
#include "../../DynLib/PageID.h"

struct plPageSettings {
    PageID pageID;
    short pageType;
    char* ageName;
    char* pageName;
    PlasmaVer ver;
    int nObjects;
};

#endif

