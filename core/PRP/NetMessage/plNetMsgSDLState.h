#ifndef _PLNETMSGSDLSTATE_H
#define _PLNETMSGSDLSTATE_H

#include "plNetMsgStreamedObject.h"
#include "SDL/plSDLMgr.h"

DllClass plNetMsgSDLState : public plNetMsgStreamedObject {
private:
    bool fIsInitialState, fPersistOnServer, fIsAvatarState;
    // The stream is an SDL blob that will need to be parsed from
    // an SDL Manager with the correct descriptors loaded
    plStateDescriptor* fDescriptor;

public:
    plNetMsgSDLState();
    ~plNetMsgSDLState();

    DECLARE_CREATABLE(plNetMsgSDLState)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    
    void findDescriptor(plSDLMgr* sdl);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plNetMsgSDLStateBCast : public plNetMsgSDLState {
public:
    DECLARE_CREATABLE(plNetMsgSDLStateBCast)
};

#endif
