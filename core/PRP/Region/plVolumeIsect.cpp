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

#include "plVolumeIsect.h"

/* plBoundsIsect */
void plBoundsIsect::read(hsStream* S, plResManager* mgr)
{
    fLocalBounds.read(S);
    fWorldBounds.read(S);
}

void plBoundsIsect::write(hsStream* S, plResManager* mgr)
{
    fLocalBounds.write(S);
    fWorldBounds.write(S);
}

void plBoundsIsect::IPrcWrite(pfPrcHelper* prc)
{
    prc->writeSimpleTag("LocalBounds");
    fLocalBounds.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("WorldBounds");
    fWorldBounds.prcWrite(prc);
    prc->closeTag();
}

void plBoundsIsect::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "LocalBounds") {
        if (tag->hasChildren())
            fLocalBounds.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "WorldBounds") {
        if (tag->hasChildren())
            fWorldBounds.prcParse(tag->getFirstChild());
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}


/* plConeIsect */
void plConeIsect::read(hsStream* S, plResManager* mgr)
{
    fCapped = S->readInt();
    fRadAngle = S->readFloat();
    fLength = S->readFloat();
    fWorldTip.read(S);
    fWorldNorm.read(S);
    fWorldToNDC.read(S);
    fLightToNDC.read(S);

    size_t count = 4 + (fCapped != 0 ? 1 : 0);
    for (size_t i=0; i<count; i++) {
        fNorms[i].read(S);
        fDists[i] = S->readFloat();
    }
}

void plConeIsect::write(hsStream* S, plResManager* mgr)
{
    S->writeInt(fCapped);
    S->writeFloat(fRadAngle);
    S->writeFloat(fLength);
    fWorldTip.write(S);
    fWorldNorm.write(S);
    fWorldToNDC.write(S);
    fLightToNDC.write(S);

    size_t count = 4 + (fCapped != 0 ? 1 : 0);
    for (size_t i=0; i<count; i++) {
        fNorms[i].write(S);
        S->writeFloat(fDists[i]);
    }
}

void plConeIsect::IPrcWrite(pfPrcHelper* prc)
{
    prc->startTag("ConeParams");
    prc->writeParam("Capped", fCapped);
    prc->writeParam("RadAngle", fRadAngle);
    prc->writeParam("Length", fLength);
    prc->endTag(true);

    prc->writeSimpleTag("WorldTip");
    fWorldTip.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("WorldNorm");
    fWorldNorm.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("WorldToNDC");
    fWorldToNDC.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("LightToNDC");
    fLightToNDC.prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Norms");
    size_t count = 4 + (fCapped != 0 ? 1 : 0);
    for (size_t i=0; i<count; i++) {
        prc->startTag("Normal");
        prc->writeParam("Distance", fDists[i]);
        prc->endTag();
        fNorms[i].prcWrite(prc);
        prc->closeTag();;
    }
    prc->closeTag();
}

void plConeIsect::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "ConeParams") {
        fCapped = tag->getParam("Capped", "0").to_int();
        fRadAngle = tag->getParam("RadAngle", "0").to_float();
        fLength = tag->getParam("Length", "0").to_float();
    } else if (tag->getName() == "WorldTip") {
        if (tag->hasChildren())
            fWorldTip.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "WorldNorm") {
        if (tag->hasChildren())
            fWorldNorm.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "WorldToNDC") {
        if (tag->hasChildren())
            fWorldToNDC.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "LightToNDC") {
        if (tag->hasChildren())
            fLightToNDC.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "Norms") {
        size_t count = 4 + (fCapped != 0 ? 1 : 0);
        if (tag->countChildren() != count)
            throw pfPrcTagException(__FILE__, __LINE__, "Incorrect number of Norms");
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<count; i++) {
            if (child->getName() != "Normal")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            fDists[i] = child->getParam("Distance", "0").to_float();
            if (child->hasChildren())
                fNorms[i].prcParse(child->getFirstChild());
            child = child->getNextSibling();
        }
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}


