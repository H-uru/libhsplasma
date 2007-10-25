#ifndef _PFGUIEDITBOXMOD_H
#define _PFGUIEDITBOXMOD_H

#include "pfGUIControlMod.h"
#include "../../DynLib/Platform.h"

DllClass pfGUIEditBoxMod : public pfGUIControlMod {
public:
    enum {
        kShift = 0x1,
        kCtrl = 0x2
    };

    enum ExtendedEvents { kValueChanging };

protected:
    plWString fBuffer;
    unsigned int fCursorPos;
    int fScrollPos;
    bool fIgnoreNextKey, fEscapedFlag;
    bool fFirstHalfExitKeyPushed, fSpecialCaptureKeyEventMode;
    plKeyDef fSavedKey;
    unsigned char fSavedModifiers;
    wchar_t fLastDeadKey;
    //wchar_t fDeadKeyConverter[256][256];  // 128KB array...

public:
    pfGUIEditBoxMod();
    virtual ~pfGUIEditBoxMod();

    DECLARE_CREATABLE(pfGUIEditBoxMod)
};

#endif
