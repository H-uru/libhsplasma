#ifndef _PLNETMSGLOADCLONE_H
#define _PLNETMSGLOADCLONE_H

#include "plNetMsgGameMessage.h"
#include "plNetMsgObject.h"

DllClass plNetMsgLoadClone : public plNetMsgGameMessage {
    CREATABLE(plNetMsgLoadClone, kNetMsgLoadClone, plNetMsgGameMessage)

private:
    plNetMsgObjectHelper fObject;
    bool fIsPlayer, fIsLoading, fIsInitialState;

public:
    plNetMsgLoadClone();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const plNetMsgObjectHelper& getObject() const { return fObject; }
    plNetMsgObjectHelper& getObject() { return fObject; }

    bool isPlayer() const { return fIsPlayer; }
    bool isLoading() const { return fIsLoading; }
    bool isInitialState() const { return fIsInitialState; }

    void setIsPlayer(bool isPlayer) { fIsPlayer = isPlayer; }
    void setIsLoading(bool isLoading) { fIsLoading = isLoading; }
    void setIsInitialState(bool isInitialState) { fIsInitialState = isInitialState; }
};

#endif
