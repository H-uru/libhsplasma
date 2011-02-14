/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _PLAVATARCLOTHING_H
#define _PLAVATARCLOTHING_H

#include "PRP/Object/plSynchedObject.h"

class PLASMA_DLL plClothingOutfit : public virtual plSynchedObject {
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


class PLASMA_DLL plClothingBase : public virtual hsKeyedObject {
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
