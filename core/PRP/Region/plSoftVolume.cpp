#include "plSoftVolume.h"

/* plSoftVolume */
plSoftVolume::plSoftVolume()
            : fListenState(kListenNone), fInsideStrength(0.0f),
              fOutsideStrength(0.0f) { }

void plSoftVolume::read(hsStream* S, plResManager* mgr) {
    plObjInterface::read(S, mgr);

    fListenState = S->readInt();
    fInsideStrength = S->readFloat();
    fOutsideStrength = S->readFloat();
}

void plSoftVolume::write(hsStream* S, plResManager* mgr) {
    plObjInterface::write(S, mgr);

    S->writeInt(fListenState);
    S->writeFloat(fInsideStrength);
    S->writeFloat(fOutsideStrength);
}

void plSoftVolume::IPrcWrite(pfPrcHelper* prc) {
    plObjInterface::IPrcWrite(prc);

    prc->startTag("SoftVolumeParams");
    prc->writeParam("ListenState", fListenState);
    prc->writeParam("InsideStrength", fInsideStrength);
    prc->writeParam("OutsideStrength", fOutsideStrength);
    prc->endTag(true);
}

void plSoftVolume::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "SoftVolumeParams") {
        fListenState = tag->getParam("ListenState", "0").toUint();
        fInsideStrength = tag->getParam("InsideStrength", "0").toFloat();
        fOutsideStrength = tag->getParam("OutsideStrength", "0").toFloat();
    } else {
        plObjInterface::IPrcParse(tag, mgr);
    }
}


/* plSoftVolumeSimple */
plSoftVolumeSimple::plSoftVolumeSimple() : fVolume(NULL), fSoftDist(0.0f) { }

plSoftVolumeSimple::~plSoftVolumeSimple() {
    delete fVolume;
}

void plSoftVolumeSimple::read(hsStream* S, plResManager* mgr) {
    plSoftVolume::read(S, mgr);

    fSoftDist = S->readFloat();
    setVolume(plVolumeIsect::Convert(mgr->ReadCreatable(S)));
}

void plSoftVolumeSimple::write(hsStream* S, plResManager* mgr) {
    plSoftVolume::write(S, mgr);

    S->writeFloat(fSoftDist);
    mgr->WriteCreatable(S, fVolume);
}

void plSoftVolumeSimple::IPrcWrite(pfPrcHelper* prc) {
    plSoftVolume::IPrcWrite(prc);

    prc->startTag("Volume");
    prc->writeParam("SoftDist", fSoftDist);
    prc->endTag();
    fVolume->prcWrite(prc);
    prc->closeTag();
}

void plSoftVolumeSimple::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Volume") {
        fSoftDist = tag->getParam("SoftDist", "0").toFloat();
        if (tag->hasChildren())
            setVolume(plVolumeIsect::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
    } else {
        plSoftVolume::IPrcParse(tag, mgr);
    }
}

void plSoftVolumeSimple::setVolume(plVolumeIsect* vol) {
    delete fVolume;
    fVolume = vol;
}


/* plSoftVolumeComplex */
void plSoftVolumeComplex::read(hsStream* S, plResManager* mgr) {
    plSoftVolume::read(S, mgr);

    fSubVolumes.setSize(S->readInt());
    for (size_t i=0; i<fSubVolumes.getSize(); i++)
        fSubVolumes[i] = mgr->readKey(S);
}

void plSoftVolumeComplex::write(hsStream* S, plResManager* mgr) {
    plSoftVolume::write(S, mgr);

    S->writeInt(fSubVolumes.getSize());
    for (size_t i=0; i<fSubVolumes.getSize(); i++)
        mgr->writeKey(S, fSubVolumes[i]);
}

void plSoftVolumeComplex::IPrcWrite(pfPrcHelper* prc) {
    plSoftVolume::IPrcWrite(prc);

    prc->writeSimpleTag("SubVolumes");
    for (size_t i=0; i<fSubVolumes.getSize(); i++)
        fSubVolumes[i]->prcWrite(prc);
    prc->closeTag();
}

void plSoftVolumeComplex::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "SubVolumes") {
        fSubVolumes.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fSubVolumes.getSize(); i++) {
            fSubVolumes[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        plSoftVolume::IPrcParse(tag, mgr);
    }
}
