#ifndef _PLMATRIXCHANNEL_H
#define _PLMATRIXCHANNEL_H

#include "plAGApplicator.h"
#include "PubUtilLib/plInterp/plController.h"

/* Matrix Channels */
DllClass plMatrixChannel : public plAGChannel {
protected:
    hsMatrix44 fResult;
    hsAffineParts fAP;

public:
    plMatrixChannel();
    virtual ~plMatrixChannel();

    DECLARE_CREATABLE(plMatrixChannel)
};

DllClass plMatrixBlend : public plMatrixChannel {
public:
    plMatrixBlend();
    virtual ~plMatrixBlend();

    DECLARE_CREATABLE(plMatrixBlend)
};

DllClass plMatrixConstant : public plMatrixChannel {
public:
    plMatrixConstant();
    virtual ~plMatrixConstant();

    DECLARE_CREATABLE(plMatrixConstant)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plMatrixControllerCacheChannel : public plMatrixChannel {
public:
    plMatrixControllerCacheChannel();
    virtual ~plMatrixControllerCacheChannel();

    DECLARE_CREATABLE(plMatrixControllerCacheChannel)
};

DllClass plMatrixControllerChannel : public plMatrixChannel {
protected:
    plController* fController;

public:
    plMatrixControllerChannel();
    virtual ~plMatrixControllerChannel();

    DECLARE_CREATABLE(plMatrixControllerChannel)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plMatrixTimeScale : public plMatrixChannel {
public:
    plMatrixTimeScale();
    virtual ~plMatrixTimeScale();

    DECLARE_CREATABLE(plMatrixTimeScale)
};

DllClass plQuatPointCombine : public plMatrixChannel {
public:
    plQuatPointCombine();
    virtual ~plQuatPointCombine();

    DECLARE_CREATABLE(plQuatPointCombine)
};


/* Matrix Channel Applicators */
DllClass plMatrixChannelApplicator : public plAGApplicator {
public:
    plMatrixChannelApplicator();
    virtual ~plMatrixChannelApplicator();

    DECLARE_CREATABLE(plMatrixChannelApplicator)
};

DllClass plMatrixDelayedCorrectionApplicator : public plMatrixChannelApplicator {
public:
    plMatrixDelayedCorrectionApplicator();
    virtual ~plMatrixDelayedCorrectionApplicator();

    DECLARE_CREATABLE(plMatrixDelayedCorrectionApplicator)
};

DllClass plMatrixDifferenceApp : public plMatrixChannelApplicator {
public:
    plMatrixDifferenceApp();
    virtual ~plMatrixDifferenceApp();

    DECLARE_CREATABLE(plMatrixDifferenceApp)
};

#endif
