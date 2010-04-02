#ifndef _PLQUATCHANNEL_H
#define _PLQUATCHANNEL_H

#include "plAGApplicator.h"
#include "PRP/Animation/plController.h"

/* Quat Channels */
DllClass plQuatChannel : public plAGChannel {
    CREATABLE(plQuatChannel, kQuatChannel, plAGChannel)

protected:
    hsQuat fResult;

public:
    hsQuat getResult() const { return fResult; }
    void setResult(const hsQuat& result) { fResult = result; }
};


DllClass plQuatBlend : public plQuatChannel {
    CREATABLE(plQuatBlend, kQuatBlend, plQuatChannel)
};


DllClass plQuatConstant : public plQuatChannel {
    CREATABLE(plQuatConstant, kQuatConstant, plQuatChannel)

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plQuatTimeScale : public plQuatChannel {
    CREATABLE(plQuatTimeScale, kQuatTimeScale, plQuatChannel)
};


/* Quat Channel Applicators */
DllClass plQuatChannelApplicator : public plAGApplicator {
    CREATABLE(plQuatChannelApplicator, kQuatChannelApplicator, plAGApplicator)
};

#endif
