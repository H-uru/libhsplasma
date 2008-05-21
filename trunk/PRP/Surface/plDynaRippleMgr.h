#ifndef _PLDYNARIPPLEMGR_H
#define _PLDYNARIPPLEMGR_H

#include "plDynaDecalMgr.h"
#include "PubUtilLib/plInterp/plAnimPath.h"

DllClass plDynaRippleMgr : public plDynaDecalMgr {
protected:
    hsVector3 fInitUVW, fFinalUVW;

public:
    plDynaRippleMgr();
    virtual ~plDynaRippleMgr();

    DECLARE_CREATABLE(plDynaRippleMgr)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plDynaRippleVSMgr : public plDynaRippleMgr {
protected:
    plKey fWaveSetBase;

public:
    plDynaRippleVSMgr();
    virtual ~plDynaRippleVSMgr();

    DECLARE_CREATABLE(plDynaRippleVSMgr)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plDynaTorpedoMgr : public plDynaRippleMgr {
public:
    plDynaTorpedoMgr();
    virtual ~plDynaTorpedoMgr();

    DECLARE_CREATABLE(plDynaTorpedoMgr)
};

DllClass plDynaTorpedoVSMgr : public plDynaTorpedoMgr {
protected:
    plKey fWaveSetBase;

public:
    plDynaTorpedoVSMgr();
    virtual ~plDynaTorpedoVSMgr();

    DECLARE_CREATABLE(plDynaTorpedoVSMgr)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plDynaPuddleMgr : public plDynaRippleMgr {
public:
    plDynaPuddleMgr();
    virtual ~plDynaPuddleMgr();

    DECLARE_CREATABLE(plDynaPuddleMgr)
};

DllClass plDynaWakeMgr : public plDynaRippleMgr {
protected:
    hsVector3 fDefaultDir;
    plAnimPath* fAnimPath;
    float fAnimWgt, fVelWgt;

public:
    plDynaWakeMgr();
    virtual ~plDynaWakeMgr();

    DECLARE_CREATABLE(plDynaWakeMgr)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
