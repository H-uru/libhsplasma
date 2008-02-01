#include "pfGUIDraggableMod.h"

pfGUIDraggableMod::pfGUIDraggableMod() : fDragging(false) {
    fFlags.setName(kReportDragging, "kReportDragging");
    fFlags.setName(kHideCursorWhileDragging, "kHideCursorWhileDragging");
    fFlags.setName(kAlwaysSnapBackToStart, "kAlwaysSnapBackToStart");
}

pfGUIDraggableMod::~pfGUIDraggableMod() { }

IMPLEMENT_CREATABLE(pfGUIDraggableMod, kGUIDraggableMod, pfGUIControlMod)
