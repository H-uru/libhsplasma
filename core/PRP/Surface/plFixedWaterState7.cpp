#include "plFixedWaterState7.h"

/* plFixedWaterState7::WaveState */
plFixedWaterState7::WaveState::WaveState()
                             : fMaxLength(0.0f), fMinLength(0.0f),
                               fAmpOverLen(0.0f), fChop(0.0f), fAngleDev(0.0f) { }

plFixedWaterState7::WaveState::~WaveState() { }

void plFixedWaterState7::WaveState::read(hsStream* S) {
    fMaxLength = S->readFloat();
    fMinLength = S->readFloat();
    fAmpOverLen = S->readFloat();
    fChop = S->readFloat();
    fAngleDev = S->readFloat();
}

void plFixedWaterState7::WaveState::write(hsStream* S) {
    S->writeFloat(fMaxLength);
    S->writeFloat(fMinLength);
    S->writeFloat(fAmpOverLen);
    S->writeFloat(fChop);
    S->writeFloat(fAngleDev);
}

void plFixedWaterState7::WaveState::prcWrite(pfPrcHelper* prc) {
    prc->startTag("WaveState");
    prc->writeParam("MaxLen", fMaxLength);
    prc->writeParam("MinLen", fMinLength);
    prc->writeParam("AmpOverLen", fAmpOverLen);
    prc->writeParam("Chop", fChop);
    prc->writeParam("AngleDev", fAngleDev);
    prc->endTag(true);
}

void plFixedWaterState7::WaveState::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "WaveState")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fMaxLength = tag->getParam("MaxLen", "0").toFloat();
    fMinLength = tag->getParam("MinLen", "0").toFloat();
    fAmpOverLen = tag->getParam("AmpOverLen", "0").toFloat();
    fChop = tag->getParam("Chop", "0").toFloat();
    fAngleDev = tag->getParam("AngleDev", "0").toFloat();
}


/* plFixedWaterState7 */
plFixedWaterState7::plFixedWaterState7()
                  : fRippleScale(0.0f), fWaterHeight(0.0f), fWispiness(0.0f),
                    fEdgeOpac(0.0f), fEdgeRadius(0.0f), fPeriod(0.0f),
                    fFingerLength(0.0f), fEnvRefresh(0.0f), fEnvRadius(0.0f) { }

plFixedWaterState7::~plFixedWaterState7() { }


void plFixedWaterState7::read(hsStream* S) {
    fGeoState.read(S);
    fTexState.read(S);
    fRippleScale = S->readFloat();
    fWindDir.read(S);
    fSpecVec.read(S);
    fWaterHeight = S->readFloat();
    fWaterOffset.read(S);
    fMaxAtten.read(S);
    fMinAtten.read(S);
    fDepthFalloff.read(S);
    fWispiness = S->readFloat();
    fShoreTint.read(S);
    fMaxColor.read(S);
    fMinColor.read(S);
    fEdgeOpac = S->readFloat();
    fEdgeRadius = S->readFloat();
    fPeriod = S->readFloat();
    fFingerLength = S->readFloat();
    fWaterTint.read(S);
    fSpecularTint.read(S);
    fEnvCenter.read(S);
    fEnvRefresh = S->readFloat();
    fEnvRadius = S->readFloat();
}

void plFixedWaterState7::write(hsStream* S) {
    fGeoState.write(S);
    fTexState.write(S);
    S->writeFloat(fRippleScale);
    fWindDir.write(S);
    fSpecVec.write(S);
    S->writeFloat(fWaterHeight);
    fWaterOffset.write(S);
    fMaxAtten.write(S);
    fMinAtten.write(S);
    fDepthFalloff.write(S);
    S->writeFloat(fWispiness);
    fShoreTint.write(S);
    fMaxColor.write(S);
    fMinColor.write(S);
    S->writeFloat(fEdgeOpac);
    S->writeFloat(fEdgeRadius);
    S->writeFloat(fPeriod);
    S->writeFloat(fFingerLength);
    fWaterTint.write(S);
    fSpecularTint.write(S);
    fEnvCenter.write(S);
    S->writeFloat(fEnvRefresh);
    S->writeFloat(fEnvRadius);
}

void plFixedWaterState7::prcWrite(pfPrcHelper* prc) {
    prc->writeSimpleTag("plFixedWaterState7");

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

    prc->writeSimpleTag("WaterOffset");
    fWaterOffset.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("MaxAtten");
    fMaxAtten.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("MinAtten");
    fMinAtten.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("DepthFalloff");
    fDepthFalloff.prcWrite(prc);
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

    prc->writeSimpleTag("WaterTint");
    fWaterTint.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("SpecularTint");
    fSpecularTint.prcWrite(prc);
    prc->closeTag();

    prc->startTag("Env");
    prc->writeParam("Refresh", fEnvRefresh);
    prc->writeParam("Radius", fEnvRadius);
    prc->endTag(true);

    prc->writeSimpleTag("EnvCenter");
    fEnvCenter.prcWrite(prc);
    prc->closeTag();

    prc->closeTag(); // plFixedWaterState7
}

