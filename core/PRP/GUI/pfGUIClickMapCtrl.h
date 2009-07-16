#ifndef _PFGUICLICKMAPCTRL_H
#define _PFGUICLICKMAPCTRL_H

#include "pfGUIControlMod.h"

DllClass pfGUIClickMapCtrl : public pfGUIControlMod {
public:
    enum ClickMapFlags { kReportDragging = kDerivedFlagsStart, kReportHovering };

public:
    pfGUIClickMapCtrl();
    DECLARE_CREATABLE(pfGUIClickMapCtrl)
};

#endif
