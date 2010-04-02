#ifndef _PFGUIMISC_H
#define _PFGUIMISC_H

#include "pfGUIControlMod.h"

DllClass pfGUIClickMapCtrl : public pfGUIControlMod {
    CREATABLE(pfGUIClickMapCtrl, kGUIClickMapCtrl, pfGUIControlMod)

public:
    enum ClickMapFlags { kReportDragging = kDerivedFlagsStart, kReportHovering };

public:
    inline pfGUIClickMapCtrl();
};


DllClass pfGUIDragBarCtrl : public pfGUIControlMod {
    CREATABLE(pfGUIDragBarCtrl, kGUIDragBarCtrl, pfGUIControlMod)
};


DllClass pfGUIDraggableMod : public pfGUIControlMod {
    CREATABLE(pfGUIDraggableMod, kGUIDraggableMod, pfGUIControlMod)

public:
    enum DraggableFlags {
        kReportDragging = kDerivedFlagsStart, kHideCursorWhileDragging,
        kAlwaysSnapBackToStart
    };

public:
    inline pfGUIDraggableMod();
};


DllClass pfGUIEditBoxMod : public pfGUIControlMod {
    CREATABLE(pfGUIEditBoxMod, kGUIEditBoxMod, pfGUIControlMod)
};


/* pfGUIClickMapCtrl */
pfGUIClickMapCtrl::pfGUIClickMapCtrl() {
    fFlags.setName(kReportDragging, "kReportDragging");
    fFlags.setName(kReportHovering, "kReportHovering");
}


/* pfGUIDraggableMod */
pfGUIDraggableMod::pfGUIDraggableMod() {
    fFlags.setName(kReportDragging, "kReportDragging");
    fFlags.setName(kHideCursorWhileDragging, "kHideCursorWhileDragging");
    fFlags.setName(kAlwaysSnapBackToStart, "kAlwaysSnapBackToStart");
}

#endif
