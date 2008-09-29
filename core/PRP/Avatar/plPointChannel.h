#ifndef _PLPOINTCHANNEL_H
#define _PLPOINTCHANNEL_H

#include "plAGApplicator.h"
#include "PRP/Animation/plController.h"

/* Point Channels */
DllClass plPointChannel : public plAGChannel {
protected:
    hsVector3 fResult;

public:
    plPointChannel();
    virtual ~plPointChannel();

    DECLARE_CREATABLE(plPointChannel)
};

DllClass plPointBlend : public plPointChannel {
public:
    plPointBlend();
    virtual ~plPointBlend();

    DECLARE_CREATABLE(plPointBlend)
};

DllClass plPointConstant : public plPointChannel {
public:
    plPointConstant();
    virtual ~plPointConstant();

    DECLARE_CREATABLE(plPointConstant)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plPointControllerCacheChannel : public plPointChannel {
public:
    plPointControllerCacheChannel();
    virtual ~plPointControllerCacheChannel();

    DECLARE_CREATABLE(plPointControllerCacheChannel)
};

DllClass plPointControllerChannel : public plPointChannel {
protected:
    plController* fController;

public:
    plPointControllerChannel();
    virtual ~plPointControllerChannel();

    DECLARE_CREATABLE(plPointControllerChannel)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plPointTimeScale : public plPointChannel {
public:
    plPointTimeScale();
    virtual ~plPointTimeScale();

    DECLARE_CREATABLE(plPointTimeScale)
};


/* Point Channel Applicators */
DllClass plPointChannelApplicator : public plAGApplicator {
public:
    plPointChannelApplicator();
    virtual ~plPointChannelApplicator();

    DECLARE_CREATABLE(plPointChannelApplicator)
};

#endif
