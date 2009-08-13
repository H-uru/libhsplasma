#ifndef _PLNETMSGSHAREDSTATE_H
#define _PLNETMSGSHAREDSTATE_H

#include "plNetMsgStreamedObject.h"
#include "plNetSharedState.h"

DllClass plNetMsgSharedState : public plNetMsgStreamedObject {
private:
    unsigned char fLockRequest;
    plNetSharedState fState;

public:
    plNetMsgSharedState();
    ~plNetMsgSharedState();

    DECLARE_CREATABLE(plNetMsgSharedState)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

private:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plNetMsgTestAndSet : public plNetMsgSharedState {
public:
    DECLARE_CREATABLE(plNetMsgTestAndSet)
};

#endif
