#include "plStereizer.h"

plStereizer::plStereizer()
           : fAmbientDist(0.0f), fTransition(0.0f), fMaxSepDist(0.0f),
             fMinSepDist(0.0f), fTanAng(0.0f) { }

plStereizer::~plStereizer() { }

IMPLEMENT_CREATABLE(plStereizer, kStereizer, plSingleModifier)

void plStereizer::read(hsStream* S, plResManager* mgr) {
    plSingleModifier::read(S, mgr);

    fAmbientDist = S->readFloat();
    fTransition = S->readFloat();
    fMaxSepDist = S->readFloat();
    fMinSepDist = S->readFloat();
    fTanAng = S->readFloat();
    fInitPos.read(S);
}

void plStereizer::write(hsStream* S, plResManager* mgr) {
    plSingleModifier::write(S, mgr);

    S->writeFloat(fAmbientDist);
    S->writeFloat(fTransition);
    S->writeFloat(fMaxSepDist);
    S->writeFloat(fMinSepDist);
    S->writeFloat(fTanAng);
    fInitPos.write(S);
}

void plStereizer::prcWrite(pfPrcHelper* prc) {
    plSingleModifier::prcWrite(prc);

    prc->startTag("Params");
    prc->writeParam("AmbientDist", fAmbientDist);
    prc->writeParam("Transition", fTransition);
    prc->writeParam("MaxSepDist", fMaxSepDist);
    prc->writeParam("MinSepDist", fMinSepDist);
    prc->writeParam("TanAng", fTanAng);
    prc->endTag(true);

    prc->writeSimpleTag("InitPos");
    fInitPos.prcWrite(prc);
    prc->closeTag();
}
