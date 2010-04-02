#include "plFacingConditionalObject.h"

plFacingConditionalObject::plFacingConditionalObject()
                         : fTolerance(0.0f), fDirectional(false) { }

void plFacingConditionalObject::read(hsStream* S, plResManager* mgr) {
    plConditionalObject::read(S, mgr);
    fTolerance = S->readFloat();
    fDirectional = S->readBool();
}

void plFacingConditionalObject::write(hsStream* S, plResManager* mgr) {
    plConditionalObject::write(S, mgr);
    S->writeFloat(fTolerance);
    S->writeBool(fDirectional);
}

void plFacingConditionalObject::IPrcWrite(pfPrcHelper* prc) {
    plConditionalObject::IPrcWrite(prc);
    prc->startTag("FacingParams");
    prc->writeParam("Tolerance", fTolerance);
    prc->writeParam("Directional", fDirectional);
    prc->endTag(true);
}

void plFacingConditionalObject::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "FacingParams") {
        fTolerance = tag->getParam("Tolerance", "0").toFloat();
        fDirectional = tag->getParam("Directional", "false").toBool();
    } else {
        plConditionalObject::IPrcParse(tag, mgr);
    }
}
