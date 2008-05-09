#ifndef _PFGUICHECKBOXCTRL_H
#define _PFGUICHECKBOXCTRL_H

#include "pfGUIControlMod.h"

DllClass pfGUICheckBoxCtrl : public pfGUIControlMod {
public:
    enum SoundEvents { kMouseDown, kMouseUp, kMouseOver, kMouseOff };

protected:
    hsTArray<plKey> fAnimKeys;
    plString fAnimName;
    bool fChecked;
    int fPlaySound;

public:
    pfGUICheckBoxCtrl();
    virtual ~pfGUICheckBoxCtrl();

    DECLARE_CREATABLE(pfGUICheckBoxCtrl)

    void setChecked(bool checked);

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
