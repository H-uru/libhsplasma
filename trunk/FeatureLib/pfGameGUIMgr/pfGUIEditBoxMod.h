#ifndef _PFGUIEDITBOXMOD_H
#define _PFGUIEDITBOXMOD_H

#include "pfGUIControlMod.h"
#include "DynLib/Platform.h"

DllClass pfGUIEditBoxMod : public pfGUIControlMod {
public:
    enum {
        kShift = 0x1,
        kCtrl = 0x2
    };

    enum ExtendedEvents { kValueChanging };

public:
    pfGUIEditBoxMod();
    virtual ~pfGUIEditBoxMod();

    DECLARE_CREATABLE(pfGUIEditBoxMod)
};

#endif
