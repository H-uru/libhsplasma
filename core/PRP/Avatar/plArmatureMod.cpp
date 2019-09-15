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

#include "plArmatureMod.h"

/* plArmatureModBase */
plArmatureModBase::~plArmatureModBase()
{
    for (auto brain = fBrains.begin(); brain != fBrains.end(); ++brain)
        delete *brain;
}

void plArmatureModBase::read(hsStream* S, plResManager* mgr)
{
    plAGMasterMod::read(S, mgr);

    fMeshKeys.resize(S->readInt());
    fUnusedBones.resize(fMeshKeys.size());
    for (size_t i=0; i<fMeshKeys.size(); i++) {
        fMeshKeys[i] = mgr->readKey(S);
        fUnusedBones[i].resize(S->readInt());
        for (size_t j=0; j<fUnusedBones[i].size(); j++)
            fUnusedBones[i][j] = mgr->readKey(S);
    }

    clearBrains();
    fBrains.resize(S->readInt());
    for (size_t i=0; i<fBrains.size(); i++)
        fBrains[i] = mgr->ReadCreatableC<plArmatureBrain>(S);

    fDetector = mgr->readKey(S);
}

void plArmatureModBase::write(hsStream* S, plResManager* mgr)
{
    plAGMasterMod::write(S, mgr);

    S->writeInt(fMeshKeys.size());
    for (size_t i=0; i<fMeshKeys.size(); i++) {
        mgr->writeKey(S, fMeshKeys[i]);
        S->writeInt(fUnusedBones[i].size());
        for (size_t j=0; j<fUnusedBones[i].size(); j++)
            mgr->writeKey(S, fUnusedBones[i][j]);
    }

    S->writeInt(fBrains.size());
    for (size_t i=0; i<fBrains.size(); i++)
        mgr->WriteCreatable(S, fBrains[i]);

    mgr->writeKey(S, fDetector);
}

void plArmatureModBase::IPrcWrite(pfPrcHelper* prc)
{
    plAGMasterMod::IPrcWrite(prc);

    prc->writeSimpleTag("Meshes");
    for (size_t i=0; i<fMeshKeys.size(); i++) {
        prc->writeSimpleTag("Mesh");
        plResManager::PrcWriteKey(prc, fMeshKeys[i]);
        prc->writeSimpleTag("UnusedBones");
        for (size_t j=0; j<fUnusedBones[i].size(); j++)
            plResManager::PrcWriteKey(prc, fUnusedBones[i][j]);
        prc->closeTag(); // UnusedBones
        prc->closeTag(); // Mesh
    }
    prc->closeTag();

    prc->writeSimpleTag("Brains");
    for (size_t i=0; i<fBrains.size(); i++)
        fBrains[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Detector");
    plResManager::PrcWriteKey(prc, fDetector);
    prc->closeTag();
}

void plArmatureModBase::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Meshes") {
        fMeshKeys.resize(tag->countChildren());
        fUnusedBones.resize(fMeshKeys.size());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fMeshKeys.size(); i++) {
            if (child->getName() != "Mesh")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());

            const pfPrcTag* subchild = child->getFirstChild();
            while (subchild) {
                if (subchild->getName() == "plKey") {
                    fMeshKeys[i] = mgr->prcParseKey(subchild);
                } else if (subchild->getName() == "UnusedBones") {
                    fUnusedBones[i].resize(subchild->countChildren());
                    const pfPrcTag* boneChild = subchild->getFirstChild();
                    for (size_t j=0; j<fUnusedBones[i].size(); j++) {
                        fUnusedBones[i][j] = mgr->prcParseKey(boneChild);
                        boneChild = boneChild->getNextSibling();
                    }
                } else {
                    throw pfPrcTagException(__FILE__, __LINE__, subchild->getName());
                }
                subchild = subchild->getNextSibling();
            }
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Brains") {
        clearBrains();
        fBrains.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fBrains.size(); i++) {
            fBrains[i] = mgr->prcParseCreatableC<plArmatureBrain>(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Detector") {
        fDetector = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plAGMasterMod::IPrcParse(tag, mgr);
    }
}

void plArmatureModBase::clearBrains()
{
    for (auto brain = fBrains.begin(); brain != fBrains.end(); ++brain)
        delete *brain;
    fBrains.clear();
}


