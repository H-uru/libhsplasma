#ifndef _PLSCALARCHANNEL_H
#define _PLSCALARCHANNEL_H

#include "plAGApplicator.h"
#include "PRP/Animation/plController.h"

/* Scalar Channels */
DllClass plScalarChannel : public plAGChannel {
    CREATABLE(plScalarChannel, kScalarChannel, plAGChannel)

protected:
    float fResult;

public:
    float getResult() const { return fResult; }
    void setResult(float result) { fResult = result; }
};


DllClass plScalarBlend : public plScalarChannel {
    CREATABLE(plScalarBlend, kScalarBlend, plScalarChannel)
};


DllClass plScalarConstant : public plScalarChannel {
    CREATABLE(plScalarConstant, kScalarConstant, plScalarChannel)

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plScalarControllerCacheChannel : public plScalarChannel {
    CREATABLE(plScalarControllerCacheChannel, kScalarControllerCacheChannel,
              plScalarChannel)
};


DllClass plScalarControllerChannel : public plScalarChannel {
    CREATABLE(plScalarControllerChannel, kScalarControllerChannel,
              plScalarChannel)

protected:
    plController* fController;

public:
    plScalarControllerChannel();
    virtual ~plScalarControllerChannel();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plController* getController() const { return fController; }
    void setController(plController* controller);
};


DllClass plScalarTimeScale : public plScalarChannel {
    CREATABLE(plScalarTimeScale, kScalarTimeScale, plScalarChannel)
};

DllClass plScalarSDLChannel : public plScalarChannel {
    CREATABLE(plScalarSDLChannel, kScalarSDLChannel, plScalarChannel)
};

DllClass plATCChannel : public plScalarChannel {
    CREATABLE(plATCChannel, kATCChannel, plScalarChannel)
};


/* Scalar Channel Applicators */
DllClass plScalarChannelApplicator : public plAGApplicator {
    CREATABLE(plScalarChannelApplicator, kScalarChannelApplicator,
              plAGApplicator)
};

#endif
