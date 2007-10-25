#ifndef _PFGUIDRAGBARCTRL_H
#define _PFGUIDRAGBARCTRL_H

#include "pfGUIControlMod.h"

DllClass pfGUIDragBarCtrl : public pfGUIControlMod {
protected:
    hsPoint3 fDragOffset;
    bool fDragging, fAnchored;

public:
    pfGUIDragBarCtrl();
    virtual ~pfGUIDragBarCtrl();

    DECLARE_CREATABLE(pfGUIDragBarCtrl)
};

#endif
