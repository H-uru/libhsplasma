#ifndef _PLLOADAVATARMSG_H
#define _PLLOADAVATARMSG_H

#include "plLoadCloneMsg.h"
#include "PRP/Avatar/plAvTask.h"

DllClass plLoadAvatarMsg : public plLoadCloneMsg {
    CREATABLE(plLoadAvatarMsg, kLoadAvatarMsg, plLoadCloneMsg)

protected:
    bool fIsPlayer;
    plKey fSpawnPoint;
    plAvTask* fInitialTask;
    plString fUserStr;

public:
    plLoadAvatarMsg();
    virtual ~plLoadAvatarMsg();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    bool getIsPlayer() const { return fIsPlayer; }
    plKey getSpawnPoint() const { return fSpawnPoint; }
    plAvTask* getInitialTask() const { return fInitialTask; }
    plString getUserStr() const { return fUserStr; }

    void setIsPlayer(bool isPlayer) { fIsPlayer = isPlayer; }
    void setSpawnPoint(plKey spawnPoint) { fSpawnPoint = spawnPoint; }
    void setUserStr(plString userStr) { fUserStr = userStr; }

    void setInitialTask(plAvTask* InitialTask);
};

#endif
