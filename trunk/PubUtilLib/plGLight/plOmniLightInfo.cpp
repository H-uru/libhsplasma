#include "plOmniLightInfo.h"

// plOmniLightInfo //
plOmniLightInfo::plOmniLightInfo() { }
plOmniLightInfo::~plOmniLightInfo() { }

IMPLEMENT_CREATABLE(plOmniLightInfo, kOmniLightInfo, plLightInfo)

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

void plOmniLightInfo::prcWrite(pfPrcHelper* prc) {
    plLightInfo::prcWrite(prc);
    prc->startTag("Attensity");
    prc->writeParam("Constant", fAttenConst);
    prc->writeParam("Linear", fAttenLinear);
    prc->writeParam("Quadratic", fAttenQuadratic);
    prc->writeParam("Cutoff", fAttenCutoff);
    prc->endTag(true);
}


// plSpotLightInfo //
plSpotLightInfo::plSpotLightInfo() { }
plSpotLightInfo::~plSpotLightInfo() { }

IMPLEMENT_CREATABLE(plSpotLightInfo, kSpotLightInfo, plOmniLightInfo)

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

void plSpotLightInfo::prcWrite(pfPrcHelper* prc) {
    plOmniLightInfo::prcWrite(prc);
    prc->startTag("SpotLight");
    prc->writeParam("Falloff", fFalloff);
    prc->writeParam("SpotInner", fSpotInner);
    prc->writeParam("SpotOuter", fSpotOuter);
    prc->endTag(true);
}
