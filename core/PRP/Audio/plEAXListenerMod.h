#ifndef _PLEAXLISTENERMOD_H
#define _PLEAXLISTENERMOD_H

#include "PRP/Modifier/plModifier.h"
#include "3rdPartyLibs/AL/EFX-Util.h"

DllClass plEAXListenerMod : public plSingleModifier {
protected:
    plKey fSoftRegion;
    EAXREVERBPROPERTIES fListenerProps;
    bool fRegistered, fGetsMessages;

public:
    plEAXListenerMod();
    virtual ~plEAXListenerMod();

    DECLARE_CREATABLE(plEAXListenerMod)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
