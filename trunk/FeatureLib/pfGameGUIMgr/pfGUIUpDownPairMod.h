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
    virtual void IPrcWrite(pfPrcHelper* prc);
};

#endif
