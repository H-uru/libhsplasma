#ifndef _PLQUATCHANNEL_H
#define _PLQUATCHANNEL_H

#include "plAGApplicator.h"
#include "PRP/Animation/plController.h"

/* Quat Channels */
DllClass plQuatChannel : public plAGChannel {
protected:
    hsQuat fResult;

public:
    plQuatChannel();
    virtual ~plQuatChannel();

    DECLARE_CREATABLE(plQuatChannel)
};

DllClass plQuatBlend : public plQuatChannel {
public:
    plQuatBlend();
    virtual ~plQuatBlend();

    DECLARE_CREATABLE(plQuatBlend)
};

DllClass plQuatConstant : public plQuatChannel {
public:
    plQuatConstant();
    virtual ~plQuatConstant();

    DECLARE_CREATABLE(plQuatConstant)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plQuatTimeScale : public plQuatChannel {
public:
    plQuatTimeScale();
    virtual ~plQuatTimeScale();

    DECLARE_CREATABLE(plQuatTimeScale)
};


/* Quat Channel Applicators */
DllClass plQuatChannelApplicator : public plAGApplicator {
public:
    plQuatChannelApplicator();
    virtual ~plQuatChannelApplicator();

    DECLARE_CREATABLE(plQuatChannelApplicator)
};

#endif
