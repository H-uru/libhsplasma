#ifndef _PLPOSTEFFECTMOD_H
#define _PLPOSTEFFECTMOD_H

#include "plModifier.h"
#include "Math/hsMatrix44.h"

DllClass plPostEffectMod : public plSingleModifier {
public:
    enum plPostEffectModStates { kEnabled };

protected:
    hsBitVector fState;
    float fHither, fYon, fFovX, fFovY;
    plWeakKey fNodeKey;
    hsMatrix44 fDefaultW2C, fDefaultC2W;

public:
    plPostEffectMod();
    virtual ~plPostEffectMod();

    DECLARE_CREATABLE(plPostEffectMod)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
