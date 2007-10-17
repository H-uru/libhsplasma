#ifndef _PFGUISKIN_H
#define _PFGUISKIN_H

#include "../../NucleusLib/pnKeyedObject/hsKeyedObject.h"
#include "../../PubUtilLib/plResMgr/plResManager.h"

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
        void empty();
    };

protected:
    plKey fTexture;
    pfSRect fElements[14];
    unsigned short fItemMargin, fBorderMargin;

public:
    pfGUISkin();
    virtual ~pfGUISkin();

    DECLARE_CREATABLE(pfGUISkin)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
