#include "plVolumeIsect.h"

/* plVolumeIsect */
plVolumeIsect::plVolumeIsect() { }
plVolumeIsect::~plVolumeIsect() { }

IMPLEMENT_CREATABLE(plVolumeIsect, kVolumeIsect, plCreatable)


/* plBoundsIsect */
plBoundsIsect::plBoundsIsect() { }
plBoundsIsect::~plBoundsIsect() { }

IMPLEMENT_CREATABLE(plBoundsIsect, kBoundsIsect, plVolumeIsect)

void plBoundsIsect::read(hsStream* S, plResManager* mgr) {
    fLocalBounds.read(S);
    fWorldBounds.read(S);
}

void plBoundsIsect::write(hsStream* S, plResManager* mgr) {
    fLocalBounds.write(S);
    fWorldBounds.write(S);
}

void plBoundsIsect::IPrcWrite(pfPrcHelper* prc) {
    prc->writeSimpleTag("LocalBounds");
    fLocalBounds.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("WorldBounds");
    fWorldBounds.prcWrite(prc);
    prc->closeTag();
}

void plBoundsIsect::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
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
plConeIsect::plConeIsect() { }
plConeIsect::~plConeIsect() { }

IMPLEMENT_CREATABLE(plConeIsect, kConeIsect, plVolumeIsect)

