#include "pfGUIClickMapCtrl.h"

pfGUIClickMapCtrl::pfGUIClickMapCtrl() {
    fFlags.setName(kReportDragging, "kReportDragging");
    fFlags.setName(kReportHovering, "kReportHovering");
}

IMPLEMENT_CREATABLE(pfGUIClickMapCtrl, kGUIClickMapCtrl, pfGUIControlMod)
