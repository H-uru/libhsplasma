#ifndef _PLRESMANAGER_H
#define _PLRESMANAGER_H

#include "../../CoreLib/hsRefCnt.h"
#include "../../DynLib/PlasmaVersions.h"
#include "../../NucleusLib/pnKeyedObject/plKey.h"
#include "../../NucleusLib/pnKeyedObject/hsKeyedObject.h"
#include "../../CoreLib/hsStream.h"
#include "plKeyCollector.h"

class plResManager : hsRefCnt {
protected:
    PlasmaVer ver;
    plKeyCollector keys;

private:
    plKey* readKeyBase(hsStream* S);
    void writeKeyBase(hsStream* S, plKey* key);

public:
    static plResManager* inst;

    plResManager(PlasmaVer pv = pvUnknown);
    virtual ~plResManager();

    virtual void setVer(PlasmaVer pv, bool mutate = false);
    PlasmaVer getVer();

    plKey* readKey(hsStream* S);
    void writeKey(hsStream* S, plKey* key);
    hsKeyedObject* getObject(plKey& key);
};

#endif

