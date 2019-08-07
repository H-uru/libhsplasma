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

#include "plClothingItem.h"
#include "Debug/plDebug.h"

plClothingItem::plClothingItem()
    : fGroup(), fType(), fTileset(), fSortOrder()
{
    fDefaultTint1[0] = fDefaultTint2[0] = 255;
    fDefaultTint1[1] = fDefaultTint2[1] = 255;
    fDefaultTint1[2] = fDefaultTint2[2] = 255;
}

plClothingItem::~plClothingItem()
{
    for (auto tex = fTextures.begin(); tex != fTextures.end(); ++tex)
        delete[] *tex;
}

void plClothingItem::read(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::read(S, mgr);

    fItemName = S->readSafeStr();
    fGroup = S->readByte();
    fType = S->readByte();
    fTileset = S->readByte();
    fSortOrder = S->readByte();
    fDescription = S->readSafeStr();
    fCustomText = S->readSafeStr();

    if (S->readBool())
        fIcon = mgr->readKey(S);

    clearElements();
    fElementNames.resize(S->readInt());
    fTextures.resize(fElementNames.size());
    for (size_t i=0; i<fElementNames.size(); i++) {
        fElementNames[i] = S->readSafeStr();
        fTextures[i] = new plKey[kLayerMax];
        size_t count = S->readByte();
        for (size_t j=0; j<count; j++) {
            size_t idx = S->readByte();
            plKey k = mgr->readKey(S);
            if (idx < kLayerMax)
                fTextures[i][idx] = k;
            else
                plDebug::Warning("Throwing away key {}", k.toString());
        }
    }

    for (size_t i=0; i<kNumLODLevels; i++) {
        if (S->readBool())
            fMeshes[i] = mgr->readKey(S);
    }

    fAccessory = mgr->readKey(S);

    for (size_t i=0; i<3; i++) {
        fDefaultTint1[i] = S->readByte();
        fDefaultTint2[i] = S->readByte();
    }
}

void plClothingItem::write(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::write(S, mgr);

    S->writeSafeStr(fItemName);
    S->writeByte(fGroup);
    S->writeByte(fType);
    S->writeByte(fTileset);
    S->writeByte(fSortOrder);
    S->writeSafeStr(fDescription);
    S->writeSafeStr(fCustomText);

    S->writeBool(fIcon.Exists());
    if (fIcon.Exists())
        mgr->writeKey(S, fIcon);

    S->writeInt(fTextures.size());
    for (size_t i=0; i<fTextures.size(); i++) {
        S->writeSafeStr(fElementNames[i]);
        int count = 0;
        for (size_t j=0; j<kLayerMax; j++) {
            if (fTextures[i][j].Exists())
                count++;
        }
        S->writeByte(count);
        for (size_t j=0; j<kLayerMax; j++) {
            if (fTextures[i][j].Exists()) {
                S->writeByte(j);
                mgr->writeKey(S, fTextures[i][j]);
            }
        }
    }

    for (size_t i=0; i<kNumLODLevels; i++) {
        S->writeBool(fMeshes[i].Exists());
        if (fMeshes[i].Exists())
            mgr->writeKey(S, fMeshes[i]);
    }

    mgr->writeKey(S, fAccessory);

    for (size_t i=0; i<3; i++) {
        S->writeByte(fDefaultTint1[i]);
        S->writeByte(fDefaultTint2[i]);
    }
}

void plClothingItem::IPrcWrite(pfPrcHelper* prc)
{
    hsKeyedObject::IPrcWrite(prc);

    prc->startTag("ClothingName");
    prc->writeParam("value", fItemName);
    prc->endTag(true);

    prc->startTag("ClosetOptions");
    prc->writeParam("Group", fGroup);
    prc->writeParam("Type", fType);
    prc->writeParam("Tileset", fTileset);
    prc->writeParam("SortOrder", fSortOrder);
    prc->endTag(true);

    prc->writeTagNoBreak("Description");
    prc->directWrite(fDescription);
    prc->closeTagNoBreak();

    prc->startTag("CustomText");
    prc->writeParam("value", fCustomText);
    prc->endTag(true);

    prc->writeSimpleTag("Icon");
    plResManager::PrcWriteKey(prc, fIcon);
    prc->closeTag();

    prc->writeSimpleTag("Elements");
    for (size_t i=0; i<fTextures.size(); i++) {
        prc->startTag("Element");
        prc->writeParam("Name", fElementNames[i]);
        prc->endTag();
        for (size_t j=0; j<kLayerMax; j++)
            plResManager::PrcWriteKey(prc, fTextures[i][j]);
        prc->closeTag();
    }
    prc->closeTag();

    prc->writeSimpleTag("Meshes");
    for (size_t i=0; i<kNumLODLevels; i++)
        plResManager::PrcWriteKey(prc, fMeshes[i]);
    prc->closeTag();

    prc->writeSimpleTag("Accessory");
    plResManager::PrcWriteKey(prc, fAccessory);
    prc->closeTag();

    prc->writeSimpleTag("DefaultTints");
    prc->startTag("Tint1");
    prc->writeParam("red", fDefaultTint1[0]);
    prc->writeParam("green", fDefaultTint1[1]);
    prc->writeParam("blue", fDefaultTint1[2]);
    prc->endTag(true);
    prc->startTag("Tint2");
    prc->writeParam("red", fDefaultTint2[0]);
    prc->writeParam("green", fDefaultTint2[1]);
    prc->writeParam("blue", fDefaultTint2[2]);
    prc->endTag(true);
    prc->closeTag();
}

