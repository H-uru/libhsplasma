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

#include "plClusterGroup.h"

/* plLODDist */
void plLODDist::read(hsStream* S)
{
    fMinDist = S->readFloat();
    fMaxDist = S->readFloat();
}

void plLODDist::write(hsStream* S)
{
    S->writeFloat(fMinDist);
    S->writeFloat(fMaxDist);
}

void plLODDist::prcWrite(pfPrcHelper* prc)
{
    prc->startTag("plLODDist");
    prc->writeParam("Min", fMinDist);
    prc->writeParam("Max", fMaxDist);
    prc->endTag(true);
}

void plLODDist::prcParse(const pfPrcTag* tag)
{
    if (tag->getName() != "plLODDist")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fMinDist = tag->getParam("Min", "0").to_float();
    fMaxDist = tag->getParam("Max", "0").to_float();
}


/* plClusterGroup */
plClusterGroup::~plClusterGroup()
{
    for (auto cluster = fClusters.begin(); cluster != fClusters.end(); ++cluster)
        delete *cluster;
}

void plClusterGroup::read(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::read(S, mgr);

    fTemplate.read(S);
    fMaterial = mgr->readKey(S);

    clearClusters();
    fClusters.resize(S->readInt());
    for (size_t i=0; i<fClusters.size(); i++) {
        fClusters[i] = new plCluster();
        fClusters[i]->read(S, this);
    }

    fRegions.resize(S->readInt());
    for (size_t i=0; i<fRegions.size(); i++)
        fRegions[i] = mgr->readKey(S);
    fLights.resize(S->readInt());
    for (size_t i=0; i<fLights.size(); i++)
        fLights[i] = mgr->readKey(S);

    fLOD.read(S);
    fRenderLevel = S->readInt();
    fSceneNode = mgr->readKey(S);
}

void plClusterGroup::write(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::write(S, mgr);

    fTemplate.write(S);
    mgr->writeKey(S, fMaterial);

    S->writeInt(fClusters.size());
    for (size_t i=0; i<fClusters.size(); i++)
        fClusters[i]->write(S);

    S->writeInt(fRegions.size());
    for (size_t i=0; i<fRegions.size(); i++)
        mgr->writeKey(S, fRegions[i]);
    S->writeInt(fLights.size());
    for (size_t i=0; i<fLights.size(); i++)
        mgr->writeKey(S, fLights[i]);

    fLOD.write(S);
    S->writeInt(fRenderLevel);
    mgr->writeKey(S, fSceneNode);
}

void plClusterGroup::IPrcWrite(pfPrcHelper* prc)
{
    hsKeyedObject::IPrcWrite(prc);

    prc->writeSimpleTag("Template");
    fTemplate.prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Material");
    plResManager::PrcWriteKey(prc, fMaterial);
    prc->closeTag();

    prc->writeSimpleTag("Clusters");
    for (size_t i=0; i<fClusters.size(); i++)
        fClusters[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Regions");
    for (size_t i=0; i<fRegions.size(); i++)
        plResManager::PrcWriteKey(prc, fRegions[i]);
    prc->closeTag();

    prc->writeSimpleTag("Lights");
    for (size_t i=0; i<fLights.size(); i++)
        plResManager::PrcWriteKey(prc, fLights[i]);
    prc->closeTag();

    prc->writeSimpleTag("LOD");
    fLOD.prcWrite(prc);
    prc->closeTag();

    prc->startTag("RenderLevel");
    prc->writeParamHex("Level", fRenderLevel);
    prc->endTag(true);

    prc->writeSimpleTag("SceneNode");
    plResManager::PrcWriteKey(prc, fSceneNode);
    prc->closeTag();
}

void plClusterGroup::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Template") {
        if (tag->hasChildren())
            fTemplate.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "Material") {
        if (tag->hasChildren())
            fMaterial = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Clusters") {
        clearClusters();
        fClusters.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fClusters.size(); i++) {
            fClusters[i] = new plCluster();
            fClusters[i]->prcParse(child, this);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Regions") {
        fRegions.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fRegions.size(); i++) {
            fRegions[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Lights") {
        fLights.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fLights.size(); i++) {
            fLights[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "LOD") {
        if (tag->hasChildren())
            fLOD.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "RenderLevel") {
        fRenderLevel = tag->getParam("Level", "0").to_uint();
    } else if (tag->getName() == "SceneNode") {
        if (tag->hasChildren())
            fSceneNode = mgr->prcParseKey(tag->getFirstChild());
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}

void plClusterGroup::delCluster(size_t idx)
{
    delete fClusters[idx];
    fClusters.erase(fClusters.begin() + idx);
}

void plClusterGroup::clearClusters()
{
    for (auto cluster = fClusters.begin(); cluster != fClusters.end(); ++cluster)
        delete *cluster;
    fClusters.clear();
}