void plConeIsect::read(hsStream* S, plResManager* mgr) {
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

void plConeIsect::write(hsStream* S, plResManager* mgr) {
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

void plConeIsect::IPrcWrite(pfPrcHelper* prc) {
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

void plConeIsect::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "ConeParams") {
        fCapped = tag->getParam("Capped", "0").toInt();
        fRadAngle = tag->getParam("RadAngle", "0").toFloat();
        fLength = tag->getParam("Length", "0").toFloat();
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
            fDists[i] = child->getParam("Distance", "0").toFloat();
            if (child->hasChildren())
                fNorms[i].prcParse(child->getFirstChild());
            child = child->getNextSibling();
        }
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}


/* plConvexIsect */
plConvexIsect::plConvexIsect() { }
plConvexIsect::~plConvexIsect() { }

IMPLEMENT_CREATABLE(plConvexIsect, kConvexIsect, plVolumeIsect)

void plConvexIsect::read(hsStream* S, plResManager* mgr) {
    fPlanes.setSize(S->readShort());
    for (size_t i=0; i<fPlanes.getSize(); i++) {
        fPlanes[i].fNorm.read(S);
        fPlanes[i].fPos.read(S);
        fPlanes[i].fDist = S->readFloat();
        fPlanes[i].fWorldNorm.read(S);
        fPlanes[i].fWorldDist = S->readFloat();
    }
}

void plConvexIsect::write(hsStream* S, plResManager* mgr) {
    S->writeShort(fPlanes.getSize());
    for (size_t i=0; i<fPlanes.getSize(); i++) {
        fPlanes[i].fNorm.write(S);
        fPlanes[i].fPos.write(S);
        S->writeFloat(fPlanes[i].fDist);
        fPlanes[i].fWorldNorm.write(S);
        S->writeFloat(fPlanes[i].fWorldDist);
    }
}

void plConvexIsect::IPrcWrite(pfPrcHelper* prc) {
    prc->writeSimpleTag("Planes");
    for (size_t i=0; i<fPlanes.getSize(); i++) {
        prc->startTag("SinglePlane");
        prc->writeParam("Dist", fPlanes[i].fDist);
        prc->writeParam("WorldDist", fPlanes[i].fWorldDist);
        prc->endTag();
          prc->writeSimpleTag("Normal");
          fPlanes[i].fNorm.prcWrite(prc);
          prc->closeTag();
          prc->writeSimpleTag("Position");
          fPlanes[i].fPos.prcWrite(prc);
          prc->closeTag();
          prc->writeSimpleTag("WorldNormal");
          fPlanes[i].fWorldNorm.prcWrite(prc);
          prc->closeTag();
        prc->closeTag();
    }
    prc->closeTag(); // Planes
}

void plConvexIsect::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Planes") {
        fPlanes.setSize(tag->countChildren());
        const pfPrcTag* planeChild = tag->getFirstChild();
        for (size_t i=0; i<fPlanes.getSize(); i++) {
            if (planeChild->getName() != "SinglePlane")
                throw pfPrcTagException(__FILE__, __LINE__, planeChild->getName());
            fPlanes[i].fDist = planeChild->getParam("Dist", "0").toFloat();
            fPlanes[i].fWorldDist = planeChild->getParam("WorldDist", "0").toFloat();

            const pfPrcTag* child = planeChild->getFirstChild();
            while (child != NULL) {
                if (child->getName() == "Normal") {
                    if (child->hasChildren())
                        fPlanes[i].fNorm.prcParse(child->getFirstChild());
                } else if (child->getName() == "Position") {
                    if (child->hasChildren())
                        fPlanes[i].fPos.prcParse(child->getFirstChild());
                } else if (child->getName() == "WorldNormal") {
                    if (child->hasChildren())
                        fPlanes[i].fWorldNorm.prcParse(child->getFirstChild());
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


/* plCylinderIsect */
plCylinderIsect::plCylinderIsect() { }
plCylinderIsect::~plCylinderIsect() { }

IMPLEMENT_CREATABLE(plCylinderIsect, kCylinderIsect, plVolumeIsect)

void plCylinderIsect::read(hsStream* S, plResManager* mgr) {
    fTop.read(S);
    fBot.read(S);
    fRadius = S->readFloat();
    fWorldBot.read(S);
    fWorldNorm.read(S);
    fLength = S->readFloat();
    fMin = S->readFloat();
    fMax = S->readFloat();
}

void plCylinderIsect::write(hsStream* S, plResManager* mgr) {
    fTop.write(S);
    fBot.write(S);
    S->writeFloat(fRadius);
    fWorldBot.write(S);
    fWorldNorm.write(S);
    S->writeFloat(fLength);
    S->writeFloat(fMin);
    S->writeFloat(fMax);
}

void plCylinderIsect::IPrcWrite(pfPrcHelper* prc) {
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

void plCylinderIsect::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "CylinderParams") {
        fRadius = tag->getParam("Radius", "0").toFloat();
        fLength = tag->getParam("Length", "0").toFloat();
        fMin = tag->getParam("Min", "0").toFloat();
        fMax = tag->getParam("Max", "0").toFloat();
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
plParallelIsect::plParallelIsect() { }
plParallelIsect::~plParallelIsect() { }

IMPLEMENT_CREATABLE(plParallelIsect, kParallelIsect, plVolumeIsect)

void plParallelIsect::read(hsStream* S, plResManager* mgr) {
    fPlanes.setSize(S->readShort());
    for (size_t i=0; i<fPlanes.getSize(); i++) {
        fPlanes[i].fNorm.read(S);
        fPlanes[i].fMin = S->readFloat();
        fPlanes[i].fMax = S->readFloat();
        fPlanes[i].fPosOne.read(S);
        fPlanes[i].fPosTwo.read(S);
    }
}

void plParallelIsect::write(hsStream* S, plResManager* mgr) {
    S->writeShort(fPlanes.getSize());
    for (size_t i=0; i<fPlanes.getSize(); i++) {
        fPlanes[i].fNorm.write(S);
        S->writeFloat(fPlanes[i].fMin);
        S->writeFloat(fPlanes[i].fMax);
        fPlanes[i].fPosOne.write(S);
        fPlanes[i].fPosTwo.write(S);
    }
}

void plParallelIsect::IPrcWrite(pfPrcHelper* prc) {
    prc->writeSimpleTag("Planes");
    for (size_t i=0; i<fPlanes.getSize(); i++) {
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

void plParallelIsect::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Planes") {
        fPlanes.setSize(tag->countChildren());
        const pfPrcTag* planeChild = tag->getFirstChild();
        for (size_t i=0; i<fPlanes.getSize(); i++) {
            if (planeChild->getName() != "ParallelPlane")
                throw pfPrcTagException(__FILE__, __LINE__, planeChild->getName());
            fPlanes[i].fMin = planeChild->getParam("Min", "0").toFloat();
            fPlanes[i].fMax = planeChild->getParam("Max", "0").toFloat();

            const pfPrcTag* child = planeChild->getFirstChild();
            while (child != NULL) {
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
plSphereIsect::plSphereIsect() { }
plSphereIsect::~plSphereIsect() { }

IMPLEMENT_CREATABLE(plSphereIsect, kSphereIsect, plVolumeIsect)

void plSphereIsect::read(hsStream* S, plResManager* mgr) {
    fCenter.read(S);
    fWorldCenter.read(S);
    fRadius = S->readFloat();
    fMins.read(S);
    fMaxs.read(S);
}

void plSphereIsect::write(hsStream* S, plResManager* mgr) {
    fCenter.write(S);
    fWorldCenter.write(S);
    S->writeFloat(fRadius);
    fMins.write(S);
    fMaxs.write(S);
}

void plSphereIsect::IPrcWrite(pfPrcHelper* prc) {
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

void plSphereIsect::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "SphereParams") {
        fRadius = tag->getParam("Radius", "0").toFloat();
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
plComplexIsect::plComplexIsect() { }

plComplexIsect::~plComplexIsect() {
    for (size_t i=0; i<fVolumes.getSize(); i++)
        delete fVolumes[i];
}

IMPLEMENT_CREATABLE(plComplexIsect, kComplexIsect, plVolumeIsect)

void plComplexIsect::read(hsStream* S, plResManager* mgr) {
    fVolumes.setSizeNull(S->readShort());
    for (size_t i=0; i<fVolumes.getSize(); i++)
        fVolumes[i] = plVolumeIsect::Convert(mgr->ReadCreatable(S));
}

void plComplexIsect::write(hsStream* S, plResManager* mgr) {
    S->writeShort(fVolumes.getSize());
    for (size_t i=0; i<fVolumes.getSize(); i++)
        mgr->WriteCreatable(S, fVolumes[i]);
}

void plComplexIsect::IPrcWrite(pfPrcHelper* prc) {
    prc->writeSimpleTag("Volumes");
    for (size_t i=0; i<fVolumes.getSize(); i++)
        fVolumes[i]->prcWrite(prc);
    prc->closeTag();
}

void plComplexIsect::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Volumes") {
        fVolumes.setSizeNull(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fVolumes.getSize(); i++) {
            fVolumes[i] = plVolumeIsect::Convert(mgr->prcParseCreatable(child));
            child = child->getNextSibling();
        }
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}


/* plIntersectionIsect */
plIntersectionIsect::plIntersectionIsect() { }
plIntersectionIsect::~plIntersectionIsect() { }

IMPLEMENT_CREATABLE(plIntersectionIsect, kIntersectionIsect, plComplexIsect)


/* plUnionIsect */
plUnionIsect::plUnionIsect() { }
plUnionIsect::~plUnionIsect() { }

IMPLEMENT_CREATABLE(plUnionIsect, kUnionIsect, plComplexIsect)
