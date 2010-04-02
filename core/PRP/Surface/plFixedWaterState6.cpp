#include "plFixedWaterState6.h"

/* plFixedWaterState6::WaveState */
plFixedWaterState6::WaveState::WaveState()
                             : fMaxLength(0.0f), fMinLength(0.0f),
                               fAmpOverLen(0.0f), fChop(0.0f), fAngleDev(0.0f) { }

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

void plFixedWaterState6::WaveState::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "WaveState")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fMaxLength = tag->getParam("MaxLen", "0").toFloat();
    fMinLength = tag->getParam("MinLen", "0").toFloat();
    fAmpOverLen = tag->getParam("AmpOverLen", "0").toFloat();
    fChop = tag->getParam("Chop", "0").toFloat();
    fAngleDev = tag->getParam("AngleDev", "0").toFloat();
}


/* plFixedWaterState6 */
plFixedWaterState6::plFixedWaterState6()
                  : fRippleScale(0.0f), fWaterHeight(0.0f), fWispiness(0.0f),
                    fEdgeOpac(0.0f), fEdgeRadius(0.0f), fPeriod(0.0f),
                    fFingerLength(0.0f), fEnvRefresh(0.0f), fEnvRadius(0.0f) { }

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

    prc->startTag("WaterStateParams");
    prc->writeParam("RippleScale", fRippleScale);
    prc->writeParam("WaterHeight", fWaterHeight);
    prc->writeParam("Wispiness", fWispiness);
    prc->writeParam("Period", fPeriod);
    prc->writeParam("FingerLength", fFingerLength);
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

    prc->startTag("Env");
    prc->writeParam("Refresh", fEnvRefresh);
    prc->writeParam("Radius", fEnvRadius);
    prc->endTag(true);

    prc->writeSimpleTag("EnvCenter");
    fEnvCenter.prcWrite(prc);
    prc->closeTag();

    prc->closeTag(); // plFixedWaterState6
}

void plFixedWaterState6::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "plFixedWaterState6")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    const pfPrcTag* child = tag->getFirstChild();
    while (child != NULL) {
        if (child->getName() == "WaterOffset") {
            if (child->hasChildren())
                fWaterOffset.prcParse(child->getFirstChild());
        } else if (child->getName() == "GeoState") {
            if (child->hasChildren())
                fGeoState.prcParse(child->getFirstChild());
        } else if (child->getName() == "TexState") {
            if (child->hasChildren())
                fTexState.prcParse(child->getFirstChild());
        } else if (child->getName() == "WaterStateParams") {
            fRippleScale = child->getParam("RippleScale", "0").toFloat();
            fWaterHeight = child->getParam("WaterHeight", "0").toFloat();
            fWispiness = child->getParam("Wispiness", "0").toFloat();
            fPeriod = child->getParam("Period", "0").toFloat();
            fFingerLength = child->getParam("FingerLength", "0").toFloat();
        } else if (child->getName() == "WindDir") {
            if (child->hasChildren())
                fWindDir.prcParse(child->getFirstChild());
        } else if (child->getName() == "SpecVec") {
            if (child->hasChildren())
                fSpecVec.prcParse(child->getFirstChild());
        } else if (child->getName() == "MaxAtten") {
            if (child->hasChildren())
                fMaxAtten.prcParse(child->getFirstChild());
        } else if (child->getName() == "MinAtten") {
            if (child->hasChildren())
                fMinAtten.prcParse(child->getFirstChild());
        } else if (child->getName() == "ShoreTint") {
            if (child->hasChildren())
                fShoreTint.prcParse(child->getFirstChild());
        } else if (child->getName() == "MaxColor") {
            if (child->hasChildren())
                fMaxColor.prcParse(child->getFirstChild());
        } else if (child->getName() == "MinColor") {
            if (child->hasChildren())
                fMinColor.prcParse(child->getFirstChild());
        } else if (child->getName() == "Edge") {
            fEdgeOpac = child->getParam("Opacity", "0").toFloat();
            fEdgeRadius = child->getParam("Radius", "0").toFloat();
        } else if (child->getName() == "Env") {
            fEnvRefresh = child->getParam("Refresh", "0").toFloat();
            fEnvRadius = child->getParam("Radius", "0").toFloat();
        } else if (child->getName() == "EnvCenter") {
            if (child->hasChildren())
                fEnvCenter.prcParse(child->getFirstChild());
        } else {
            throw pfPrcTagException(__FILE__, __LINE__, child->getName());
        }
        child = child->getNextSibling();
    }
}
