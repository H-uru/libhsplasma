#include "pfGUIClickMapCtrl.h"

pfGUIClickMapCtrl::pfGUIClickMapCtrl() {
    fFlags.setName(kReportDragging, "kReportDragging");
    fFlags.setName(kReportHovering, "kReportHovering");
}

pfGUIClickMapCtrl::~pfGUIClickMapCtrl() { }

IMPLEMENT_CREATABLE(pfGUIClickMapCtrl, kGUIClickMapCtrl, pfGUIControlMod)
