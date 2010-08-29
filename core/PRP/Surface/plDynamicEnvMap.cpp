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
plDynamicEnvMap::plDynamicEnvMap()
               : fHither(0.0f), fYon(0.0f), fFogStart(0.0f), fRefreshRate(0.0f),
                 fIncCharacters(false) { }

void plDynamicEnvMap::read(hsStream* S, plResManager* mgr) {
    plCubicRenderTarget::read(S, mgr);

    fPos.read(S);
    fHither = S->readFloat();
    fYon = S->readFloat();
    fFogStart = S->readFloat();
    fColor.read(S);
    fRefreshRate = S->readFloat();
    fIncCharacters = S->readByte();

    fVisRegions.setSize(S->readInt());
    for (size_t i=0; i<fVisRegions.getSize(); i++)
        fVisRegions[i] = mgr->readKey(S);

    if (S->getVer().isLive() || S->getVer().isUniversal()) {
        fVisRegionNames.setSize(S->readInt());
        for (size_t i=0; i<fVisRegionNames.getSize(); i++)
            fVisRegionNames[i] = S->readSafeStr();

        fRootNode = mgr->readKey(S);
    } else {
        fVisRegionNames.setSize(0);
        fRootNode = plKey();
    }
}

void plDynamicEnvMap::write(hsStream* S, plResManager* mgr) {
    plCubicRenderTarget::write(S, mgr);

    fPos.write(S);
    S->writeFloat(fHither);
    S->writeFloat(fYon);
    S->writeFloat(fFogStart);
    fColor.write(S);
    S->writeFloat(fRefreshRate);
    S->writeByte(fIncCharacters);

    S->writeInt(fVisRegions.getSize());
    for (size_t i=0; i<fVisRegions.getSize(); i++)
        mgr->writeKey(S, fVisRegions[i]);

    if (S->getVer().isLive() || S->getVer().isUniversal()) {
        S->writeInt(fVisRegionNames.getSize());
        for (size_t i=0; i<fVisRegionNames.getSize(); i++)
            S->writeSafeStr(fVisRegionNames[i]);

        mgr->writeKey(S, fRootNode);
    }
}

