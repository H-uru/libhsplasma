#ifndef _PLMULTISTAGEBEHMOD_H
#define _PLMULTISTAGEBEHMOD_H

#include "PRP/Modifier/plModifier.h"
#include "plAnimStage.h"

DllClass plMultistageBehMod : public plSingleModifier {
    CREATABLE(plMultistageBehMod, kMultistageBehMod, plSingleModifier)

protected:
    hsTArray<plAnimStage*> fStages;
    bool fFreezePhys, fSmartSeek, fReverseFBControlsOnRelease;
    hsTArray<plKey> fReceivers;

public:
    plMultistageBehMod();
    virtual ~plMultistageBehMod();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const hsTArray<plAnimStage*>& getStages() const { return fStages; }
    hsTArray<plAnimStage*>& getStages() { return fStages; }
    void addStage(plAnimStage* stage) { fStages.append(stage); }
    void delStage(size_t idx);
    void clearStages();

    const hsTArray<plKey>& getReceivers() const { return fReceivers; }
    hsTArray<plKey>& getReceivers() { return fReceivers; }
    void addReceiver(plKey receiver) { fReceivers.append(receiver); }
    void delReceiver(size_t idx) { fReceivers.remove(idx); }
    void clearReceivers() { fReceivers.clear(); }

    bool getFreezePhys() const { return fFreezePhys; }
    bool getSmartSeek() const { return fSmartSeek; }
    bool getReverseFBControlsOnRelease() const { return fReverseFBControlsOnRelease; }

    void setFreezePhys(bool freeze) { fFreezePhys = freeze; }
    void setSmartSeek(bool seek) { fSmartSeek = seek; }
    void setReverseFBControlsOnRelease(bool reverse) { fReverseFBControlsOnRelease = reverse; }
};

#endif
