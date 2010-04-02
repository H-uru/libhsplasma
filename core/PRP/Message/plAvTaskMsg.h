#ifndef _PLAVTASKMSG_H
#define _PLAVTASKMSG_H

#include "plAvatarMsg.h"
#include "PRP/Avatar/plAvTask.h"

DllClass plAvTaskMsg : public plAvatarMsg {
    CREATABLE(plAvTaskMsg, kAvTaskMsg, plAvatarMsg)

private:
    plAvTask* fTask;

public:
    plAvTaskMsg();
    virtual ~plAvTaskMsg();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plAvTask* getTask() const { return fTask; }
    void setTask(plAvTask* task);
};


DllClass plAvPushBrainMsg : public plAvTaskMsg {
    CREATABLE(plAvPushBrainMsg, kAvPushBrainMsg, plAvTaskMsg)

private:
    plArmatureBrain* fBrain;

public:
    plAvPushBrainMsg();
    virtual ~plAvPushBrainMsg();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plArmatureBrain* getBrain() const { return fBrain; }
    void setBrain(plArmatureBrain* brain);
};


DllClass plAvPopBrainMsg : public plAvTaskMsg {
    CREATABLE(plAvPopBrainMsg, kAvPopBrainMsg, plAvTaskMsg)
};

#endif
