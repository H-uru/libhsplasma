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
    unsigned int nObjects;
    unsigned int loadFlags;
};

struct plAgeSettings {
    unsigned int startDateTime, dayLength, maxCapacity, lingerTime;
    signed int sequencePrefix;
    unsigned int releaseVersion;
    std::vector<plPageSettings*> pages;
};

#endif

