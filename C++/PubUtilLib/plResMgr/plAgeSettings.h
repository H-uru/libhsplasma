#ifndef _PLAGESETTINGS_H
#define _PLAGESETTINGS_H

#include "../../DynLib/PlasmaVersions.h"
#include "../../DynLib/PageID.h"

struct plAgeSettings {
    PageID pageID;
    short pageType;
    char* ageName;
    char* pageName;
    PlasmaVer ver;
    int nObjects;
};

#endif

