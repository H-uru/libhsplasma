#ifndef _PLNETMSGLOADCLONE_H
#define _PLNETMSGLOADCLONE_H

#include "plNetMsgGameMessage.h"
#include "plNetMsgObject.h"

DllClass plNetMsgLoadClone : public plNetMsgGameMessage {
private:
    plNetMsgObjectHelper fObject;
    bool fIsPlayer, fIsLoading, fIsInitialState;

public:
    plNetMsgLoadClone();
    ~plNetMsgLoadClone();

    DECLARE_CREATABLE(plNetMsgLoadClone)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plNetMsgObjectHelper getObject() const;
    bool getIsPlayer() const;
    bool getIsLoading() const;
    bool getIsInitialState() const;

    void setObject(plNetMsgObjectHelper Object);
    void setIsPlayer(bool IsPlayer);
    void setIsLoading(bool IsLoading);
    void setIsInitialState(bool IsInitialState);
};

#endif
