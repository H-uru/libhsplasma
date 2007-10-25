#ifndef _PFGUICLICKMAPCTRL_H
#define _PFGUICLICKMAPCTRL_H

#include "pfGUIControlMod.h"

DllClass pfGUIClickMapCtrl : public pfGUIControlMod {
public:
    enum ClickMapFlags { kReportDragging = kDerivedFlagsStart, kReportHovering };
    enum ExtendedEvents { kMouseDragged, kMouseHovered };

protected:
    hsPoint3 fLastMousePt, fLastMouseUpPt, fLastMouseDragPt;
    bool fTracking;
    int fCustomCursor;

public:
    pfGUIClickMapCtrl();
    virtual ~pfGUIClickMapCtrl();

    DECLARE_CREATABLE(pfGUIClickMapCtrl)
};

#endif
