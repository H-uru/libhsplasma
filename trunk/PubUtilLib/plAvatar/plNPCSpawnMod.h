#ifndef _PLNPCSPAWNMOD_H
#define _PLNPCSPAWNMOD_H

#include "../../NucleusLib/pnModifier/plModifier.h"
#include "../../NucleusLib/pnMessage/plNotifyMsg.h"
#include "../plResMgr/plResManager.h"

DllClass plNPCSpawnMod : public plSingleModifier {
protected:
    plString fModelName;
    plString fAccountName;
    bool fAutoSpawn;
    plKey fSpawnedKey;
    plNotifyMsg* fNotify;

public:
    plNPCSpawnMod();
    virtual ~plNPCSpawnMod();

    DECLARE_CREATABLE(plNPCSpawnMod)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
