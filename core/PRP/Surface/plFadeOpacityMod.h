#ifndef _PLFADEOPACITYMOD_H
#define _PLFADEOPACITYMOD_H

#include "PRP/Modifier/plModifier.h"

DllClass plFadeOpacityMod : public plSingleModifier {
    CREATABLE(plFadeOpacityMod, kFadeOpacityMod, plSingleModifier)

public:
    enum {
        kBoundsCenter = 0x1
    };

protected:
    float fFadeUp, fFadeDown;

public:
    plFadeOpacityMod();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    float getFadeUp() const { return fFadeUp; }
    float getFadeDown() const { return fFadeDown; }

    void setFadeUp(float fade) { fFadeUp = fade; }
    void setFadeDown(float fade) { fFadeDown = fade; }
};

#endif
