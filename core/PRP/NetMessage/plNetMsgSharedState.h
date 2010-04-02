#ifndef _PLNETMSGSHAREDSTATE_H
#define _PLNETMSGSHAREDSTATE_H

#include "plNetMsgStreamedObject.h"
#include "plNetSharedState.h"

DllClass plNetMsgSharedState : public plNetMsgStreamedObject {
    CREATABLE(plNetMsgSharedState, kNetMsgSharedState, plNetMsgStreamedObject)

private:
    unsigned char fLockRequest;
    plNetSharedState fState;

public:
    plNetMsgSharedState();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

private:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plNetMsgTestAndSet : public plNetMsgSharedState {
    CREATABLE(plNetMsgTestAndSet, kNetMsgTestAndSet, plNetMsgSharedState)
};

#endif