void plDynamicEnvMap::IPrcWrite(pfPrcHelper* prc) {
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
    for (size_t i=0; i<fVisRegions.getSize(); i++)
        fVisRegions[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("VisRegionNames");
    for (size_t i=0; i<fVisRegionNames.getSize(); i++) {
        prc->startTag("Region");
        prc->writeParam("Name", fVisRegionNames[i]);
        prc->endTag(true);
    }
    prc->closeTag();

    prc->writeSimpleTag("RootNode");
    fRootNode->prcWrite(prc);
    prc->closeTag();
}

void plDynamicEnvMap::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "DynamicEnvMapParams") {
        fHither = tag->getParam("Hither", "0").toFloat();
        fYon = tag->getParam("Yon", "0").toFloat();
        fFogStart = tag->getParam("FogStart", "0").toFloat();
        fRefreshRate = tag->getParam("RefreshRate", "0").toFloat();
        fIncCharacters = tag->getParam("IncCharacters", "0").toUint();

        const pfPrcTag* child = tag->getFirstChild();
        while (child != NULL) {
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
        fVisRegions.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fVisRegions.getSize(); i++) {
            fVisRegions[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "VisRegionNames") {
        fVisRegionNames.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fVisRegionNames.getSize(); i++) {
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
plDynamicCamMap::plDynamicCamMap()
               : fHither(0.0f), fYon(0.0f), fFogStart(0.0f), fRefreshRate(0.0f),
                 fIncCharacters(false) { }

void plDynamicCamMap::read(hsStream* S, plResManager* mgr) {
    plRenderTarget::read(S, mgr);

    fHither = S->readFloat();
    fYon = S->readFloat();
    fFogStart = S->readFloat();
    fColor.read(S);
    fRefreshRate = S->readFloat();
    fIncCharacters = S->readByte();

    fCamera = mgr->readKey(S);
    fRootNode = mgr->readKey(S);

    fTargetNodes.setSize(S->readByte());
    for (size_t i=0; i<fTargetNodes.getSize(); i++)
        fTargetNodes[i] = mgr->readKey(S);

    fVisRegions.setSize(S->readInt());
    for (size_t i=0; i<fVisRegions.getSize(); i++)
        fVisRegions[i] = mgr->readKey(S);

    fVisRegionNames.setSize(S->readInt());
    for (size_t i=0; i<fVisRegionNames.getSize(); i++)
        fVisRegionNames[i] = S->readSafeStr();

    fDisableTexture = mgr->readKey(S);

    fMatLayers.setSize(S->readByte());
    for (size_t i=0; i<fMatLayers.getSize(); i++)
        fMatLayers[i] = mgr->readKey(S);
}

void plDynamicCamMap::write(hsStream* S, plResManager* mgr) {
    plRenderTarget::write(S, mgr);

    S->writeFloat(fHither);
    S->writeFloat(fYon);
    S->writeFloat(fFogStart);
    fColor.write(S);
    S->writeFloat(fRefreshRate);
    S->writeByte(fIncCharacters);

    mgr->writeKey(S, fCamera);
    mgr->writeKey(S, fRootNode);

    S->writeByte(fTargetNodes.getSize());
    for (size_t i=0; i<fTargetNodes.getSize(); i++)
        mgr->writeKey(S, fTargetNodes[i]);

    S->writeInt(fVisRegions.getSize());
    for (size_t i=0; i<fVisRegions.getSize(); i++)
        mgr->writeKey(S, fVisRegions[i]);

    S->writeInt(fVisRegionNames.getSize());
    for (size_t i=0; i<fVisRegionNames.getSize(); i++)
        S->writeSafeStr(fVisRegionNames[i]);

    mgr->writeKey(S, fDisableTexture);

    S->writeByte(fMatLayers.getSize());
    for (size_t i=0; i<fMatLayers.getSize(); i++)
        mgr->writeKey(S, fMatLayers[i]);
}

void plDynamicCamMap::IPrcWrite(pfPrcHelper* prc) {
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
    fCamera->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("RootNode");
    fRootNode->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("TargetNodes");
    for (size_t i=0; i<fTargetNodes.getSize(); i++)
        fTargetNodes[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("VisRegions");
    for (size_t i=0; i<fVisRegions.getSize(); i++)
        fVisRegions[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("VisRegionNames");
    for (size_t i=0; i<fVisRegionNames.getSize(); i++) {
        prc->startTag("Region");
        prc->writeParam("Name", fVisRegionNames[i]);
        prc->endTag(true);
    }
    prc->closeTag();

    prc->writeSimpleTag("DisableTexture");
    fDisableTexture->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("MatLayers");
    for (size_t i=0; i<fMatLayers.getSize(); i++)
        fMatLayers[i]->prcWrite(prc);
    prc->closeTag();
}

void plDynamicCamMap::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "DynamicCamMapParams") {
        fHither = tag->getParam("Hither", "0").toFloat();
        fYon = tag->getParam("Yon", "0").toFloat();
        fFogStart = tag->getParam("FogStart", "0").toFloat();
        fRefreshRate = tag->getParam("RefreshRate", "0").toFloat();
        fIncCharacters = tag->getParam("IncCharacters", "0").toUint();

        const pfPrcTag* child = tag->getFirstChild();
        while (child != NULL) {
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
        fTargetNodes.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fTargetNodes.getSize(); i++) {
            fTargetNodes[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "VisRegions") {
        fVisRegions.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fVisRegions.getSize(); i++) {
            fVisRegions[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "VisRegionNames") {
        fVisRegionNames.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fVisRegionNames.getSize(); i++) {
            if (child->getName() != "Region")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            fVisRegionNames[i] = tag->getParam("Name", "");
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "DisableTexture") {
        if (tag->hasChildren())
            fDisableTexture = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "MatLayers") {
        fMatLayers.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fMatLayers.getSize(); i++) {
            fMatLayers[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        plRenderTarget::IPrcParse(tag, mgr);
    }
}
