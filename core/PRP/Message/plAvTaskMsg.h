#ifndef _PLAVTASKMSG_H
#define _PLAVTASKMSG_H

#include "plAvatarMsg.h"
#include "PRP/Avatar/plAvTask.h"

DllClass plAvTaskMsg : public plAvatarMsg {
private:
    plAvTask* fTask;

public:
    plAvTaskMsg();
    virtual ~plAvTaskMsg();

    DECLARE_CREATABLE(plAvTaskMsg)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plAvTask* getTask() const;
    void setTask(plAvTask* task);
};

DllClass plAvPushBrainMsg : public plAvTaskMsg {
private:
    plArmatureBrain* fBrain;

public:
    plAvPushBrainMsg();
    virtual ~plAvPushBrainMsg();

    DECLARE_CREATABLE(plAvPushBrainMsg)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plArmatureBrain* getBrain() const;
    void setBrain(plArmatureBrain* brain);
};

DllClass plAvPopBrainMsg : public plAvTaskMsg {
public:
    plAvPopBrainMsg();
    virtual ~plAvPopBrainMsg();

    DECLARE_CREATABLE(plAvPopBrainMsg)
};

#endif
