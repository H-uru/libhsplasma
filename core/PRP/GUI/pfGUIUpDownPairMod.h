#ifndef _PFGUIUPDOWNPAIRMOD_H
#define _PFGUIUPDOWNPAIRMOD_H

#include "pfGUIValueCtrl.h"

DllClass pfGUIUpDownPairMod : public pfGUIValueCtrl {
protected:
    plKey fUpControl, fDownControl;

public:
    pfGUIUpDownPairMod();
    virtual ~pfGUIUpDownPairMod();

    DECLARE_CREATABLE(pfGUIUpDownPairMod)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plKey getUpControl() const;
    plKey getDownControl() const;

    void setUpControl(plKey ctrl);
    void setDownControl(plKey ctrl);
};

#endif
