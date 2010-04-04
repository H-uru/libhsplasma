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

public:
    const plNetSharedState& getState() const { return fState; }
    plNetSharedState& getState() { return fState; }

    unsigned char getLockRequest() const { return fLockRequest; }
    void setLockRequest(unsigned char req) { fLockRequest = req; }
};


DllClass plNetMsgTestAndSet : public plNetMsgSharedState {
    CREATABLE(plNetMsgTestAndSet, kNetMsgTestAndSet, plNetMsgSharedState)
};

#endif
