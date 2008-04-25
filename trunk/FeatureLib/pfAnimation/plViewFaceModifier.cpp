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

    prc->writeSimpleTag("OrigTransforms");
    fLocalToParent.prcWrite(prc);
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
