#ifndef _PLAVATARCLOTHING_H
#define _PLAVATARCLOTHING_H

#include "PRP/Object/plSynchedObject.h"

DllClass plClothingOutfit : public plSynchedObject {
    CREATABLE(plClothingOutfit, kClothingOutfit, plSynchedObject)

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

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plClothingBase : public hsKeyedObject {
    CREATABLE(plClothingBase, kClothingBase, hsKeyedObject)

protected:
    plString fName, fLayoutName;
    plKey fBaseTexture;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
