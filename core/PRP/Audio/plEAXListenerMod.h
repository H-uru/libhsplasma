#ifndef _PLEAXLISTENERMOD_H
#define _PLEAXLISTENERMOD_H

#include "PRP/Modifier/plModifier.h"
#include "3rdPartyLibs/AL/EFX-Util.h"

DllClass plEAXListenerMod : public plSingleModifier {
    CREATABLE(plEAXListenerMod, kEAXListenerMod, plSingleModifier)

protected:
    plKey fSoftRegion;
    EAXREVERBPROPERTIES fListenerProps;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
