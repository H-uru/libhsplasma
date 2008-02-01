#include "plFixedWaterState6.h"

// plFixedWaterState6::WaveState //
plFixedWaterState6::WaveState::WaveState()
                             : fMaxLength(0.0f), fMinLength(0.0f),
                               fAmpOverLen(0.0f), fChop(0.0f), fAngleDev(0.0f) { }

plFixedWaterState6::WaveState::~WaveState() { }

void plFixedWaterState6::WaveState::read(hsStream* S) {
    fMaxLength = S->readFloat();
    fMinLength = S->readFloat();
    fAmpOverLen = S->readFloat();
    fChop = S->readFloat();
    fAngleDev = S->readFloat();
}

void plFixedWaterState6::WaveState::write(hsStream* S) {
    S->writeFloat(fMaxLength);
    S->writeFloat(fMinLength);
    S->writeFloat(fAmpOverLen);
    S->writeFloat(fChop);
    S->writeFloat(fAngleDev);
}

void plFixedWaterState6::WaveState::prcWrite(pfPrcHelper* prc) {
    prc->startTag("WaveState");
    prc->writeParam("MaxLen", fMaxLength);
    prc->writeParam("MinLen", fMinLength);
    prc->writeParam("AmpOverLen", fAmpOverLen);
    prc->writeParam("Chop", fChop);
    prc->writeParam("AngleDev", fAngleDev);
    prc->endTag(true);
}


// plFixedWaterState6 //
plFixedWaterState6::plFixedWaterState6()
                  : fRippleScale(0.0f), fWaterHeight(0.0f), fWispiness(0.0f),
                    fEdgeOpac(0.0f), fEdgeRadius(0.0f), fPeriod(0.0f),
                    fFingerLength(0.0f), fEnvRefresh(0.0f), fEnvRadius(0.0f) { }

plFixedWaterState6::~plFixedWaterState6() { }


void plFixedWaterState6::read(hsStream* S) {
    fWaterOffset.read(S);
    fGeoState.read(S);
    fTexState.read(S);
    fRippleScale = S->readFloat();
    fWaterHeight = S->readFloat();
    fWindDir.read(S);
    fSpecVec.read(S);
    fMaxAtten.read(S);
    fMinAtten.read(S);
    fWispiness = S->readFloat();
    fShoreTint.read(S);
    fMaxColor.read(S);
    fMinColor.read(S);
    fEdgeOpac = S->readFloat();
    fEdgeRadius = S->readFloat();
    fPeriod = S->readFloat();
    fFingerLength = S->readFloat();
    fEnvCenter.read(S);
    fEnvRefresh = S->readFloat();
    fEnvRadius = S->readFloat();
}

void plFixedWaterState6::write(hsStream* S) {
    fWaterOffset.write(S);
    fGeoState.write(S);
    fTexState.write(S);
    S->writeFloat(fRippleScale);
    S->writeFloat(fWaterHeight);
    fWindDir.write(S);
    fSpecVec.write(S);
    fMaxAtten.write(S);
    fMinAtten.write(S);
    S->writeFloat(fWispiness);
    fShoreTint.write(S);
    fMaxColor.write(S);
    fMinColor.write(S);
    S->writeFloat(fEdgeOpac);
    S->writeFloat(fEdgeRadius);
    S->writeFloat(fPeriod);
    S->writeFloat(fFingerLength);
    fEnvCenter.write(S);
    S->writeFloat(fEnvRefresh);
    S->writeFloat(fEnvRadius);
}

void plFixedWaterState6::prcWrite(pfPrcHelper* prc) {
    prc->writeSimpleTag("plFixedWaterState6");

    prc->writeSimpleTag("WaterOffset");
    fWaterOffset.prcWrite(prc);
    prc->closeTag();
    
    prc->writeSimpleTag("GeoState");
    fGeoState.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("TexState");
    fTexState.prcWrite(prc);
    prc->closeTag();
    
    prc->startTag("RippleScale");
    prc->writeParam("value", fRippleScale);
    prc->endTag(true);
    prc->startTag("WaterHeight");
    prc->writeParam("value", fWaterHeight);
    prc->endTag(true);

    prc->writeSimpleTag("WindDir");
    fWindDir.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("SpecVec");
    fSpecVec.prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("MaxAtten");
    fMaxAtten.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("MinAtten");
    fMinAtten.prcWrite(prc);
    prc->closeTag();

    prc->startTag("Wispiness");
    prc->writeParam("value", fWispiness);
    prc->endTag(true);

    prc->writeSimpleTag("ShoreTint");
    fShoreTint.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("MaxColor");
    fMaxColor.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("MinColor");
    fMinColor.prcWrite(prc);
    prc->closeTag();

    prc->startTag("Edge");
    prc->writeParam("Opacity", fEdgeOpac);
    prc->writeParam("Radius", fEdgeRadius);
    prc->endTag(true);

    prc->startTag("Period");
    prc->writeParam("value", fPeriod);
    prc->endTag(true);
    prc->startTag("FingerLength");
    prc->writeParam("value", fFingerLength);
    prc->endTag(true);

    prc->writeSimpleTag("EnvCenter");
    fEnvCenter.prcWrite(prc);
    prc->closeTag();

    prc->startTag("Env");
    prc->writeParam("Refresh", fEnvRefresh);
    prc->writeParam("Radius", fEnvRadius);
    prc->endTag(true);

    prc->closeTag(); // plFixedWaterState6
}
