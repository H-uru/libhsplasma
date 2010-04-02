#ifndef _PLMATRIXCHANNEL_H
#define _PLMATRIXCHANNEL_H

#include "plAGApplicator.h"
#include "PRP/Animation/plController.h"

/* Matrix Channels */
DllClass plMatrixChannel : public plAGChannel {
    CREATABLE(plMatrixChannel, kMatrixChannel, plAGChannel)

protected:
    hsAffineParts fAP;

public:
    hsAffineParts getAffine() const { return fAP; }
    void setAffine(const hsAffineParts& ap) { fAP = ap; }
};


DllClass plMatrixBlend : public plMatrixChannel {
    CREATABLE(plMatrixBlend, kMatrixBlend, plMatrixChannel)
};


DllClass plMatrixConstant : public plMatrixChannel {
    CREATABLE(plMatrixConstant, kMatrixConstant, plMatrixChannel)

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plMatrixControllerCacheChannel : public plMatrixChannel {
    CREATABLE(plMatrixControllerCacheChannel, kMatrixControllerCacheChannel,
              plMatrixChannel)
};


DllClass plMatrixControllerChannel : public plMatrixChannel {
    CREATABLE(plMatrixControllerChannel, kMatrixControllerChannel,
              plMatrixChannel)

protected:
    plController* fController;

public:
    plMatrixControllerChannel();
    virtual ~plMatrixControllerChannel();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plController* getController() const { return fController; }
    void setController(plController* controller);
};


DllClass plMatrixTimeScale : public plMatrixChannel {
    CREATABLE(plMatrixTimeScale, kMatrixTimeScale, plMatrixChannel)
};

DllClass plQuatPointCombine : public plMatrixChannel {
    CREATABLE(plQuatPointCombine, kQuatPointCombine, plMatrixChannel)
};


/* Matrix Channel Applicators */
DllClass plMatrixChannelApplicator : public plAGApplicator {
    CREATABLE(plMatrixChannelApplicator, kMatrixChannelApplicator,
              plAGApplicator)
};

DllClass plMatrixDelayedCorrectionApplicator : public plMatrixChannelApplicator {
    CREATABLE(plMatrixDelayedCorrectionApplicator,
              kMatrixDelayedCorrectionApplicator,
              plMatrixChannelApplicator)
};

DllClass plMatrixDifferenceApp : public plMatrixChannelApplicator {
    CREATABLE(plMatrixDifferenceApp, kMatrixDifferenceApp,
              plMatrixChannelApplicator)
};

DllClass plRelativeMatrixChannelApplicator : public plAGApplicator {
    CREATABLE(plRelativeMatrixChannelApplicator,
              kRelativeMatrixChannelApplicator,
              plAGApplicator)
};

#endif
