#include "plFacingConditionalObject.h"

plFacingConditionalObject::plFacingConditionalObject() { }
plFacingConditionalObject::~plFacingConditionalObject() { }

IMPLEMENT_CREATABLE(plFacingConditionalObject, kFacingConditionalObject,
                    plConditionalObject)

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
