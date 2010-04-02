#ifndef _PLSHADOWCASTER_H
#define _PLSHADOWCASTER_H

#include "PRP/Modifier/plModifier.h"
#include "PRP/Geometry/plDrawableSpans.h"

DllClass plShadowCaster : public plMultiModifier {
    CREATABLE(plShadowCaster, kShadowCaster, plMultiModifier)

public:
    DllStruct DrawSpan {
    public:
        plDrawableSpans* fDraw;
        plSpan* fSpan;
        unsigned int fIndex;
    };

    enum {
        kNone = 0,
        kSelfShadow = 0x1,
        kPerspective = 0x2,
        kLimitRes = 0x4
    };

protected:
    unsigned char fCastFlags;
    float fBoost, fAttenScale, fBlurScale, fMaxOpacity;
    hsTArray<DrawSpan> fSpans;

public:
    plShadowCaster();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
