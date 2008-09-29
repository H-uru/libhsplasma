#ifndef _PFGUIMULTILINEEDITCTRL_H
#define _PFGUIMULTILINEEDITCTRL_H

#include "pfGUIControlMod.h"

DllClass pfGUIMultiLineEditCtrl : public pfGUIControlMod {
public:
    enum Direction {
        kLineStart, kLineEnd, kBufferStart, kBufferEnd, kOneBack, kOneForward,
        kOneWordBack, kOneWordForward, kOneLineUp, kOneLineDown, kPageUp,
        kPageDown
    };

    enum flagsSet {
        kFontFaceSet = 0x1,
        kFontColorSet = 0x2,
        kFontSizeSet = 0x4,
        kFontStyleSet = 0x8
    };

    enum ExtendedEvents { kValueChanging, kScrollPosChanged, kKeyPressedEvent };

protected:
    plKey fScrollCtrl;

public:
    pfGUIMultiLineEditCtrl();
    virtual ~pfGUIMultiLineEditCtrl();

    DECLARE_CREATABLE(pfGUIMultiLineEditCtrl)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
