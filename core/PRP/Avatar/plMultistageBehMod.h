#ifndef _PLMULTISTAGEBEHMOD_H
#define _PLMULTISTAGEBEHMOD_H

#include "PRP/Modifier/plModifier.h"
#include "plAnimStage.h"

DllClass plMultistageBehMod : public plSingleModifier {
protected:
    hsTArray<plAnimStage*> fStages;
    bool fFreezePhys, fSmartSeek, fReverseFBControlsOnRelease;
    hsTArray<plKey> fReceivers;

public:
    plMultistageBehMod();
    virtual ~plMultistageBehMod();

    DECLARE_CREATABLE(plMultistageBehMod)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    size_t getNumStages() const;
    plAnimStage* getStage(size_t idx) const;
    void addStage(plAnimStage* stage);
    void delStage(size_t idx);
    void clearStages();

    size_t getNumReceivers() const;
    plKey getReceiver(size_t idx) const;
    void addReceiver(plKey receiver);
    void delReceiver(size_t idx);
    void clearReceivers();

    bool getFreezePhys() const;
    bool getSmartSeek() const;
    bool getReverseFBControlsOnRelease() const;

    void setFreezePhys(bool freeze);
    void setSmartSeek(bool seek);
    void setReverseFBControlsOnRelease(bool release);
};

#endif
