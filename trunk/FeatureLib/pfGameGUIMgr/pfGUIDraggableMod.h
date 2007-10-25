#ifndef _PFGUIDRAGGABLEMOD_H
#define _PFGUIDRAGGABLEMOD_H

#include "pfGUIControlMod.h"

DllClass pfGUIDraggableMod : public pfGUIControlMod {
public:
    enum DraggableFlags {
        kReportDragging = kDerivedFlagsStart, kHideCursorWhileDragging,
        kAlwaysSnapBackToStart
    };

    enum ExtendedEvents { kDragging, kCancelled, kStartingDrag };

protected:
    hsPoint3 fDragOffset, fLastMousePt, fOrigCenter;
    bool fDragging;

public:
    pfGUIDraggableMod();
    virtual ~pfGUIDraggableMod();

    DECLARE_CREATABLE(pfGUIDraggableMod)
};

#endif
