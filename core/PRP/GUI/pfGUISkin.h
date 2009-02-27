#ifndef _PFGUISKIN_H
#define _PFGUISKIN_H

#include "PRP/KeyedObject/hsKeyedObject.h"

DllClass pfGUISkin : public hsKeyedObject {
public:
    enum Elements {
        kUpLeftCorner, kTopSpan, kUpRightCorner, kRightSpan, kLowerRightCorner,
        kBottomSpan, kLowerLeftCorner, kLeftSpan, kMiddleFill, kSelectedFill,
        kSubMenuArrow, kSelectedSubMenuArrow, kTreeButtonClosed,
        kTreeButtonOpen, kNumElements
    };

    DllStruct pfSRect {
        unsigned short fX, fY, fWidth, fHeight;

        pfSRect();
        void read(hsStream* S);
        void write(hsStream* S);
        void prcWrite(pfPrcHelper* prc);
        void prcParse(const pfPrcTag* tag);
        void clear();
    };

protected:
    plKey fTexture;
    pfSRect fElements[kNumElements];
    unsigned short fItemMargin, fBorderMargin;

public:
    pfGUISkin();
    virtual ~pfGUISkin();

    DECLARE_CREATABLE(pfGUISkin)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
