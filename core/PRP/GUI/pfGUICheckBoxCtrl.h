#ifndef _PFGUICHECKBOXCTRL_H
#define _PFGUICHECKBOXCTRL_H

#include "pfGUIControlMod.h"

DllClass pfGUICheckBoxCtrl : public pfGUIControlMod {
protected:
    hsTArray<plKey> fAnimKeys;
    plString fAnimName;
    bool fChecked;

public:
    pfGUICheckBoxCtrl();
    virtual ~pfGUICheckBoxCtrl();

    DECLARE_CREATABLE(pfGUICheckBoxCtrl)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    size_t getNumAnimKeys() const;
    plKey getAnimKey(size_t idx) const;
    void addAnimKey(plKey key);
    void delAnimKey(size_t idx);
    void clearAnimKeys();

    const plString& getAnimName() const;
    bool getChecked() const;

    void setAnimName(const plString& name);
    void setChecked(bool checked);
};

#endif
