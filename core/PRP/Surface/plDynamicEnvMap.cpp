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

#include "plDynamicEnvMap.h"

/* plDynamicEnvMap */
void plDynamicEnvMap::read(hsStream* S, plResManager* mgr)
{
    plCubicRenderTarget::read(S, mgr);

    fPos.read(S);
    fHither = S->readFloat();
    fYon = S->readFloat();
    fFogStart = S->readFloat();
    fColor.read(S);
    fRefreshRate = S->readFloat();
    fIncCharacters = S->readBool();

    fVisRegions.resize(S->readInt());
    for (size_t i=0; i<fVisRegions.size(); i++)
        fVisRegions[i] = mgr->readKey(S);

    if (!S->getVer().isUruSP() || S->getVer().isUniversal()) {
        fVisRegionNames.resize(S->readInt());
        for (size_t i=0; i<fVisRegionNames.size(); i++)
            fVisRegionNames[i] = S->readSafeStr();

        fRootNode = mgr->readKey(S);
    } else {
        fVisRegionNames.clear();
        fRootNode = plKey();
    }
}

void plDynamicEnvMap::write(hsStream* S, plResManager* mgr)
{
    plCubicRenderTarget::write(S, mgr);

    fPos.write(S);
    S->writeFloat(fHither);
    S->writeFloat(fYon);
    S->writeFloat(fFogStart);
    fColor.write(S);
    S->writeFloat(fRefreshRate);
    S->writeBool(fIncCharacters);

    S->writeInt(fVisRegions.size());
    for (size_t i=0; i<fVisRegions.size(); i++)
        mgr->writeKey(S, fVisRegions[i]);

    if (!S->getVer().isUruSP() || S->getVer().isUniversal()) {
        S->writeInt(fVisRegionNames.size());
        for (size_t i=0; i<fVisRegionNames.size(); i++)
            S->writeSafeStr(fVisRegionNames[i]);

        mgr->writeKey(S, fRootNode);
    }
}

void plDynamicEnvMap::IPrcWrite(pfPrcHelper* prc)
{
    plCubicRenderTarget::IPrcWrite(prc);

    prc->startTag("DynamicEnvMapParams");
    prc->writeParam("Hither", fHither);
    prc->writeParam("Yon", fYon);
    prc->writeParam("FogStart", fFogStart);
    prc->writeParam("RefreshRate", fRefreshRate);
    prc->writeParam("IncCharacters", fIncCharacters);
    prc->endTag();
      prc->writeSimpleTag("Pos");
      fPos.prcWrite(prc);
      prc->closeTag();
      fColor.prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("VisRegions");
    for (size_t i=0; i<fVisRegions.size(); i++)
        plResManager::PrcWriteKey(prc, fVisRegions[i]);
    prc->closeTag();

    prc->writeSimpleTag("VisRegionNames");
    for (size_t i=0; i<fVisRegionNames.size(); i++) {
        prc->startTag("Region");
        prc->writeParam("Name", fVisRegionNames[i]);
        prc->endTag(true);
    }
    prc->closeTag();

    prc->writeSimpleTag("RootNode");
    plResManager::PrcWriteKey(prc, fRootNode);
    prc->closeTag();
}