void plFixedWaterState7::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "plFixedWaterState7")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    const pfPrcTag* child = tag->getFirstChild();
    while (child != NULL) {
        if (child->getName() == "GeoState") {
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
        } else if (child->getName() == "WaterOffset") {
            if (child->hasChildren())
                fWaterOffset.prcParse(child->getFirstChild());
        } else if (child->getName() == "MaxAtten") {
            if (child->hasChildren())
                fMaxAtten.prcParse(child->getFirstChild());
        } else if (child->getName() == "MinAtten") {
            if (child->hasChildren())
                fMinAtten.prcParse(child->getFirstChild());
        } else if (child->getName() == "DepthFalloff") {
            if (child->hasChildren())
                fDepthFalloff.prcParse(child->getFirstChild());
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
        } else if (child->getName() == "WaterTint") {
            if (child->hasChildren())
                fWaterTint.prcParse(child->getFirstChild());
        } else if (child->getName() == "SpecularTint") {
            if (child->hasChildren())
                fSpecularTint.prcParse(child->getFirstChild());
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

plFixedWaterState7::WaveState& plFixedWaterState7::getGeoState() { return fGeoState; }
const plFixedWaterState7::WaveState& plFixedWaterState7::getGeoState() const { return fGeoState; }
plFixedWaterState7::WaveState& plFixedWaterState7::getTexState() { return fTexState; }
const plFixedWaterState7::WaveState& plFixedWaterState7::getTexState() const { return fTexState; }
float plFixedWaterState7::getRippleScale() const { return fRippleScale; }
float plFixedWaterState7::getWaterHeight() const { return fWaterHeight; }
hsVector3 plFixedWaterState7::getWindDir() const { return fWindDir; }
hsVector3 plFixedWaterState7::getSpecVector() const { return fSpecVec; }
hsVector3 plFixedWaterState7::getWaterOffset() const { return fWaterOffset; }
hsVector3 plFixedWaterState7::getMaxAtten() const { return fMaxAtten; }
hsVector3 plFixedWaterState7::getMinAtten() const { return fMinAtten; }
hsVector3 plFixedWaterState7::getDepthFalloff() const { return fDepthFalloff; }
float plFixedWaterState7::getWispiness() const { return fWispiness; }
hsColorRGBA plFixedWaterState7::getShoreTint() const { return fShoreTint; }
hsColorRGBA plFixedWaterState7::getMaxColor() const { return fMaxColor; }
hsColorRGBA plFixedWaterState7::getMinColor() const { return fMinColor; }
float plFixedWaterState7::getEdgeOpacity() const { return fEdgeOpac; }
float plFixedWaterState7::getEdgeRadius() const { return fEdgeRadius; }
float plFixedWaterState7::getPeriod() const { return fPeriod; }
float plFixedWaterState7::getFingerLength() const { return fFingerLength; }
hsColorRGBA plFixedWaterState7::getWaterTint() const { return fWaterTint; }
hsColorRGBA plFixedWaterState7::getSpecularTint() const { return fSpecularTint; }
hsVector3 plFixedWaterState7::getEnvCenter() const { return fEnvCenter; }
float plFixedWaterState7::getEnvRefresh() const { return fEnvRefresh; }
float plFixedWaterState7::getEnvRadius() const { return fEnvRadius; }

void plFixedWaterState7::setRippleScale(float scale) { fRippleScale = scale; }
void plFixedWaterState7::setWaterHeight(float height) { fWaterHeight = height; }
void plFixedWaterState7::setWindDir(const hsVector3& dir) { fWindDir = dir; }
void plFixedWaterState7::setSpecVector(const hsVector3& vec) { fSpecVec = vec; }
void plFixedWaterState7::setWaterOffset(const hsVector3& offset) { fWaterOffset = offset; }
void plFixedWaterState7::setMaxAtten(const hsVector3& atten) { fMaxAtten = atten; }
void plFixedWaterState7::setMinAtten(const hsVector3& atten) { fMinAtten = atten; }
void plFixedWaterState7::setDepthFalloff(const hsVector3& falloff) { fDepthFalloff = falloff; }
void plFixedWaterState7::setWispiness(float wispiness) { fWispiness = wispiness; }
void plFixedWaterState7::setShoreTint(const hsColorRGBA& tint) { fShoreTint = tint; }
void plFixedWaterState7::setMaxColor(const hsColorRGBA& color) { fMaxColor = color; }
void plFixedWaterState7::setMinColor(const hsColorRGBA& color) { fMinColor = color; }
void plFixedWaterState7::setEdgeOpacity(float opacity) { fEdgeOpac = opacity; }
void plFixedWaterState7::setEdgeRadius(float radius) { fEdgeRadius = radius; }
void plFixedWaterState7::setPeriod(float period) { fPeriod = period; }
void plFixedWaterState7::setFingerLength(float length) { fFingerLength = length; }
void plFixedWaterState7::setWaterTint(const hsColorRGBA& tint) { fWaterTint = tint; }
void plFixedWaterState7::setSpecularTint(const hsColorRGBA& tint) { fSpecularTint = tint; }
void plFixedWaterState7::setEnvCenter(const hsVector3& center) { fEnvCenter = center; }
void plFixedWaterState7::setEnvRefresh(float refresh) { fEnvRefresh = refresh; }
void plFixedWaterState7::setEnvRadius(float radius) { fEnvRadius = radius; }
