#ifndef _PLNETMSGSDLSTATE_H
#define _PLNETMSGSDLSTATE_H

#include "plNetMsgStreamedObject.h"
#include "SDL/plStateDataRecord.h"

DllClass plNetMsgSDLState : public plNetMsgStreamedObject {
private:
    bool fIsInitialState, fPersistOnServer, fIsAvatarState;
    plString fDescName;
    int fDescVersion;
    // The stream is an SDL blob that will need to be parsed from
    // an SDL Manager with the correct descriptors loaded
    plStateDataRecord fRecord; //That would be this record...

public:
    plNetMsgSDLState();
    ~plNetMsgSDLState();

    DECLARE_CREATABLE(plNetMsgSDLState)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plNetMsgSDLStateBCast : public plNetMsgSDLState {
public:
    DECLARE_CREATABLE(plNetMsgSDLStateBCast)
};

#endif
