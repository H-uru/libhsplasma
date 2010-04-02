#ifndef _PFGUICHECKBOXCTRL_H
#define _PFGUICHECKBOXCTRL_H

#include "pfGUIControlMod.h"

DllClass pfGUICheckBoxCtrl : public pfGUIControlMod {
    CREATABLE(pfGUICheckBoxCtrl, kGUICheckBoxCtrl, pfGUIControlMod)

protected:
    hsTArray<plKey> fAnimKeys;
    plString fAnimName;
    bool fChecked;

public:
    pfGUICheckBoxCtrl();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const hsTArray<plKey>& getAnimKeys() const { return fAnimKeys; }
    hsTArray<plKey>& getAnimKeys() { return fAnimKeys; }
    void addAnimKey(plKey key) { fAnimKeys.append(key); }
    void delAnimKey(size_t idx) { fAnimKeys.remove(idx); }
    void clearAnimKeys() { fAnimKeys.clear(); }

    const plString& getAnimName() const { return fAnimName; }
    bool isChecked() const { return fChecked; }

    void setAnimName(const plString& name) { fAnimName = name; }
    void setChecked(bool checked) { fChecked = checked; }
};

#endif