/* plArmatureMod */
void plArmatureMod::read(hsStream* S, plResManager* mgr)
{
    if (S->getVer().isUru()) {
        plAGMasterMod::read(S, mgr);
        fDefaultMesh = mgr->readKey(S);
    } else {
        plArmatureModBase::read(S, mgr);
    }

    fRootName = S->readSafeStr();

    if (S->getVer().isUru()) {
        clearBrains();
        fBrains.resize(S->readInt());
        for (size_t i=0; i<fBrains.size(); i++)
            fBrains[i] = mgr->ReadCreatableC<plArmatureBrain>(S);

        if (S->readBool())
            fClothingOutfit = mgr->readKey(S);
        else
            fClothingOutfit = plKey();
    }

    fBodyType = S->readInt();
    if (S->readBool())
        fEffects = mgr->readKey(S);
    else
        fEffects = plKey();

    if (S->getVer().isUruSP() || S->getVer().isUniversal()) {
        fMins.read(S);
        fMaxs.read(S);
    }

    if (!S->getVer().isNewPlasma()) {
        fPhysHeight = S->readFloat();
        fPhysWidth = S->readFloat();
    }

    if (S->getVer().isMoul() || S->getVer().isUniversal()) {
        fFootstepType = S->readSafeStr();
        fFootstepAge = S->readSafeStr();
        fFootstepPage = S->readSafeStr();
    } else {
        fFootstepAge = "CustomAvatars";
        fFootstepPage = "Audio";
        if (fBodyType == kBoneBaseCritter) {
            fFootstepPage = "Quab";
            fFootstepType = "Quab";
        } else if (fBodyType == kBoneBaseMale) {
            fFootstepType = "Male";
        } else if (fBodyType == kBoneBaseFemale) {
            fFootstepType = "Female";
        }
    }
}

void plArmatureMod::write(hsStream* S, plResManager* mgr)
{
    if (S->getVer().isUru()) {
        plAGMasterMod::write(S, mgr);
        mgr->writeKey(S, fDefaultMesh);
    } else {
        plArmatureModBase::write(S, mgr);
    }

    S->writeSafeStr(fRootName);

    S->writeInt(fBrains.size());
    for (size_t i=0; i<fBrains.size(); i++)
        mgr->WriteCreatable(S, fBrains[i]);

    S->writeBool(fClothingOutfit.Exists());
    if (fClothingOutfit.Exists())
        mgr->writeKey(S, fClothingOutfit);

    S->writeInt(fBodyType);
    S->writeBool(fEffects.Exists());
    if (fEffects.Exists())
        mgr->writeKey(S, fEffects);

    if (S->getVer().isUruSP() || S->getVer().isUniversal()) {
        fMins.write(S);
        fMaxs.write(S);
    }

    if (!S->getVer().isNewPlasma()) {
        S->writeFloat(fPhysHeight);
        S->writeFloat(fPhysWidth);
    }

    if (S->getVer().isMoul() || S->getVer().isUniversal()) {
        S->writeSafeStr(fFootstepType);
        S->writeSafeStr(fFootstepAge);
        S->writeSafeStr(fFootstepPage);
    }
}

void plArmatureMod::IPrcWrite(pfPrcHelper* prc)
{
    plArmatureModBase::IPrcWrite(prc);

    prc->writeSimpleTag("DefaultMesh");
    plResManager::PrcWriteKey(prc, fDefaultMesh);
    prc->closeTag();

    prc->startTag("ArmatureParams");
    prc->writeParam("Root", fRootName);
    prc->writeParam("BodyType", fBodyType);
    prc->writeParam("PhysHeight", fPhysHeight);
    prc->writeParam("PhysWidth", fPhysWidth);
    prc->endTag();
      prc->writeSimpleTag("Mins");
      fMins.prcWrite(prc);
      prc->closeTag();
      prc->writeSimpleTag("Maxs");
      fMaxs.prcWrite(prc);
      prc->closeTag();
    prc->closeTag();

    prc->startTag("Footsteps");
    prc->writeParam("Age", fFootstepAge);
    prc->writeParam("Page", fFootstepPage);
    prc->writeParam("Type", fFootstepType);
    prc->endTag(true);

    /*prc->writeSimpleTag("Brains");
    for (size_t i=0; i<fBrains.size(); i++)
        fBrains[i]->prcWrite(prc);
    prc->closeTag();*/

    prc->writeSimpleTag("ClothingOutfit");
    plResManager::PrcWriteKey(prc, fClothingOutfit);
    prc->closeTag();

    prc->writeSimpleTag("Effects");
    plResManager::PrcWriteKey(prc, fEffects);
    prc->closeTag();
}

void plArmatureMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "DefaultMesh") {
        fDefaultMesh = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "ArmatureParams") {
        fRootName = tag->getParam("Root", "");
        fBodyType = tag->getParam("BodyType", "0").to_int();
        fPhysHeight = tag->getParam("PhysHeight", "0").to_float();
        fPhysWidth = tag->getParam("PhysWidth", "0").to_float();
        const pfPrcTag* child = tag->getFirstChild();
        while (child) {
            if (child->getName() == "Mins")
                fMins.prcParse(child->getFirstChild());
            else if (child->getName() == "Maxs")
                fMaxs.prcParse(child->getFirstChild());
            else
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Footsteps") {
        fFootstepAge = tag->getParam("Age", "");
        fFootstepPage = tag->getParam("Page", "");
        fFootstepType = tag->getParam("Type", "");
    } else if (tag->getName() == "Brains") {
        fBrains.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fBrains.size(); i++) {
            fBrains[i] = mgr->prcParseCreatableC<plArmatureBrain>(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "ClothingOutfit") {
        fClothingOutfit = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Effects") {
        fEffects = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plArmatureModBase::IPrcParse(tag, mgr);
    }
}


/* plArmatureLODMod */
void plArmatureLODMod::read(hsStream* S, plResManager* mgr)
{
    plArmatureMod::read(S, mgr);

    fMeshKeys.resize(S->readInt());
    fUnusedBones.resize(fMeshKeys.size());
    for (size_t i=0; i<fMeshKeys.size(); i++) {
        fMeshKeys[i] = mgr->readKey(S);
        fUnusedBones[i].resize(S->readInt());
        for (size_t j=0; j<fUnusedBones[i].size(); j++)
            fUnusedBones[i][j] = mgr->readKey(S);
    }
}

void plArmatureLODMod::write(hsStream* S, plResManager* mgr)
{
    plArmatureMod::write(S, mgr);

    S->writeInt(fMeshKeys.size());
    for (size_t i=0; i<fMeshKeys.size(); i++) {
        mgr->writeKey(S, fMeshKeys[i]);
        S->writeInt(fUnusedBones[i].size());
        for (size_t j=0; j<fUnusedBones[i].size(); j++)
            mgr->writeKey(S, fUnusedBones[i][j]);
    }
}

void plArmatureLODMod::IPrcWrite(pfPrcHelper* prc)
{
    plArmatureMod::IPrcWrite(prc);

    prc->writeSimpleTag("Meshes");
    for (size_t i=0; i<fMeshKeys.size(); i++) {
        prc->writeSimpleTag("Mesh");
        plResManager::PrcWriteKey(prc, fMeshKeys[i]);
        prc->writeSimpleTag("UnusedBones");
        for (size_t j=0; j<fUnusedBones[i].size(); j++)
            plResManager::PrcWriteKey(prc, fUnusedBones[i][j]);
        prc->closeTag(); // UnusedBones
        prc->closeTag(); // Mesh
    }
    prc->closeTag();
}

void plArmatureLODMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Meshes") {
        fMeshKeys.resize(tag->countChildren());
        fUnusedBones.resize(fMeshKeys.size());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fMeshKeys.size(); i++) {
            if (child->getName() != "Mesh")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());

            const pfPrcTag* subchild = child->getFirstChild();
            while (subchild) {
                if (subchild->getName() == "plKey") {
                    fMeshKeys[i] = mgr->prcParseKey(subchild);
                } else if (subchild->getName() == "UnusedBones") {
                    fUnusedBones[i].resize(subchild->countChildren());
                    const pfPrcTag* boneChild = subchild->getFirstChild();
                    for (size_t j=0; j<fUnusedBones[i].size(); j++) {
                        fUnusedBones[i][j] = mgr->prcParseKey(boneChild);
                        boneChild = boneChild->getNextSibling();
                    }
                } else {
                    throw pfPrcTagException(__FILE__, __LINE__, subchild->getName());
                }
                subchild = subchild->getNextSibling();
            }
            child = child->getNextSibling();
        }
    } else {
        plArmatureMod::IPrcParse(tag, mgr);
    }
}
