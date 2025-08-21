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

class HSPLASMA_EXPORT plClothingOutfit : public plSynchedObject
{
    CREATABLE(plClothingOutfit, kClothingOutfit, plSynchedObject)

public:
    enum
    {
        kClothingGroupMale, kClothingGroupFemale, kClothingGroupNoOptions,
        kMaxClothingGroup
    };

    enum
    {
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
    plClothingOutfit() : fGroup(kClothingGroupNoOptions) { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    unsigned char getGroup() const { return fGroup; }
    plKey getBase() const { return fBase; }
    plKey getTargetTexture() const { return fTargetTexture; }
    plKey getMaterial() const { return fMaterial; }

    void setGroup(unsigned char group) { fGroup = group; }
    void setBase(plKey base) { fBase = std::move(base); }
    void setTargetTexture(plKey targetTexture) { fTargetTexture = std::move(targetTexture); }
    void setMaterial(plKey material) { fMaterial = std::move(material); }
};


class HSPLASMA_EXPORT plClothingBase : public hsKeyedObject
{
    CREATABLE(plClothingBase, kClothingBase, hsKeyedObject)

protected:
    ST::string fName, fLayoutName;
    plKey fBaseTexture;

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    const ST::string& getName() const { return fName; }
    const ST::string& getLayoutName() const { return fLayoutName; }
    plKey getBaseTexture() const { return fBaseTexture; }

    void setName(ST::string name) { fName = std::move(name); }
    void setLayoutName(ST::string layoutName) { fLayoutName = std::move(layoutName); }
    void setBaseTexture(plKey baseTexture) { fBaseTexture = std::move(baseTexture); }
};

#endif
