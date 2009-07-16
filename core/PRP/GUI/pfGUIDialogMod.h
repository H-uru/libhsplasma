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
    pfGUIColorScheme fColorScheme;
    plKey fProcReceiver, fSceneNode;

public:
    pfGUIDialogMod();
    virtual ~pfGUIDialogMod();

    DECLARE_CREATABLE(pfGUIDialogMod)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    size_t getNumControls() const;
    plKey getControl(size_t idx) const;
    void addControl(plKey ctrl);
    void delControl(size_t idx);
    void clearControls();

    unsigned int getTagID() const;
    unsigned int getVersion() const;
    plKey getRenderMod() const;
    plString getName() const;
    plKey getProcReceiver() const;
    plKey getSceneNode() const;

    void setTagID(unsigned int id);
    void setVersion(unsigned int version);
    void setRenderMod(plKey mod);
    void setName(const char* name);
    void setProcReceiver(plKey receiver);
    void setSceneNode(plKey node);

    pfGUIColorScheme& getColorScheme();
    const pfGUIColorScheme& getColorScheme() const;
};

#endif