void plDynamicEnvMap::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "DynamicEnvMapParams") {
        fHither = tag->getParam("Hither", "0").to_float();
        fYon = tag->getParam("Yon", "0").to_float();
        fFogStart = tag->getParam("FogStart", "0").to_float();
        fRefreshRate = tag->getParam("RefreshRate", "0").to_float();
        fIncCharacters = tag->getParam("IncCharacters", "false").to_bool();

        const pfPrcTag* child = tag->getFirstChild();
        while (child) {
            if (child->getName() == "Pos") {
                if (child->hasChildren())
                    fPos.prcParse(child->getFirstChild());
            } else if (child->getName() == "hsColorRGBA") {
                fColor.prcParse(child);
            } else {
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            }
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "VisRegions") {
        fVisRegions.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fVisRegions.size(); i++) {
            fVisRegions[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "VisRegionNames") {
        fVisRegionNames.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fVisRegionNames.size(); i++) {
            if (child->getName() != "Region")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            fVisRegionNames[i] = tag->getParam("Name", "");
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "RootNode") {
        if (tag->hasChildren())
            fRootNode = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plCubicRenderTarget::IPrcParse(tag, mgr);
    }
}


/* plDynamicCamMap */
void plDynamicCamMap::read(hsStream* S, plResManager* mgr)
{
    plRenderTarget::read(S, mgr);

    fHither = S->readFloat();
    fYon = S->readFloat();
    fFogStart = S->readFloat();
    fColor.read(S);
    fRefreshRate = S->readFloat();
    fIncCharacters = S->readBool();

    fCamera = mgr->readKey(S);
    fRootNode = mgr->readKey(S);

    fTargetNodes.resize(S->readByte());
    for (size_t i=0; i<fTargetNodes.size(); i++)
        fTargetNodes[i] = mgr->readKey(S);

    fVisRegions.resize(S->readInt());
    for (size_t i=0; i<fVisRegions.size(); i++)
        fVisRegions[i] = mgr->readKey(S);

    fVisRegionNames.resize(S->readInt());
    for (size_t i=0; i<fVisRegionNames.size(); i++)
        fVisRegionNames[i] = S->readSafeStr();

    fDisableTexture = mgr->readKey(S);

    fMatLayers.resize(S->readByte());
    for (size_t i=0; i<fMatLayers.size(); i++)
        fMatLayers[i] = mgr->readKey(S);
}

void plDynamicCamMap::write(hsStream* S, plResManager* mgr)
{
    plRenderTarget::write(S, mgr);

    S->writeFloat(fHither);
    S->writeFloat(fYon);
    S->writeFloat(fFogStart);
    fColor.write(S);
    S->writeFloat(fRefreshRate);
    S->writeBool(fIncCharacters);

    mgr->writeKey(S, fCamera);
    mgr->writeKey(S, fRootNode);

    S->writeByte(fTargetNodes.size());
    for (size_t i=0; i<fTargetNodes.size(); i++)
        mgr->writeKey(S, fTargetNodes[i]);

    S->writeInt(fVisRegions.size());
    for (size_t i=0; i<fVisRegions.size(); i++)
        mgr->writeKey(S, fVisRegions[i]);

    S->writeInt(fVisRegionNames.size());
    for (size_t i=0; i<fVisRegionNames.size(); i++)
        S->writeSafeStr(fVisRegionNames[i]);

    mgr->writeKey(S, fDisableTexture);

    S->writeByte(fMatLayers.size());
    for (size_t i=0; i<fMatLayers.size(); i++)
        mgr->writeKey(S, fMatLayers[i]);
}

void plDynamicCamMap::IPrcWrite(pfPrcHelper* prc)
{
    plRenderTarget::IPrcWrite(prc);

    prc->startTag("DynamicCamMapParams");
    prc->writeParam("Hither", fHither);
    prc->writeParam("Yon", fYon);
    prc->writeParam("FogStart", fFogStart);
    prc->writeParam("RefreshRate", fRefreshRate);
    prc->writeParam("IncCharacters", fIncCharacters);
    prc->endTag();
    fColor.prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Camera");
    plResManager::PrcWriteKey(prc, fCamera);
    prc->closeTag();

    prc->writeSimpleTag("RootNode");
    plResManager::PrcWriteKey(prc, fRootNode);
    prc->closeTag();

    prc->writeSimpleTag("TargetNodes");
    for (size_t i=0; i<fTargetNodes.size(); i++)
        plResManager::PrcWriteKey(prc, fTargetNodes[i]);
    prc->closeTag();

    prc->writeSimpleTag("VisRegions");
    for (size_t i=0; i<fVisRegions.size(); i++)
        plResManager::PrcWriteKey(prc, fVisRegions[i]);
    prc->closeTag();

    prc->writeSimpleTag("VisRegionNames");
    for (size_t i=0; i<fVisRegionNames.size(); i++) {
        prc->startTag("Region");
        prc->writeParam("Name", fVisRegionNames[i]);
        prc->endTag(true);
    }
    prc->closeTag();

    prc->writeSimpleTag("DisableTexture");
    plResManager::PrcWriteKey(prc, fDisableTexture);
    prc->closeTag();

    prc->writeSimpleTag("MatLayers");
    for (size_t i=0; i<fMatLayers.size(); i++)
        plResManager::PrcWriteKey(prc, fMatLayers[i]);
    prc->closeTag();
}

void plDynamicCamMap::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "DynamicCamMapParams") {
        fHither = tag->getParam("Hither", "0").to_float();
        fYon = tag->getParam("Yon", "0").to_float();
        fFogStart = tag->getParam("FogStart", "0").to_float();
        fRefreshRate = tag->getParam("RefreshRate", "0").to_float();
        fIncCharacters = tag->getParam("IncCharacters", "false").to_bool();

        const pfPrcTag* child = tag->getFirstChild();
        while (child) {
            if (child->getName() == "hsColorRGBA") {
                fColor.prcParse(child);
            } else {
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            }
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Camera") {
        if (tag->hasChildren())
            fCamera = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "RootNode") {
        if (tag->hasChildren())
            fRootNode = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "TargetNodes") {
        fTargetNodes.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fTargetNodes.size(); i++) {
            fTargetNodes[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "VisRegions") {
        fVisRegions.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fVisRegions.size(); i++) {
            fVisRegions[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "VisRegionNames") {
        fVisRegionNames.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fVisRegionNames.size(); i++) {
            if (child->getName() != "Region")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            fVisRegionNames[i] = tag->getParam("Name", "");
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "DisableTexture") {
        if (tag->hasChildren())
            fDisableTexture = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "MatLayers") {
        fMatLayers.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fMatLayers.size(); i++) {
            fMatLayers[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        plRenderTarget::IPrcParse(tag, mgr);
    }
}
