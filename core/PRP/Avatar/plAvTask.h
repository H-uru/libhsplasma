#ifndef _PLAVTASK_H
#define _PLAVTASK_H

#include "PRP/plCreatable.h"
#include "plArmatureBrain.h"

DllClass plAvTask : public plCreatable {
public:
    plAvTask();
    virtual ~plAvTask();

    DECLARE_CREATABLE(plAvTask)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plAvAnimTask : public plAvTask {
private:
    plString fAnimName;
    float fInitialBlend, fTargetBlend;
    float fFadeSpeed, fSetTime;
    bool fStart, fLoop, fAttach;

public:
    plAvAnimTask();
    virtual ~plAvAnimTask();

    DECLARE_CREATABLE(plAvAnimTask)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plAvOneShotTask : public plAvTask {
public:
    plAvOneShotTask();
    virtual ~plAvOneShotTask();

    DECLARE_CREATABLE(plAvOneShotTask)
};

DllClass plAvOneShotLinkTask : public plAvOneShotTask {
private:
    plString fAnimName, fMarkerName;

public:
    plAvOneShotLinkTask();
    virtual ~plAvOneShotLinkTask();

    DECLARE_CREATABLE(plAvOneShotLinkTask)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plAvSeekTask : public plAvTask {
public:
    plAvSeekTask();
    virtual ~plAvSeekTask();

    DECLARE_CREATABLE(plAvSeekTask)
};

DllClass plAvTaskBrain : public plAvTask {
private:
    plArmatureBrain* fBrain;

public:
    plAvTaskBrain();
    virtual ~plAvTaskBrain();

    DECLARE_CREATABLE(plAvTaskBrain)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plArmatureBrain* getBrain() const;
    void setBrain(plArmatureBrain* brain);
};

// Yay redundancy
DllClass plAvTaskSeek : public plAvTask {
public:
    plAvTaskSeek();
    virtual ~plAvTaskSeek();

    DECLARE_CREATABLE(plAvTaskSeek)
};

#endif
