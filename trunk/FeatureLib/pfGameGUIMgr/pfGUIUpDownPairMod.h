#ifndef _PFGUIUPDOWNPAIRMOD_H
#define _PFGUIUPDOWNPAIRMOD_H

#include "pfGUIValueCtrl.h"

DllClass pfUpDownBtnProc : public pfGUICtrlProcObject {
protected:
    class pfGUIButtonMod* fUp;
    class pfGUIButtonMod* fDown;
    class pfGUIUpDownPairMod* fParent;

public:
    pfUpDownBtnProc(class pfGUIButtonMod* up, class pfGUIButtonMod* fDown,
                    class pfGUIUpDownPairMod* fParent);
    virtual void DoSomething(pfGUIControlMod* ctrl);
};

DllClass pfGUIUpDownPairMod : public pfGUIValueCtrl {
protected:
    plKey fUpControl, fDownControl;
    pfUpDownBtnProc* fButtonProc;

public:
    pfGUIUpDownPairMod();
    virtual ~pfGUIUpDownPairMod();

    DECLARE_CREATABLE(pfGUIUpDownPairMod)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
