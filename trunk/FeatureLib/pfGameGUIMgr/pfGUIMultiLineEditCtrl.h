#ifndef _PFGUIMULTILINEEDITCTRL_H
#define _PFGUIMULTILINEEDITCTRL_H

#include "pfGUIControlMod.h"

DllClass pfMLScrollProc : public pfGUICtrlProcObject {
protected:
    class pfGUIMultiLineEditCtrl* fParent;

public:
    pfMLScrollProc(class pfGUIMultiLineEditCtrl* parent);
    virtual void DoSomething(pfGUIControlMod* ctrl);
};

DllClass pfGUIMultiLineEditProc {
    //TODO: Stuff
};

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
    hsTArray<wchar_t> fBuffer;
    hsTArray<int> fLineStarts;
    unsigned short fLineHeight, fCurrCursorX, fCurrCursorY;
    int fCursorPos, fLastCursorLine;
    bool fIgnoreNextKey, fReadyToRender;
    hsBounds3Ext fLastP2PArea;
    signed char fLockCount;
    unsigned char fCalcedFontSize, fLastKeyModifiers;
    wchar_t fLastKeyPressed, fLastDeadKey;
    //wchar_t fDeadKeyConverter[256][256];
    plKey fScrollCtrl;
    pfMLScrollProc* fScrollProc;
    int fScrollPos, fBufferLimit;
    pfGUIMultiLineEditCtrl* fNextCtrl;
    pfGUIMultiLineEditCtrl* fPrevCtrl;
    pfGUIMultiLineEditProc* fEventProc;
    plString fFontFace;
    hsColorRGBA fFontColor;
    unsigned char fFontSize, fFontStyle, fFontFlagsSet;
    int fTopMargin, fLeftMargin, fBottomMargin, fRightMargin;

public:
    pfGUIMultiLineEditCtrl();
    virtual ~pfGUIMultiLineEditCtrl();

    DECLARE_CREATABLE(pfGUIMultiLineEditCtrl)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
