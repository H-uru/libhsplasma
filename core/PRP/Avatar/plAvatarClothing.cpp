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

#include "plAvatarClothing.h"

/* plClothingOutfit */
const char* const plClothingOutfit::GroupNames[] = {
    "Male", "Female", "(No Options)"
};

const char* const plClothingOutfit::TypeNames[] = {
    "Pants", "Shirt", "LeftHand", "RightHand", "Face", "Hair",
    "LeftFoot", "RightFoot", "Accessory"
};

void plClothingOutfit::read(hsStream* S, plResManager* mgr)
{
    plSynchedObject::read(S, mgr);

    fGroup = S->readByte();
    fBase = mgr->readKey(S);
    if (fGroup != kClothingGroupNoOptions) {
        fTargetTexture = mgr->readKey(S);
        fMaterial = mgr->readKey(S);
    }
}

void plClothingOutfit::write(hsStream* S, plResManager* mgr)
{
    plSynchedObject::write(S, mgr);

    S->writeByte(fGroup);
    mgr->writeKey(S, fBase);
    if (fGroup != kClothingGroupNoOptions) {
        mgr->writeKey(S, fTargetTexture);
        mgr->writeKey(S, fMaterial);
    }
}

void plClothingOutfit::IPrcWrite(pfPrcHelper* prc)
{
    plSynchedObject::IPrcWrite(prc);

    prc->startTag("Group");
    prc->writeParam("Type", GroupNames[fGroup]);
    prc->endTag(true);

    prc->writeSimpleTag("Base");
    plResManager::PrcWriteKey(prc, fBase);
    prc->closeTag();

    if (fGroup != kClothingGroupNoOptions) {
        prc->writeSimpleTag("TargetTexture");
        plResManager::PrcWriteKey(prc, fTargetTexture);
        prc->closeTag();

        prc->writeSimpleTag("Material");
        plResManager::PrcWriteKey(prc, fMaterial);
        prc->closeTag();
    }
}

void plClothingOutfit::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Group") {
        ST::string grpName = tag->getParam("Type", "");
        fGroup = kClothingGroupNoOptions;
        for (size_t i=0; i<kMaxClothingGroup; i++) {
            if (grpName == GroupNames[i])
                fGroup = i;
        }
    } else if (tag->getName() == "Base") {
        if (tag->hasChildren())
            fBase = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "TargetTexture") {
        if (tag->hasChildren())
            fTargetTexture = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Material") {
        if (tag->hasChildren())
            fMaterial = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plSynchedObject::IPrcParse(tag, mgr);
    }
}


/* plClothingBase */
void plClothingBase::read(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::read(S, mgr);

    fName = S->readSafeStr();
    if (S->readBool())
        fBaseTexture = mgr->readKey(S);
    fLayoutName = S->readSafeStr();
}

void plClothingBase::write(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::write(S, mgr);

    S->writeSafeStr(fName);
    if (fBaseTexture.Exists()) {
        S->writeBool(true);
        mgr->writeKey(S, fBaseTexture);
    } else {
        S->writeBool(false);
    }
    S->writeSafeStr(fLayoutName);
}

void plClothingBase::IPrcWrite(pfPrcHelper* prc)
{
    hsKeyedObject::IPrcWrite(prc);

    prc->startTag("ClothingBaseParams");
    prc->writeParam("Name", fName);
    prc->writeParam("Layout", fLayoutName);
    prc->endTag(true);

    prc->writeSimpleTag("BaseTexture");
    plResManager::PrcWriteKey(prc, fBaseTexture);
    prc->closeTag();
}

void plClothingBase::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "ClothingBaseParams") {
        fName = tag->getParam("Name", "");
        fLayoutName = tag->getParam("Layout", "");
    } else if (tag->getName() == "BaseTexture") {
        if (tag->hasChildren())
            fBaseTexture = mgr->prcParseKey(tag->getFirstChild());
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}
