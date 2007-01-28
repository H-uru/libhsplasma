#include "hsBounds.h"

/* hsBounds */
hsBounds::hsBounds() : fType(0) { }
hsBounds::~hsBounds() { }

void hsBounds::read(hsStream *S) {
    fType = S->readInt();
}

void hsBounds::write(hsStream *S) {
    S->writeInt(fType);
}


/* hsBounds3 */
hsBounds3::hsBounds3() { }
hsBounds3::~hsBounds3() { }

void hsBounds3::read(hsStream *S) {
    hsBounds::read(S);
    fMins.read(S);
    fMaxs.read(S);
}

void hsBounds3::write(hsStream *S) {
    hsBounds::write(S);
    fMins.write(S);
    fMaxs.write(S);
}


/* hsBounds3Ext */
hsBounds3Ext::hsBounds3Ext() : fExtFlags(0), fRadius(0.0f) { }
hsBounds3Ext::~hsBounds3Ext() { }

void hsBounds3Ext::read(hsStream *S) {
    fExtFlags = S->readInt();
    hsBounds3::read(S);
    if (fExtFlags & kAxisAligned) {
        fCorner.read(S);
        for (int i=0; i<3; i++) {
            fAxes[i].read(S);
            fDists[i].X = S->readFloat();
            fDists[i].Y = S->readFloat();
        }
    }
}

void hsBounds3Ext::write(hsStream *S) {
    S->writeInt(fExtFlags);
    hsBounds3::write(S);
    if (fExtFlags & kAxisAligned) {
        fCorner.write(S);
        for (int i=0; i<3; i++) {
            fAxes[i].write(S);
            S->writeFloat(fDists[i].X);
            S->writeFloat(fDists[i].Y);
        }
    }
}

/* hsBoundsOriented */
hsBoundsOriented::hsBoundsOriented() : fCenterValid(0), fPlanes(NULL),
                                       fNumPlanes(0) { }

hsBoundsOriented::~hsBoundsOriented() {
    if (fPlanes != NULL)
        delete[] fPlanes;
}

void hsBoundsOriented::read(hsStream* S) {
    fType = S->readInt();
    fCenter.read(S);
    fCenterValid = S->readInt();
    fNumPlanes = S->readInt();
    if (fPlanes != NULL)
        delete[] fPlanes;
    fPlanes = new hsPlane3[fNumPlanes];
    for (unsigned int i=0; i<fNumPlanes; i++)
        fPlanes[i].read(S);
}

void hsBoundsOriented::write(hsStream* S) {
    S->writeInt(fType);
    fCenter.write(S);
    S->writeInt(fCenterValid);
    S->writeInt(fNumPlanes);
    for (unsigned int i=0; i<fNumPlanes; i++)
        fPlanes[i].write(S);
}
