#include "plViewFaceModifier.h"

plViewFaceModifier::plViewFaceModifier() {
    fFlags.setName(kPivotFace, "kPivotFace");
    fFlags.setName(kPivotFavorY, "kPivotFavorY");
    fFlags.setName(kPivotY, "kPivotY");
    fFlags.setName(kPivotTumple, "kPivotTumple");
    fFlags.setName(kScale, "kScale");
    fFlags.setName(kFaceCam, "kFaceCam");
    fFlags.setName(kFaceList, "kFaceList");
    fFlags.setName(kFacePlay, "kFacePlay");
    fFlags.setName(kFaceObj, "kFaceObj");
    fFlags.setName(kOffset, "kOffset");
    fFlags.setName(kOffsetLocal, "kOffsetLocal");
    fFlags.setName(kMaxBounds, "kMaxBounds");
}

plViewFaceModifier::~plViewFaceModifier() { }

IMPLEMENT_CREATABLE(plViewFaceModifier, kViewFaceModifier, plSingleModifier)

void plViewFaceModifier::read(hsStream* S, plResManager* mgr) {
    plSingleModifier::read(S, mgr);

    fScale.read(S);
    fLocalToParent.read(S);
    fParentToLocal.read(S);
    if (fFlags[kFaceObj])
        fFaceObj = mgr->readKey(S);
    fOffset.read(S);
    if (fFlags[kMaxBounds])
        fMaxBounds.read(S);
}

void plViewFaceModifier::write(hsStream* S, plResManager* mgr) {
    plSingleModifier::write(S, mgr);

    fScale.write(S);
    fLocalToParent.write(S);
    fParentToLocal.write(S);
    if (fFlags[kFaceObj])
        mgr->writeKey(S, fFaceObj);
    fOffset.write(S);
    if (fFlags[kMaxBounds])
        fMaxBounds.write(S);
}

void plViewFaceModifier::IPrcWrite(pfPrcHelper* prc) {
    plSingleModifier::IPrcWrite(prc);

    prc->writeSimpleTag("Scale");
    fScale.prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("LocalToParent");
    fLocalToParent.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("ParentToLocal");
    fParentToLocal.prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Offset");
    fOffset.prcWrite(prc);
    prc->closeTag();

    if (fFlags[kFaceObj]) {
        prc->writeSimpleTag("FaceObj");
        fFaceObj->prcWrite(prc);
        prc->closeTag();
    }

    if (fFlags[kMaxBounds]) {
        prc->writeSimpleTag("MaxBounds");
        fMaxBounds.prcWrite(prc);
        prc->closeTag();
    }
}

void plViewFaceModifier::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Scale") {
        if (tag->hasChildren())
            fScale.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "LocalToParent") {
        if (tag->hasChildren())
            fLocalToParent.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "ParentToLocal") {
        if (tag->hasChildren())
            fParentToLocal.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "Offset") {
        if (tag->hasChildren())
            fOffset.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "FaceObj") {
        if (tag->hasChildren())
            fFaceObj = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "MaxBounds") {
        if (tag->hasChildren())
            fMaxBounds.prcParse(tag->getFirstChild());
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}

hsVector3 plViewFaceModifier::getScale() const { return fScale; }
hsVector3 plViewFaceModifier::getOffset() const { return fOffset; }
hsMatrix44 plViewFaceModifier::getLocalToParent() const { return fLocalToParent; }
hsMatrix44 plViewFaceModifier::getParentToLocal() const { return fParentToLocal; }
plKey plViewFaceModifier::getFaceObj() const { return fFaceObj; }
hsBounds3Ext plViewFaceModifier::getMaxBounds() const { return fMaxBounds; }

void plViewFaceModifier::setScale(const hsVector3& scale) { fScale = scale; }
void plViewFaceModifier::setOffset(const hsVector3& offset) { fOffset = offset; }
void plViewFaceModifier::setLocalToParent(const hsMatrix44& l2p) { fLocalToParent = l2p; }
void plViewFaceModifier::setParentToLocal(const hsMatrix44& p2l) { fParentToLocal = p2l; }
void plViewFaceModifier::setFaceObj(plKey obj) { fFaceObj = obj; }
void plViewFaceModifier::setMaxBounds(const hsBounds3Ext& bounds) { fMaxBounds = bounds; }
