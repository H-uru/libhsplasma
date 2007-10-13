#ifndef _PFGUIDIALOGMOD_H
#define _PFGUIDIALOGMOD_H

#include "pfGUIControlMod.h"

DllClass pfGUIDialogMod : public plSingleModifier {
public:
    enum Flags { kModal, kDerivedFlagsStart };

protected:
    pfGUIDialogMod* fNext;
    pfGUIDialogMod* fPrev;
    unsigned int fTagID, fVersion;
    plKey fRenderMod;
    bool fEnabled;
    char fName[128];
    hsTArray<plKey> fControls;
    pfGUIControlMod* fControlOfInterest;
    pfGUIControlMod* fFocusCtrl;
    pfGUIControlMod* fMousedCtrl;
    pfGUIColorScheme* fColorScheme;
    pfGUIDialogProc* fHandler;
    plKey fProcReceiver;
    hsTArray<plKey> pfGUIListElement;
    int fDragMode, fDragReceptive;
    pfGUIControlMod* fDragTarget;
    pfGUIControlMod* fDragSource;
    plKey fSceneNode;

public:
    pfGUIDialogMod();
    virtual ~pfGUIDialogMod();

    DECLARE_CREATABLE(pfGUIDialogMod)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
