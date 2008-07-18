#ifndef _PLMULTISTAGEBEHMOD_H
#define _PLMULTISTAGEBEHMOD_H

#include "PRP/Modifier/plModifier.h"
#include "plAnimStage.h"

DllClass plMultistageBehMod : public plSingleModifier {
protected:
    hsTArray<plAnimStage*> fStages;
    bool fFreezePhys, fSmartSeek, fReverseFBControlsOnRelease;
    hsTArray<plKey> fReceivers;

public:
    plMultistageBehMod();
    virtual ~plMultistageBehMod();

    DECLARE_CREATABLE(plMultistageBehMod)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