/* plConvexIsect::SinglePlane */
void plConvexIsect::SinglePlane::read(hsStream* S)
{
    fNorm.read(S);
    fPos.read(S);
    fDist = S->readFloat();
    fWorldNorm.read(S);
    fWorldDist = S->readFloat();
}

void plConvexIsect::SinglePlane::write(hsStream* S)
{
    fNorm.write(S);
    fPos.write(S);
    S->writeFloat(fDist);
    fWorldNorm.write(S);
    S->writeFloat(fWorldDist);
}

void plConvexIsect::SinglePlane::prcWrite(pfPrcHelper* prc)
{
    prc->startTag("SinglePlane");
    prc->writeParam("Dist", fDist);
    prc->writeParam("WorldDist", fWorldDist);
    prc->endTag();
    prc->writeSimpleTag("Normal");
    fNorm.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Position");
    fPos.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("WorldNormal");
    fWorldNorm.prcWrite(prc);
    prc->closeTag();
    prc->closeTag();
}

void plConvexIsect::SinglePlane::prcParse(const pfPrcTag* tag)
{
    if (tag->getName() != "SinglePlane")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    fDist = tag->getParam("Dist", "0").to_float();
    fWorldDist = tag->getParam("WorldDist", "0").to_float();

    const pfPrcTag* child = tag->getFirstChild();
    while (child) {
        if (child->getName() == "Normal") {
            if (child->hasChildren())
                fNorm.prcParse(child->getFirstChild());
        } else if (child->getName() == "Position") {
            if (child->hasChildren())
                fPos.prcParse(child->getFirstChild());
        } else if (child->getName() == "WorldNormal") {
            if (child->hasChildren())
                fWorldNorm.prcParse(child->getFirstChild());
        } else {
            throw pfPrcTagException(__FILE__, __LINE__, child->getName());
        }
        child = child->getNextSibling();
    }
}


/* plConvexIsect */
void plConvexIsect::read(hsStream* S, plResManager* mgr)
{
    fPlanes.resize(S->readShort());
    for (size_t i=0; i<fPlanes.size(); i++) {
        fPlanes[i].read(S);
    }
}

void plConvexIsect::write(hsStream* S, plResManager* mgr)
{
    S->writeShort(fPlanes.size());
    for (size_t i=0; i<fPlanes.size(); i++) {
        fPlanes[i].write(S);
    }
}

void plConvexIsect::IPrcWrite(pfPrcHelper* prc)
{
    prc->writeSimpleTag("Planes");
    for (size_t i=0; i<fPlanes.size(); i++) {
        fPlanes[i].prcWrite(prc);
    }
    prc->closeTag(); // Planes
}

void plConvexIsect::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Planes") {
        fPlanes.resize(tag->countChildren());
        const pfPrcTag* planeChild = tag->getFirstChild();
        for (size_t i=0; i<fPlanes.size(); i++) {
            fPlanes[i].prcParse(planeChild);
            planeChild = planeChild->getNextSibling();
        }
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

void plConvexIsect::addPlane(hsVector3 normal, const hsVector3& pos)
{
    normal.normalize();

    // Check to see if we already have this plane -- if so, make sure that we have the outermost
    // point associated with it
    for (SinglePlane& i : fPlanes) {
        if (i.getNorm().dotP(normal) >= 0.9998f) {
            float dist = normal.dotP(pos);
            if (dist > i.getDist()) {
                i.setDist(dist);
                i.setPos(pos);
            }
            return;
        }
    }

    SinglePlane plane;
    plane.setNorm(normal);
    plane.setPos(pos);
    plane.setDist(normal.dotP(pos));
    plane.setWorldNorm(normal);
    plane.setWorldDist(plane.getDist());
    fPlanes.push_back(plane);
}

void plConvexIsect::transform(const hsMatrix44& localToWorld, const hsMatrix44& worldToLocal)
{
    for (SinglePlane& i : fPlanes) {
        hsVector3 worldNorm = worldToLocal.multVector(i.getNorm());
        worldNorm.normalize();
        i.setWorldNorm(worldNorm);

        hsVector3 pos = localToWorld.multPoint(i.getPos());
        i.setWorldDist(i.getWorldNorm().dotP(pos));
    }
}

