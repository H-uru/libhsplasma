#ifndef _PLFADEOPACITYMOD_H
#define _PLFADEOPACITYMOD_H

#include "PRP/Modifier/plModifier.h"

DllClass plFadeOpacityMod : public plSingleModifier {
public:
    enum {
        kBoundsCenter = 0x1
    };

protected:
    float fFadeUp, fFadeDown;

public:
    plFadeOpacityMod();
    virtual ~plFadeOpacityMod();

    DECLARE_CREATABLE(plFadeOpacityMod)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
