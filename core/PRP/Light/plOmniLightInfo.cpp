#include "plOmniLightInfo.h"

/* plOmniLightInfo */
plOmniLightInfo::plOmniLightInfo()
               : fAttenConst(0.0f), fAttenLinear(0.0f), fAttenQuadratic(0.0f),
                 fAttenCutoff(0.0f) { }

void plOmniLightInfo::read(hsStream* S, plResManager* mgr) {
    plLightInfo::read(S, mgr);
    fAttenConst = S->readFloat();
    fAttenLinear = S->readFloat();
    fAttenQuadratic = S->readFloat();
    fAttenCutoff = S->readFloat();
}

void plOmniLightInfo::write(hsStream* S, plResManager* mgr) {
    plLightInfo::write(S, mgr);
    S->writeFloat(fAttenConst);
    S->writeFloat(fAttenLinear);
    S->writeFloat(fAttenQuadratic);
    S->writeFloat(fAttenCutoff);
}

void plOmniLightInfo::IPrcWrite(pfPrcHelper* prc) {
    plLightInfo::IPrcWrite(prc);
    prc->startTag("Attensity");
    prc->writeParam("Constant", fAttenConst);
    prc->writeParam("Linear", fAttenLinear);
    prc->writeParam("Quadratic", fAttenQuadratic);
    prc->writeParam("Cutoff", fAttenCutoff);
    prc->endTag(true);
}

void plOmniLightInfo::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Attensity") {
        fAttenConst = tag->getParam("Constant", "0").toFloat();
        fAttenLinear = tag->getParam("Linear", "0").toFloat();
        fAttenQuadratic = tag->getParam("Quadratic", "0").toFloat();
        fAttenCutoff = tag->getParam("Cutoff", "0").toFloat();
    } else {
        plLightInfo::IPrcParse(tag, mgr);
    }
}


/* plSpotLightInfo */
plSpotLightInfo::plSpotLightInfo()
               : fFalloff(0.0f), fSpotInner(0.0f), fSpotOuter(0.0f) { }

void plSpotLightInfo::read(hsStream* S, plResManager* mgr) {
    plOmniLightInfo::read(S, mgr);
    fFalloff = S->readFloat();
    fSpotInner = S->readFloat();
    fSpotOuter = S->readFloat();
}

void plSpotLightInfo::write(hsStream* S, plResManager* mgr) {
    plOmniLightInfo::write(S, mgr);
    S->writeFloat(fFalloff);
    S->writeFloat(fSpotInner);
    S->writeFloat(fSpotOuter);
}

void plSpotLightInfo::IPrcWrite(pfPrcHelper* prc) {
    plOmniLightInfo::IPrcWrite(prc);
    prc->startTag("SpotLight");
    prc->writeParam("Falloff", fFalloff);
    prc->writeParam("SpotInner", fSpotInner);
    prc->writeParam("SpotOuter", fSpotOuter);
    prc->endTag(true);
}

void plSpotLightInfo::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "SpotLight") {
        fFalloff = tag->getParam("Falloff", "0").toFloat();
        fSpotInner = tag->getParam("SpotInner", "0").toFloat();
        fSpotOuter = tag->getParam("SpotOuter", "0").toFloat();
    } else {
        plOmniLightInfo::IPrcParse(tag, mgr);
    }
}
