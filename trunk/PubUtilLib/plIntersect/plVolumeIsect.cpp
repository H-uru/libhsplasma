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
    prc->endTag();

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

    prc->closeTag(); // ConeParams

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
          prc->writeSimpleTag("Norm");
          fPlanes[i].fNorm.prcWrite(prc);
          prc->closeTag();
          prc->writeSimpleTag("Position");
          fPlanes[i].fPos.prcWrite(prc);
          prc->closeTag();
          prc->writeSimpleTag("WorldNorm");
          fPlanes[i].fWorldNorm.prcWrite(prc);
          prc->closeTag();
        prc->closeTag();
    }
    prc->closeTag(); // Planes
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
    prc->endTag();

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

    prc->closeTag(); // CylinderParams
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
          prc->writeSimpleTag("Norm");
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
    prc->endTag();

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

    prc->closeTag(); // SphereParams
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


/* plIntersectionIsect */
plIntersectionIsect::plIntersectionIsect() { }
plIntersectionIsect::~plIntersectionIsect() { }

IMPLEMENT_CREATABLE(plIntersectionIsect, kIntersectionIsect, plComplexIsect)


/* plUnionIsect */
plUnionIsect::plUnionIsect() { }
plUnionIsect::~plUnionIsect() { }

IMPLEMENT_CREATABLE(plUnionIsect, kUnionIsect, plComplexIsect)
