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

#include "plOccluder.h"

/* plOccluder */
void plOccluder::read(hsStream* S, plResManager* mgr)
{
    plObjInterface::read(S, mgr);

    fWorldBounds.read(S);
    fPriority = S->readFloat();

    fPolys.resize(S->readShort());
    for (size_t i=0; i<fPolys.size(); i++)
        fPolys[i].read(S);

    fSceneNode = mgr->readKey(S);
    fVisRegions.resize(S->readShort());
    for (size_t i=0; i<fVisRegions.size(); i++)
        fVisRegions[i] = mgr->readKey(S);
}

void plOccluder::write(hsStream* S, plResManager* mgr)
{
    plObjInterface::write(S, mgr);

    fWorldBounds.write(S);
    S->writeFloat(fPriority);

    S->writeShort(fPolys.size());
    for (size_t i=0; i<fPolys.size(); i++)
        fPolys[i].write(S);

    mgr->writeKey(S, fSceneNode);
    S->writeShort(fVisRegions.size());
    for (size_t i=0; i<fVisRegions.size(); i++)
        mgr->writeKey(S, fVisRegions[i]);
}

void plOccluder::IPrcWrite(pfPrcHelper* prc)
{
    plObjInterface::IPrcWrite(prc);

    prc->writeSimpleTag("WorldBounds");
    fWorldBounds.prcWrite(prc);
    prc->closeTag();

    prc->startTag("Priority");
    prc->writeParam("value", fPriority);
    prc->endTag(true);

    prc->writeSimpleTag("Polys");
    for (size_t i=0; i<fPolys.size(); i++)
        fPolys[i].prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("SceneNode");
    plResManager::PrcWriteKey(prc, fSceneNode);
    prc->closeTag();

    prc->writeSimpleTag("VisRegions");
    for (size_t i=0; i<fVisRegions.size(); i++)
        plResManager::PrcWriteKey(prc, fVisRegions[i]);
    prc->closeTag();
}

void plOccluder::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "WorldBounds") {
        if (tag->hasChildren())
            fWorldBounds.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "Priority") {
        fPriority = tag->getParam("value", "0").to_float();
    } else if (tag->getName() == "Polys") {
        fPolys.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fPolys.size(); i++) {
            fPolys[i].prcParse(child);
            child = child->getNextSibling();
        }
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


/* plMobileOccluder */
void plMobileOccluder::read(hsStream* S, plResManager* mgr)
{
    plOccluder::read(S, mgr);

    fLocalToWorld.read(S);
    fWorldToLocal.read(S);
    fLocalBounds.read(S);
}

void plMobileOccluder::write(hsStream* S, plResManager* mgr)
{
    plOccluder::write(S, mgr);

    fLocalToWorld.write(S);
    fWorldToLocal.write(S);
    fLocalBounds.write(S);
}

void plMobileOccluder::IPrcWrite(pfPrcHelper* prc)
{
    plOccluder::IPrcWrite(prc);

    prc->writeSimpleTag("LocalToWorld");
    fLocalToWorld.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("WorldToLocal");
    fWorldToLocal.prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("LocalBounds");
    fLocalBounds.prcWrite(prc);
    prc->closeTag();
}

void plMobileOccluder::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "LocalToWorld") {
        if (tag->hasChildren())
            fLocalToWorld.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "WorldToLocal") {
        if (tag->hasChildren())
            fWorldToLocal.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "LocalBounds") {
        if (tag->hasChildren())
            fLocalBounds.prcParse(tag->getFirstChild());
    } else {
        plOccluder::IPrcParse(tag, mgr);
    }
}
