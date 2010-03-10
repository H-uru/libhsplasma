#ifndef _PLLOADAVATARMSG_H
#define _PLLOADAVATARMSG_H

#include "plLoadCloneMsg.h"
#include "PRP/Avatar/plAvTask.h"

DllClass plLoadAvatarMsg : public plLoadCloneMsg {
protected:
    bool fIsPlayer;
    plKey fSpawnPoint;
    plAvTask* fInitialTask;
    plString fUserStr;

public:
    plLoadAvatarMsg();
    virtual ~plLoadAvatarMsg();

    DECLARE_CREATABLE(plLoadAvatarMsg)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plAvTask* getInitialTask() const;
    void setInitialTask(plAvTask* task);
};

#endif