/* plCylinderIsect */
void plCylinderIsect::read(hsStream* S, plResManager* mgr)
{
    fTop.read(S);
    fBot.read(S);
    fRadius = S->readFloat();
    fWorldBot.read(S);
    fWorldNorm.read(S);
    fLength = S->readFloat();
    fMin = S->readFloat();
    fMax = S->readFloat();
}

void plCylinderIsect::write(hsStream* S, plResManager* mgr)
{
    fTop.write(S);
    fBot.write(S);
    S->writeFloat(fRadius);
    fWorldBot.write(S);
    fWorldNorm.write(S);
    S->writeFloat(fLength);
    S->writeFloat(fMin);
    S->writeFloat(fMax);
}

void plCylinderIsect::IPrcWrite(pfPrcHelper* prc)
{
    prc->startTag("CylinderParams");
    prc->writeParam("Radius", fRadius);
    prc->writeParam("Length", fLength);
    prc->writeParam("Min", fMin);
    prc->writeParam("Max", fMax);
    prc->endTag(true);

    prc->writeSimpleTag("Top");
    fTop.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Bottom");
    fBot.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("WorldBottom");
    fWorldBot.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("WorldNorm");
    fWorldNorm.prcWrite(prc);
    prc->closeTag();
}

void plCylinderIsect::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "CylinderParams") {
        fRadius = tag->getParam("Radius", "0").to_float();
        fLength = tag->getParam("Length", "0").to_float();
        fMin = tag->getParam("Min", "0").to_float();
        fMax = tag->getParam("Max", "0").to_float();
    } else if (tag->getName() == "Top") {
        if (tag->hasChildren())
            fTop.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "Bottom") {
        if (tag->hasChildren())
            fBot.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "WorldBottom") {
        if (tag->hasChildren())
            fWorldBot.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "WorldNorm") {
        if (tag->hasChildren())
            fWorldNorm.prcParse(tag->getFirstChild());
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}


/* plParallelIsect */
void plParallelIsect::read(hsStream* S, plResManager* mgr)
{
    fPlanes.resize(S->readShort());
    for (size_t i=0; i<fPlanes.size(); i++) {
        fPlanes[i].fNorm.read(S);
        fPlanes[i].fMin = S->readFloat();
        fPlanes[i].fMax = S->readFloat();
        fPlanes[i].fPosOne.read(S);
        fPlanes[i].fPosTwo.read(S);
    }
}

void plParallelIsect::write(hsStream* S, plResManager* mgr)
{
    S->writeShort(fPlanes.size());
    for (size_t i=0; i<fPlanes.size(); i++) {
        fPlanes[i].fNorm.write(S);
        S->writeFloat(fPlanes[i].fMin);
        S->writeFloat(fPlanes[i].fMax);
        fPlanes[i].fPosOne.write(S);
        fPlanes[i].fPosTwo.write(S);
    }
}

void plParallelIsect::IPrcWrite(pfPrcHelper* prc)
{
    prc->writeSimpleTag("Planes");
    for (size_t i=0; i<fPlanes.size(); i++) {
        prc->startTag("ParallelPlane");
        prc->writeParam("Min", fPlanes[i].fMin);
        prc->writeParam("Max", fPlanes[i].fMax);
        prc->endTag();
          prc->writeSimpleTag("Normal");
          fPlanes[i].fNorm.prcWrite(prc);
          prc->closeTag();
          prc->writeSimpleTag("Positions");
          fPlanes[i].fPosOne.prcWrite(prc);
          fPlanes[i].fPosTwo.prcWrite(prc);
          prc->closeTag();
        prc->closeTag();
    }
    prc->closeTag(); // Planes
}

