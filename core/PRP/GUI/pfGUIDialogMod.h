#ifndef _PFGUIDIALOGMOD_H
#define _PFGUIDIALOGMOD_H

#include "pfGUIControlMod.h"

DllClass pfGUIDialogMod : public plSingleModifier {
public:
    enum Flags { kModal, kDerivedFlagsStart };

protected:
    unsigned int fTagID, fVersion;
    plKey fRenderMod;
    char fName[128];
    hsTArray<plKey> fControls;
    pfGUIColorScheme* fColorScheme;
    plKey fProcReceiver;
    hsTArray<plKey> pfGUIListElement;
    plKey fSceneNode;

public:
    pfGUIDialogMod();
    virtual ~pfGUIDialogMod();

    DECLARE_CREATABLE(pfGUIDialogMod)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
