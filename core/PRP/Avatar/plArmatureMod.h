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

class PLASMA_DLL plArmatureModBase : public plAGMasterMod
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
    void clearBrains();
};


class PLASMA_DLL plArmatureMod : public plArmatureModBase
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
};


class PLASMA_DLL plArmatureLODMod : public plArmatureMod
{
    CREATABLE(plArmatureLODMod, kArmatureLODMod, plArmatureMod)

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;
};

#endif