void plClothingItem::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "ClothingName") {
        fItemName = tag->getParam("value", "");
    } else if (tag->getName() == "ClosetOptions") {
        fGroup = tag->getParam("Group", "0").to_uint();
        fType = tag->getParam("Type", "0").to_uint();
        fTileset = tag->getParam("Tileset", "0").to_uint();
        fSortOrder = tag->getParam("SortOrder", "0").to_uint();
    } else if (tag->getName() == "Description") {
        fDescription = "";
        std::list<ST::string> descTokens = tag->getContents();
        for (auto tok = descTokens.begin(); tok != descTokens.end(); ++tok)
            fDescription += *tok + " ";
    } else if (tag->getName() == "CustomText") {
        fCustomText = tag->getParam("value", "");
    } else if (tag->getName() == "Icon") {
        if (tag->hasChildren())
            fIcon = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Elements") {
        clearElements();
        fElementNames.resize(tag->countChildren());
        fTextures.resize(fElementNames.size());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fElementNames.size(); i++) {
            if (child->getName() != "Element")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            fElementNames[i] = child->getParam("Name", "");
            fTextures[i] = new plKey[10];
            size_t nSubChildren = child->countChildren();
            const pfPrcTag* subChild = child->getFirstChild();
            for (size_t j=0; j<nSubChildren; j++) {
                plKey k = mgr->prcParseKey(subChild);
                if (j < kLayerMax)
                    fTextures[i][j] = k;
                else
                    plDebug::Warning("Throwing away key {}", k.toString());
                subChild = subChild->getNextSibling();
            }
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Meshes") {
        size_t nMeshes = tag->countChildren();
        if (nMeshes != kNumLODLevels)
            throw hsBadParamException(__FILE__, __LINE__);
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<kNumLODLevels; i++) {
            fMeshes[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Accessory") {
        if (tag->hasChildren())
            fAccessory = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "DefaultTints") {
        const pfPrcTag* child = tag->getFirstChild();
        while (child) {
            if (child->getName() == "Tint1") {
                fDefaultTint1[0] = child->getParam("red", "0").to_uint();
                fDefaultTint1[1] = child->getParam("green", "0").to_uint();
                fDefaultTint1[2] = child->getParam("blue", "0").to_uint();
            } else if (child->getName() == "Tint2") {
                fDefaultTint2[0] = child->getParam("red", "0").to_uint();
                fDefaultTint2[1] = child->getParam("green", "0").to_uint();
                fDefaultTint2[2] = child->getParam("blue", "0").to_uint();
            } else {
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            }
            child = child->getNextSibling();
        }
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}

void plClothingItem::setDefaultTint1(const hsColorRGBA& tint)
{
    fDefaultTint1[0] = tint.r * 255;
    fDefaultTint1[1] = tint.g * 255;
    fDefaultTint1[2] = tint.b * 255;
}

void plClothingItem::setDefaultTint2(const hsColorRGBA& tint)
{
    fDefaultTint2[0] = tint.r * 255;
    fDefaultTint2[1] = tint.g * 255;
    fDefaultTint2[2] = tint.b * 255;
}

void plClothingItem::clearElements()
{
    for (auto tex = fTextures.begin(); tex != fTextures.end(); ++tex)
        delete[] *tex;
    fTextures.clear();
    fElementNames.clear();
}

void plClothingItem::addElement(const ST::string& elementName)
{
    fElementNames.push_back(elementName);
    fTextures.push_back(new plKey[kLayerMax]);
}

void plClothingItem::delElement(int element)
{
    delete[] fTextures[element];
    fTextures.erase(fTextures.begin() + element);
    fElementNames.erase(fElementNames.begin() + element);
}
