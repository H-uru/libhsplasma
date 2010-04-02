#ifndef _PFGUIUPDOWNPAIRMOD_H
#define _PFGUIUPDOWNPAIRMOD_H

#include "pfGUIValueCtrl.h"

DllClass pfGUIUpDownPairMod : public pfGUIValueCtrl {
    CREATABLE(pfGUIUpDownPairMod, kGUIUpDownPairMod, pfGUIValueCtrl)

protected:
    plKey fUpControl, fDownControl;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plKey getUpControl() const { return fUpControl; }
    plKey getDownControl() const { return fDownControl; }

    void setUpControl(plKey ctrl) { fUpControl = ctrl; }
    void setDownControl(plKey ctrl) { fDownControl = ctrl; }
};

#endif
