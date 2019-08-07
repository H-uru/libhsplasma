/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "plFixedWaterState7.h"

/* plFixedWaterState7::WaveState */
void plFixedWaterState7::WaveState::read(hsStream* S)
{
    fMaxLength = S->readFloat();
    fMinLength = S->readFloat();
    fAmpOverLen = S->readFloat();
    fChop = S->readFloat();
    fAngleDev = S->readFloat();
}

void plFixedWaterState7::WaveState::write(hsStream* S)
{
    S->writeFloat(fMaxLength);
    S->writeFloat(fMinLength);
    S->writeFloat(fAmpOverLen);
    S->writeFloat(fChop);
    S->writeFloat(fAngleDev);
}

void plFixedWaterState7::WaveState::prcWrite(pfPrcHelper* prc)
{
    prc->startTag("WaveState");
    prc->writeParam("MaxLen", fMaxLength);
    prc->writeParam("MinLen", fMinLength);
    prc->writeParam("AmpOverLen", fAmpOverLen);
    prc->writeParam("Chop", fChop);
    prc->writeParam("AngleDev", fAngleDev);
    prc->endTag(true);
}

void plFixedWaterState7::WaveState::prcParse(const pfPrcTag* tag)
{
    if (tag->getName() != "WaveState")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fMaxLength = tag->getParam("MaxLen", "0").to_float();
    fMinLength = tag->getParam("MinLen", "0").to_float();
    fAmpOverLen = tag->getParam("AmpOverLen", "0").to_float();
    fChop = tag->getParam("Chop", "0").to_float();
    fAngleDev = tag->getParam("AngleDev", "0").to_float();
}


/* plFixedWaterState7 */
void plFixedWaterState7::read(hsStream* S)
{
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

void plFixedWaterState7::write(hsStream* S)
{
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

void plFixedWaterState7::prcWrite(pfPrcHelper* prc)
{
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

void plFixedWaterState7::prcParse(const pfPrcTag* tag)
{
    if (tag->getName() != "plFixedWaterState7")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    const pfPrcTag* child = tag->getFirstChild();
    while (child) {
        if (child->getName() == "GeoState") {
            if (child->hasChildren())
                fGeoState.prcParse(child->getFirstChild());
        } else if (child->getName() == "TexState") {
            if (child->hasChildren())
                fTexState.prcParse(child->getFirstChild());
        } else if (child->getName() == "WaterStateParams") {
            fRippleScale = child->getParam("RippleScale", "0").to_float();
            fWaterHeight = child->getParam("WaterHeight", "0").to_float();
            fWispiness = child->getParam("Wispiness", "0").to_float();
            fPeriod = child->getParam("Period", "0").to_float();
            fFingerLength = child->getParam("FingerLength", "0").to_float();
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
            fEdgeOpac = child->getParam("Opacity", "0").to_float();
            fEdgeRadius = child->getParam("Radius", "0").to_float();
        } else if (child->getName() == "WaterTint") {
            if (child->hasChildren())
                fWaterTint.prcParse(child->getFirstChild());
        } else if (child->getName() == "SpecularTint") {
            if (child->hasChildren())
                fSpecularTint.prcParse(child->getFirstChild());
        } else if (child->getName() == "Env") {
            fEnvRefresh = child->getParam("Refresh", "0").to_float();
            fEnvRadius = child->getParam("Radius", "0").to_float();
        } else if (child->getName() == "EnvCenter") {
            if (child->hasChildren())
                fEnvCenter.prcParse(child->getFirstChild());
        } else {
            throw pfPrcTagException(__FILE__, __LINE__, child->getName());
        }
        child = child->getNextSibling();
    }
}
