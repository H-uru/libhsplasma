#ifndef _PLARMATUREMOD_H
#define _PLARMATUREMOD_H

#include "plAGMasterMod.h"
#include "plArmatureBrain.h"
#include "Math/hsGeometry3.h"

DllClass plArmatureModBase : public plAGMasterMod {
    CREATABLE(plArmatureModBase, kArmatureModBase, plAGMasterMod)

protected:
    hsTArray<plKey> fMeshKeys;
    hsTArray<hsTArray<plKey> > fUnusedBones;
    hsTArray<plArmatureBrain*> fBrains;

public:
    plArmatureModBase() { }
    virtual ~plArmatureModBase();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    void clearBrains();
};


DllClass plArmatureMod : public plArmatureModBase {
    CREATABLE(plArmatureMod, kArmatureMod, plArmatureModBase)

public:
    enum {
        kBoneBaseMale, kBoneBaseFemale, kBoneBaseCritter, kBoneBaseActor,
        kMaxBoneBase
    };

    const char* kBoneNames[kMaxBoneBase];

protected:
    plString fRootName;
    plKey fClothingOutfit;
    int fBodyType;
    plKey fEffects;
    hsVector3 fMins, fMaxs;
    float fPhysHeight, fPhysWidth;
    plString fFootstepAge, fFootstepPage, fFootstepType;

public:
    plArmatureMod();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plArmatureLODMod : public plArmatureMod {
    CREATABLE(plArmatureLODMod, kArmatureLODMod, plArmatureMod)

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
