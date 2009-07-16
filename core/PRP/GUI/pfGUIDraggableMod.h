#ifndef _PFGUIDRAGGABLEMOD_H
#define _PFGUIDRAGGABLEMOD_H

#include "pfGUIControlMod.h"

DllClass pfGUIDraggableMod : public pfGUIControlMod {
public:
    enum DraggableFlags {
        kReportDragging = kDerivedFlagsStart, kHideCursorWhileDragging,
        kAlwaysSnapBackToStart
    };

public:
    pfGUIDraggableMod();
    DECLARE_CREATABLE(pfGUIDraggableMod)
};

#endif
