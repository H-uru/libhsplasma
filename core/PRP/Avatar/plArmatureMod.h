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

#ifndef _PLARMATUREMOD_H
#define _PLARMATUREMOD_H

#include "plAGMasterMod.h"
#include "plArmatureBrain.h"
#include "Math/hsGeometry3.h"

class HSPLASMA_EXPORT plArmatureModBase : public plAGMasterMod
{
    CREATABLE(plArmatureModBase, kArmatureModBase, plAGMasterMod)

protected:
    std::vector<plKey> fMeshKeys;
    std::vector<std::vector<plKey>> fUnusedBones;
    std::vector<plArmatureBrain*> fBrains;
    plKey fDetector;

public:
    plArmatureModBase() { }
    ~plArmatureModBase();

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    const std::vector<plKey>& getMeshes() const { return fMeshKeys; }
    std::vector<plKey>& getMeshes() { return fMeshKeys; }
    const std::vector<std::vector<plKey>>& getUnusedBones() const { return fUnusedBones; }
    std::vector<std::vector<plKey>>& getUnusedBones() { return fUnusedBones; }
    const std::vector<plArmatureBrain*>& getBrains() const { return fBrains; }
    std::vector<plArmatureBrain*>& getBrains() { return fBrains; }
    plKey getDetector() const { return fDetector; }

    void clearBrains();
    void setDetector(plKey detector) { fDetector = std::move(detector); }
};


class HSPLASMA_EXPORT plArmatureMod : public plArmatureModBase
{
    CREATABLE(plArmatureMod, kArmatureMod, plArmatureModBase)

public:
    enum
    {
        kBoneBaseMale, kBoneBaseFemale, kBoneBaseCritter, kBoneBaseActor,
        kMaxBoneBase
    };

    const char* kBoneNames[kMaxBoneBase];

protected:
    plKey fDefaultMesh;
    ST::string fRootName;
    plKey fClothingOutfit;
    int fBodyType;
    plKey fEffects;
    hsVector3 fMins, fMaxs;
    float fPhysHeight, fPhysWidth;
    ST::string fFootstepAge, fFootstepPage, fFootstepType;

public:
    plArmatureMod() : fBodyType(), fPhysHeight(), fPhysWidth() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    plKey getDefaultMesh() const { return fDefaultMesh; }
    const ST::string& getRootName() const { return fRootName; }
    plKey getClothingOutfit() const { return fClothingOutfit; }
    int getBodyType() const { return fBodyType; }
    plKey getEffects() const { return fEffects; }
    hsVector3 getMins() const { return fMins; }
    hsVector3 getMaxs() const { return fMaxs; }
    float getPhysHeight() const { return fPhysHeight; }
    float getPhysWidth() const { return fPhysWidth; }
    const ST::string& getFootstepAge() const { return fFootstepAge; }
    const ST::string& getFootstepPage() const { return fFootstepPage; }
    const ST::string& getFootstepType() const { return fFootstepType; }

    void setDefaultMesh(plKey defaultMesh) { fDefaultMesh = std::move(defaultMesh); }
    void setRootName(ST::string rootName) { fRootName = std::move(rootName); }
    void setClothingOutfit(plKey clothingOutfit) { fClothingOutfit = std::move(clothingOutfit); }
    void setBodyType(int bodyType) { fBodyType = bodyType; }
    void setEffects(plKey effects) { fEffects = std::move(effects); }
    void setMins(hsVector3 mins) { fMins = mins; }
    void setMaxs(hsVector3 maxs) { fMaxs = maxs; }
    void setPhysHeight(float physHeight) { fPhysHeight = physHeight; }
    void setPhysWidth(float physWidth) { fPhysWidth = physWidth; }
    void setFootstepAge(ST::string footstepAge) { fFootstepAge = std::move(footstepAge); }
    void setFootstepPage(ST::string footstepPage) { fFootstepPage = std::move(footstepPage); }
    void setFootstepType(ST::string footstepType) { fFootstepType = std::move(footstepType); }
};


class HSPLASMA_EXPORT plArmatureLODMod : public plArmatureMod
{
    CREATABLE(plArmatureLODMod, kArmatureLODMod, plArmatureMod)

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;
};

#endif
