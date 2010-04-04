#ifndef _PLNETMSGSDLSTATE_H
#define _PLNETMSGSDLSTATE_H

#include "plNetMsgStreamedObject.h"
#include "SDL/plSDLMgr.h"

DllClass plNetMsgSDLState : public plNetMsgStreamedObject {
    CREATABLE(plNetMsgSDLState, kNetMsgSDLState, plNetMsgStreamedObject)

private:
    bool fIsInitialState, fPersistOnServer, fIsAvatarState;
    // The stream is an SDL blob that will need to be parsed from
    // an SDL Manager with the correct descriptors loaded
    plStateDescriptor* fDescriptor;

public:
    plNetMsgSDLState();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

    bool findDescriptor(plSDLMgr* sdl);
    plStateDescriptor* getDescriptor() const { return fDescriptor; }

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    bool isInitialState() const { return fIsInitialState; }
    bool getPersistOnServer() const { return fPersistOnServer; }
    bool isAvatarState() const { return fIsAvatarState; }

    void setInitialState(bool initialState) { fIsInitialState = initialState; }
    void setPersistOnServer(bool persist) { fPersistOnServer = persist; }
    void setIsAvatarState(bool avState) { fIsAvatarState = avState; }
};


DllClass plNetMsgSDLStateBCast : public plNetMsgSDLState {
    CREATABLE(plNetMsgSDLStateBCast, kNetMsgSDLStateBCast, plNetMsgSDLState)
};

#endif
