#ifndef _PLRESMANAGER_H
#define _PLRESMANAGER_H

#include "../../CoreLib/hsRefCnt.h"
#include "../../DynLib/PlasmaVersions.h"
#include "../../DynLib/PageID.h"
#include "../../NucleusLib/pnKeyedObject/plKey.h"
#include "../../NucleusLib/pnKeyedObject/hsKeyedObject.h"
#include "../../CoreLib/hsStream.h"
#include "../../CoreLib/hsTArray.hpp"
#include "plKeyCollector.h"
#include "plAgeSettings.h"

class plResManager : hsRefCnt {
protected:
    PlasmaVer ver;

public:
    plKeyCollector keys;
    std::map<PageID, plAgeSettings*, PageComparator> ages;

private:
    plKey* readKeyBase(hsStream* S);
    void writeKeyBase(hsStream* S, plKey* key);
    void ReadKeyring(hsStream* S, PageID& pid);
    unsigned int ReadObjects(hsStream* S, PageID& pid);

public:
    static plResManager* inst;

    plResManager(PlasmaVer pv = pvUnknown);
    virtual ~plResManager();

    virtual void setVer(PlasmaVer pv, bool mutate = false);
    PlasmaVer getVer();

    plKey* readKey(hsStream* S);
    void writeKey(hsStream* S, plKey* key);
    hsKeyedObject* getObject(plKey& key);

    plAgeSettings* ReadPage(const char* filename);
    void WritePage(const char* filename);
};

#endif

