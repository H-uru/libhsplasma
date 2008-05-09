#include "hsBounds.h"

/* hsBounds */
hsBounds::hsBounds() : fType(0) { }
hsBounds::~hsBounds() { }

const char* hsBounds::ClassName() { return "hsBounds"; }

void hsBounds::read(hsStream* S) {
    fType = S->readInt();
}

void hsBounds::write(hsStream* S) {
    S->writeInt(fType);
}

void hsBounds::prcWrite(pfPrcHelper* prc) {
    prc->writeSimpleTag(ClassName());
    IPrcWrite(prc);
    prc->closeTag();
}

void hsBounds::IPrcWrite(pfPrcHelper* prc) {
    prc->startTag("BoundsInfo");
    prc->writeParam("Type", fType);
    prc->endTag(true);
}

void hsBounds::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != ClassName())
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    const pfPrcTag* child = tag->getFirstChild();
    while (child != NULL) {
        IPrcParse(child);
        child = child->getNextSibling();
    }
}

void hsBounds::IPrcParse(const pfPrcTag* tag) {
    if (tag->getName() == "BoundsInfo") {
        fType = tag->getParam("Type", "0").toInt();
    } else {
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    }
}

void hsBounds::setType(int type) { fType = type; }


/* hsBounds3 */
hsBounds3::hsBounds3() { }
hsBounds3::~hsBounds3() { }

const char* hsBounds3::ClassName() { return "hsBounds3"; }

void hsBounds3::read(hsStream* S) {
    hsBounds::read(S);
    fMins.read(S);
    fMaxs.read(S);
}

void hsBounds3::write(hsStream* S) {
    hsBounds::write(S);
    fMins.write(S);
    fMaxs.write(S);
}

void hsBounds3::IPrcWrite(pfPrcHelper* prc) {
    hsBounds::IPrcWrite(prc);
    prc->writeSimpleTag("Mins");
    fMins.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Maxs");
    fMaxs.prcWrite(prc);
    prc->closeTag();
}

void hsBounds3::IPrcParse(const pfPrcTag* tag) {
    if (tag->getName() == "Mins") {
        if (tag->hasChildren())
            fMins.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "Maxs") {
        if (tag->hasChildren())
            fMaxs.prcParse(tag->getFirstChild());
    } else {
        hsBounds::IPrcParse(tag);
    }
}


/* hsBounds3Ext */
hsBounds3Ext::hsBounds3Ext() : fExtFlags(0), fRadius(0.0f) { }

hsBounds3Ext::hsBounds3Ext(const hsBounds3Ext& src) : hsBounds3() {
    fType = src.fType;
    fMins = src.fMins;
    fMaxs = src.fMaxs;
    fCenter = src.fCenter;
    fExtFlags = src.fExtFlags;
    fCorner = src.fCorner;
    fRadius = src.fRadius;
    for (int i=0; i<3; i++) {
        fAxes[i] = src.fAxes[i];
        fDists[i].X = src.fDists[i].X;
        fDists[i].Y = src.fDists[i].Y;
    }
}

hsBounds3Ext::~hsBounds3Ext() { }

const char* hsBounds3Ext::ClassName() { return "hsBounds3Ext"; }

void hsBounds3Ext::read(hsStream* S) {
    fExtFlags = S->readInt();
    hsBounds3::read(S);
    if (!(fExtFlags & kAxisAligned)) {
        fCorner.read(S);
        for (int i=0; i<3; i++) {
            fAxes[i].read(S);
            fDists[i].X = S->readFloat();
            fDists[i].Y = S->readFloat();
        }
    }
}

void hsBounds3Ext::write(hsStream* S) {
    S->writeInt(fExtFlags);
    hsBounds3::write(S);
    if (!(fExtFlags & kAxisAligned)) {
        fCorner.write(S);
        for (int i=0; i<3; i++) {
            fAxes[i].write(S);
            S->writeFloat(fDists[i].X);
            S->writeFloat(fDists[i].Y);
        }
    }
}

void hsBounds3Ext::IPrcWrite(pfPrcHelper* prc) {
    hsBounds3::IPrcWrite(prc);
    prc->startTag("ExtFlags");
    prc->writeParamHex("value", fExtFlags);
    prc->endTag(true);
    if (!(fExtFlags & kAxisAligned)) {
        prc->writeSimpleTag("Corner");
        fCorner.prcWrite(prc);
        prc->closeTag();
        prc->writeSimpleTag("Axes");
        for (int i=0; i<3; i++) {
            prc->startTag("Axis");
            prc->writeParam("DistX", fDists[i].X);
            prc->writeParam("DistY", fDists[i].Y);
            prc->endTag();
            fAxes[i].prcWrite(prc);
            prc->closeTag();
        }
        prc->closeTag();
    }
}

void hsBounds3Ext::IPrcParse(const pfPrcTag* tag) {
    if (tag->getName() == "ExtFlags") {
        fExtFlags = tag->getParam("value", "0").toUint();
    } else if (tag->getName() == "Corner") {
        if (tag->hasChildren())
            fCorner.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "Axes") {
        const pfPrcTag* child = tag->getFirstChild();
        for (int i=0; i<3 && child != NULL; i++) {
            if (child->getName() != "Axis")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());

            fDists[i].X = child->getParam("DistX", "0").toFloat();
            fDists[i].Y = child->getParam("DistY", "0").toFloat();
            if (child->hasChildren())
                fAxes[i].prcParse(child->getFirstChild());
            
            child = child->getNextSibling();
        }
    } else {
        hsBounds3::IPrcParse(tag);
    }
}


/* hsBoundsOriented */
hsBoundsOriented::hsBoundsOriented() : fCenterValid(0), fPlanes(NULL),
                                       fNumPlanes(0) { }

hsBoundsOriented::~hsBoundsOriented() {
    if (fPlanes != NULL)
        delete[] fPlanes;
}

const char* hsBoundsOriented::ClassName() { return "hsBoundsOriented"; }

void hsBoundsOriented::read(hsStream* S) {
    hsBounds::read(S);
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
    hsBounds::write(S);
    fCenter.write(S);
    S->writeInt(fCenterValid);
    S->writeInt(fNumPlanes);
    for (unsigned int i=0; i<fNumPlanes; i++)
        fPlanes[i].write(S);
}

void hsBoundsOriented::IPrcWrite(pfPrcHelper* prc) {
    hsBounds::IPrcWrite(prc);
    prc->startTag("Center");
    prc->writeParam("IsValid", fCenterValid);
    prc->endTag();
      fCenter.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Planes");
    for (unsigned int i=0; i<fNumPlanes; i++)
        fPlanes[i].prcWrite(prc);
    prc->closeTag();
}

void hsBoundsOriented::IPrcParse(const pfPrcTag* tag) {
    if (tag->getName() == "Center") {
        fCenterValid = tag->getParam("IsValid", "false").toBool();
        if (tag->hasChildren())
            fCenter.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "Planes") {
        if (fPlanes != NULL)
            delete[] fPlanes;
        fNumPlanes = tag->countChildren();
        fPlanes = new hsPlane3[fNumPlanes];
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fNumPlanes; i++) {
            fPlanes[i].prcParse(child);
            child = child->getNextSibling();
        }
    } else {
        hsBounds::IPrcParse(tag);
    }
}
