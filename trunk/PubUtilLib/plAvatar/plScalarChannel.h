#ifndef _PLSCALARCHANNEL_H
#define _PLSCALARCHANNEL_H

#include "plAGApplicator.h"
#include "PubUtilLib/plInterp/plController.h"

/* Scalar Channels */
DllClass plScalarChannel : public plAGChannel {
protected:
    float fResult;

public:
    plScalarChannel();
    virtual ~plScalarChannel();

    DECLARE_CREATABLE(plScalarChannel)
};

DllClass plScalarBlend : public plScalarChannel {
public:
    plScalarBlend();
    virtual ~plScalarBlend();

    DECLARE_CREATABLE(plScalarBlend)
};

DllClass plScalarConstant : public plScalarChannel {
public:
    plScalarConstant();
    virtual ~plScalarConstant();

    DECLARE_CREATABLE(plScalarConstant)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

DllClass plScalarControllerCacheChannel : public plScalarChannel {
public:
    plScalarControllerCacheChannel();
    virtual ~plScalarControllerCacheChannel();

    DECLARE_CREATABLE(plScalarControllerCacheChannel)
};

DllClass plScalarControllerChannel : public plScalarChannel {
protected:
    plController* fController;

public:
    plScalarControllerChannel();
    virtual ~plScalarControllerChannel();

    DECLARE_CREATABLE(plScalarControllerChannel)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

DllClass plScalarTimeScale : public plScalarChannel {
public:
    plScalarTimeScale();
    virtual ~plScalarTimeScale();

    DECLARE_CREATABLE(plScalarTimeScale)
};

DllClass plScalarSDLChannel : public plScalarChannel {
public:
    plScalarSDLChannel();
    virtual ~plScalarSDLChannel();

    DECLARE_CREATABLE(plScalarSDLChannel)
};

DllClass plATCChannel : public plScalarChannel {
public:
    plATCChannel();
    virtual ~plATCChannel();

    DECLARE_CREATABLE(plATCChannel)
};


/* Scalar Channel Applicators */
DllClass plScalarChannelApplicator : public plAGApplicator {
public:
    plScalarChannelApplicator();
    virtual ~plScalarChannelApplicator();

    DECLARE_CREATABLE(plScalarChannelApplicator)
};

#endif
