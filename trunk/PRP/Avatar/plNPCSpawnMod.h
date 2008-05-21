#ifndef _PLNPCSPAWNMOD_H
#define _PLNPCSPAWNMOD_H

#include "NucleusLib/pnModifier/plModifier.h"
#include "NucleusLib/pnMessage/plNotifyMsg.h"

DllClass plNPCSpawnMod : public plSingleModifier {
protected:
    plString fModelName, fAccountName;
    bool fAutoSpawn;
    plNotifyMsg* fNotify;

public:
    plNPCSpawnMod();
    virtual ~plNPCSpawnMod();

    DECLARE_CREATABLE(plNPCSpawnMod)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
