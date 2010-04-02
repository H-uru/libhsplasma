#ifndef _PFGUIDIALOGMOD_H
#define _PFGUIDIALOGMOD_H

#include "pfGUIControlMod.h"

DllClass pfGUIDialogMod : public plSingleModifier {
    CREATABLE(pfGUIDialogMod, kGUIDialogMod, plSingleModifier)

public:
    enum Flags { kModal, kDerivedFlagsStart };

protected:
    unsigned int fTagID, fVersion;
    plKey fRenderMod;
    char fName[128];
    hsTArray<plKey> fControls;
    pfGUIColorScheme fColorScheme;
    plKey fProcReceiver, fSceneNode;

public:
    pfGUIDialogMod();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const hsTArray<plKey>& getControls() const { return fControls; }
    hsTArray<plKey>& getControls() { return fControls; }
    void addControl(plKey ctrl) { fControls.append(ctrl); }
    void delControl(size_t idx) { fControls.remove(idx); }
    void clearControls() { fControls.clear(); }

    unsigned int getTagID() const { return fTagID; }
    unsigned int getVersion() const { return fVersion; }
    plKey getRenderMod() const { return fRenderMod; }
    plString getName() const { return fName; }
    plKey getProcReceiver() const { return fProcReceiver; }
    plKey getSceneNode() const { return fSceneNode; }

    void setTagID(unsigned int id) { fTagID = id; }
    void setVersion(unsigned int version) { fVersion = version; }
    void setRenderMod(plKey mod) { fRenderMod = mod; }
    void setName(const char* name) { strncpy(fName, name, 128); }
    void setProcReceiver(plKey receiver) { fProcReceiver = receiver; }
    void setSceneNode(plKey node) { fSceneNode = node; }

    const pfGUIColorScheme& getColorScheme() const { return fColorScheme; }
    pfGUIColorScheme& getColorScheme() { return fColorScheme; }
};

#endif