void plParallelIsect::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Planes") {
        fPlanes.resize(tag->countChildren());
        const pfPrcTag* planeChild = tag->getFirstChild();
        for (size_t i=0; i<fPlanes.size(); i++) {
            if (planeChild->getName() != "ParallelPlane")
                throw pfPrcTagException(__FILE__, __LINE__, planeChild->getName());
            fPlanes[i].fMin = planeChild->getParam("Min", "0").to_float();
            fPlanes[i].fMax = planeChild->getParam("Max", "0").to_float();

            const pfPrcTag* child = planeChild->getFirstChild();
            while (child) {
                if (child->getName() == "Normal") {
                    if (child->hasChildren())
                        fPlanes[i].fNorm.prcParse(child->getFirstChild());
                } else if (child->getName() == "Positions") {
                    if (child->countChildren() != 2)
                        throw pfPrcParseException(__FILE__, __LINE__, "ParallelPlane expects exactly 2 posiitons");
                    fPlanes[i].fPosOne.prcParse(child->getFirstChild());
                    fPlanes[i].fPosTwo.prcParse(child->getFirstChild()->getNextSibling());
                } else {
                    throw pfPrcTagException(__FILE__, __LINE__, child->getName());
                }
                child = child->getNextSibling();
            }
            planeChild = planeChild->getNextSibling();
        }
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}


/* plSphereIsect */
void plSphereIsect::read(hsStream* S, plResManager* mgr)
{
    fCenter.read(S);
    fWorldCenter.read(S);
    fRadius = S->readFloat();
    fMins.read(S);
    fMaxs.read(S);
}

void plSphereIsect::write(hsStream* S, plResManager* mgr)
{
    fCenter.write(S);
    fWorldCenter.write(S);
    S->writeFloat(fRadius);
    fMins.write(S);
    fMaxs.write(S);
}

void plSphereIsect::IPrcWrite(pfPrcHelper* prc)
{
    prc->startTag("SphereParams");
    prc->writeParam("Radius", fRadius);
    prc->endTag(true);

    prc->writeSimpleTag("Center");
    fCenter.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("WorldCenter");
    fWorldCenter.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Mins");
    fMins.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Maxs");
    fMaxs.prcWrite(prc);
    prc->closeTag();
}

void plSphereIsect::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "SphereParams") {
        fRadius = tag->getParam("Radius", "0").to_float();
    } else if (tag->getName() == "Center") {
        if (tag->hasChildren())
            fCenter.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "WorldCenter") {
        if (tag->hasChildren())
            fWorldCenter.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "Mins") {
        if (tag->hasChildren())
            fMins.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "Maxs") {
        if (tag->hasChildren())
            fMaxs.prcParse(tag->getFirstChild());
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}


/* plComplexIsect */
plComplexIsect::~plComplexIsect()
{
    for (auto vol = fVolumes.begin(); vol != fVolumes.end(); ++vol)
        delete *vol;
}

void plComplexIsect::read(hsStream* S, plResManager* mgr)
{
    clearVolumes();
    fVolumes.resize(S->readShort());
    for (size_t i=0; i<fVolumes.size(); i++)
        fVolumes[i] = mgr->ReadCreatableC<plVolumeIsect>(S);
}

void plComplexIsect::write(hsStream* S, plResManager* mgr)
{
    S->writeShort(fVolumes.size());
    for (size_t i=0; i<fVolumes.size(); i++)
        mgr->WriteCreatable(S, fVolumes[i]);
}

void plComplexIsect::IPrcWrite(pfPrcHelper* prc)
{
    prc->writeSimpleTag("Volumes");
    for (size_t i=0; i<fVolumes.size(); i++)
        fVolumes[i]->prcWrite(prc);
    prc->closeTag();
}

void plComplexIsect::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Volumes") {
        clearVolumes();
        fVolumes.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fVolumes.size(); i++) {
            fVolumes[i] = mgr->prcParseCreatableC<plVolumeIsect>(child);
            child = child->getNextSibling();
        }
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

void plComplexIsect::clearVolumes()
{
    for (auto vol = fVolumes.begin(); vol != fVolumes.end(); ++vol)
        delete *vol;
    fVolumes.clear();
}
