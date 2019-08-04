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

#include "plLightInfo.h"

plLightInfo::plLightInfo()
{
    fProps.setName(kDisable, "kDisable");
    fProps.setName(kLPCastShadows, "kLPCastShadows");
    fProps.setName(kLPMovable, "kLPMovable");
    fProps.setName(kLPHasIncludes, "kLPHasIncludes");
    fProps.setName(kLPIncludesChars, "kLPIncludesChars");
    fProps.setName(kLPOverAll, "kLPOverAll");
    fProps.setName(kLPHasSpecular, "kLPHasSpecular");
    fProps.setName(kLPShadowOnly, "kLPShadowOnly");
    fProps.setName(kLPShadowLightGroup, "kLPShadowLightGroup");
    fProps.setName(kLPForceProj, "kLPForceProj");
}

void plLightInfo::read(hsStream* S, plResManager* mgr)
{
    plObjInterface::read(S, mgr);

    fAmbient.read(S);
    fDiffuse.read(S);
    fSpecular.read(S);
    fLightToLocal.read(S);
    fLocalToLight.read(S);
    fLightToWorld.read(S);
    fWorldToLight.read(S);
    //fLocalToWorld = fLightToWorld * fLocalToLight;
    //fWorldToLocal = fLightToLocal * fWorldToLight;

    fProjection = mgr->readKey(S);
    fSoftVolume = mgr->readKey(S);
    fSceneNode = mgr->readKey(S);

    fVisRegions.resize(S->readInt());
    for (size_t i=0; i<fVisRegions.size(); i++)
        fVisRegions[i] = mgr->readKey(S);
}

void plLightInfo::write(hsStream* S, plResManager* mgr)
{
    plObjInterface::write(S, mgr);

    fAmbient.write(S);
    fDiffuse.write(S);
    fSpecular.write(S);
    fLightToLocal.write(S);
    fLocalToLight.write(S);
    fLightToWorld.write(S);
    fWorldToLight.write(S);

    mgr->writeKey(S, fProjection);
    mgr->writeKey(S, fSoftVolume);
    mgr->writeKey(S, fSceneNode);

    S->writeInt(fVisRegions.size());
    for (size_t i=0; i<fVisRegions.size(); i++)
        mgr->writeKey(S, fVisRegions[i]);
}

void plLightInfo::IPrcWrite(pfPrcHelper* prc)
{
    plObjInterface::IPrcWrite(prc);

    prc->writeSimpleTag("Ambient");
    fAmbient.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Diffuse");
    fDiffuse.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Specular");
    fSpecular.prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("LightToLocal");
    fLightToLocal.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("LocalToLight");
    fLocalToLight.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("LightToWorld");
    fLightToWorld.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("WorldToLight");
    fWorldToLight.prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Projection");
    plResManager::PrcWriteKey(prc, fProjection);
    prc->closeTag();
    prc->writeSimpleTag("SoftVolume");
    plResManager::PrcWriteKey(prc, fSoftVolume);
    prc->closeTag();
    prc->writeSimpleTag("SceneNode");
    plResManager::PrcWriteKey(prc, fSceneNode);
    prc->closeTag();

    prc->writeSimpleTag("VisRegions");
    for (size_t i=0; i<fVisRegions.size(); i++)
        plResManager::PrcWriteKey(prc, fVisRegions[i]);
    prc->closeTag();
}

void plLightInfo::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Ambient") {
        if (tag->hasChildren())
            fAmbient.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "Diffuse") {
        if (tag->hasChildren())
            fDiffuse.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "Specular") {
        if (tag->hasChildren())
            fSpecular.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "LightToLocal") {
        if (tag->hasChildren())
            fLightToLocal.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "LocalToLight") {
        if (tag->hasChildren())
            fLocalToLight.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "LightToWorld") {
        if (tag->hasChildren())
            fLightToWorld.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "WorldToLight") {
        if (tag->hasChildren())
            fWorldToLight.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "Projection") {
        if (tag->hasChildren())
            fProjection = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "SoftVolume") {
        if (tag->hasChildren())
            fSoftVolume = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "SceneNode") {
        if (tag->hasChildren())
            fSceneNode = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "VisRegions") {
        fVisRegions.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fVisRegions.size(); i++) {
            fVisRegions[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        plObjInterface::IPrcParse(tag, mgr);
    }
}
