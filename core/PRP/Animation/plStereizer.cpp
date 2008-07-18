#include "plStereizer.h"

plStereizer::plStereizer()
           : fAmbientDist(0.0f), fTransition(0.0f), fMaxSepDist(0.0f),
             fMinSepDist(0.0f), fTanAng(0.0f) {
    fFlags.setName(kLeftChannel, "kLeftChannel");
    fFlags.setName(kHasMaster, "kHasMaster");
}

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

void plStereizer::IPrcWrite(pfPrcHelper* prc) {
    plSingleModifier::IPrcWrite(prc);

    prc->startTag("StereizerParams");
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

void plStereizer::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "StereizerParams") {
        fAmbientDist = tag->getParam("AmbientDist", "0").toFloat();
        fTransition = tag->getParam("Transition", "0").toFloat();
        fMaxSepDist = tag->getParam("MaxSepDist", "0").toFloat();
        fMinSepDist = tag->getParam("MinSepDist", "0").toFloat();
        fTanAng = tag->getParam("TanAng", "0").toFloat();
    } else if (tag->getName() == "InitPos") {
        if (tag->hasChildren())
            fInitPos.prcParse(tag->getFirstChild());
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}
