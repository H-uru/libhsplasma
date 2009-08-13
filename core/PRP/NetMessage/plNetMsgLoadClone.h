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
};

#endif
