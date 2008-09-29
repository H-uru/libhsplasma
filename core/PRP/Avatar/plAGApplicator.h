#ifndef _PLAGAPPLICATOR_H
#define _PLAGAPPLICATOR_H

#include "plAGChannel.h"

DllClass plAGApplicator : public plCreatable {
protected:
    plAGChannel* fChannel;
    bool fEnabled;
    plString fChannelName;

public:
    plAGApplicator();
    virtual ~plAGApplicator();

    DECLARE_CREATABLE(plAGApplicator)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plAGChannel* getChannel() const;
    void setChannel(plAGChannel*);
};

DllClass plSoundVolumeApplicator : public plAGApplicator {
protected:
    unsigned int fIndex;

public:
    plSoundVolumeApplicator();
    virtual ~plSoundVolumeApplicator();

    DECLARE_CREATABLE(plSoundVolumeApplicator)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plLightAmbientApplicator : public plAGApplicator {
public:
    plLightAmbientApplicator();
    virtual ~plLightAmbientApplicator();

    DECLARE_CREATABLE(plLightAmbientApplicator)
};

DllClass plLightDiffuseApplicator : public plAGApplicator {
public:
    plLightDiffuseApplicator();
    virtual ~plLightDiffuseApplicator();

    DECLARE_CREATABLE(plLightDiffuseApplicator)
};

DllClass plLightSpecularApplicator : public plAGApplicator {
public:
    plLightSpecularApplicator();
    virtual ~plLightSpecularApplicator();

    DECLARE_CREATABLE(plLightSpecularApplicator)
};

DllClass plOmniApplicator : public plAGApplicator {
public:
    plOmniApplicator();
    virtual ~plOmniApplicator();

    DECLARE_CREATABLE(plOmniApplicator)
};

DllClass plOmniCutoffApplicator : public plAGApplicator {
public:
    plOmniCutoffApplicator();
    virtual ~plOmniCutoffApplicator();

    DECLARE_CREATABLE(plOmniCutoffApplicator)
};

DllClass plOmniSqApplicator : public plAGApplicator {
public:
    plOmniSqApplicator();
    virtual ~plOmniSqApplicator();

    DECLARE_CREATABLE(plOmniSqApplicator)
};

DllClass plSpotInnerApplicator : public plAGApplicator {
public:
    plSpotInnerApplicator();
    virtual ~plSpotInnerApplicator();

    DECLARE_CREATABLE(plSpotInnerApplicator)
};

DllClass plSpotOuterApplicator : public plAGApplicator {
public:
    plSpotOuterApplicator();
    virtual ~plSpotOuterApplicator();

    DECLARE_CREATABLE(plSpotOuterApplicator)
};

#endif
