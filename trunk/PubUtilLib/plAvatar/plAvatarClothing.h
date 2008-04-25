#ifndef _PLAVATARCLOTHING_H
#define _PLAVATARCLOTHING_H

#include "NucleusLib/pnNetCommon/plSynchedObject.h"

DllClass plClothingOutfit : public plSynchedObject {
public:
    enum {
        kClothingGroupMale, kClothingGroupFemale, kClothingGroupNoOptions,
        kMaxClothingGroup
    };

    enum {
        kTypePants, kTypeShirt, kTypeLeftHand, kTypeRightHand, kTypeFace,
        kTypeHair, kTypeLeftFoot, kTypeRightFoot, kTypeAccessory,
        kMaxClothingType
    };

    static const char* const GroupNames[];
    static const char* const TypeNames[];

protected:
    unsigned char fGroup;
    plKey fBase, fTargetTexture, fMaterial;

public:
    plClothingOutfit();
    virtual ~plClothingOutfit();

    DECLARE_CREATABLE(plClothingOutfit)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

DllClass plClothingBase : public hsKeyedObject {
protected:
    plString fName, fLayoutName;
    plKey fBaseTexture;

public:
    plClothingBase();
    virtual ~plClothingBase();

    DECLARE_CREATABLE(plClothingBase)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

#endif
