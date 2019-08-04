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

#include "plOmniLightInfo.h"

/* plOmniLightInfo */
void plOmniLightInfo::read(hsStream* S, plResManager* mgr)
{
    plLightInfo::read(S, mgr);
    fAttenConst = S->readFloat();
    fAttenLinear = S->readFloat();
    fAttenQuadratic = S->readFloat();
    fAttenCutoff = S->readFloat();
}

void plOmniLightInfo::write(hsStream* S, plResManager* mgr)
{
    plLightInfo::write(S, mgr);
    S->writeFloat(fAttenConst);
    S->writeFloat(fAttenLinear);
    S->writeFloat(fAttenQuadratic);
    S->writeFloat(fAttenCutoff);
}

void plOmniLightInfo::IPrcWrite(pfPrcHelper* prc)
{
    plLightInfo::IPrcWrite(prc);
    prc->startTag("Attensity");
    prc->writeParam("Constant", fAttenConst);
    prc->writeParam("Linear", fAttenLinear);
    prc->writeParam("Quadratic", fAttenQuadratic);
    prc->writeParam("Cutoff", fAttenCutoff);
    prc->endTag(true);
}

void plOmniLightInfo::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Attensity") {
        fAttenConst = tag->getParam("Constant", "0").to_float();
        fAttenLinear = tag->getParam("Linear", "0").to_float();
        fAttenQuadratic = tag->getParam("Quadratic", "0").to_float();
        fAttenCutoff = tag->getParam("Cutoff", "0").to_float();
    } else {
        plLightInfo::IPrcParse(tag, mgr);
    }
}


/* plSpotLightInfo */
plSpotLightInfo::plSpotLightInfo()
    : fFalloff(), fSpotInner(), fSpotOuter() { }

void plSpotLightInfo::read(hsStream* S, plResManager* mgr)
{
    plOmniLightInfo::read(S, mgr);
    fFalloff = S->readFloat();
    fSpotInner = S->readFloat();
    fSpotOuter = S->readFloat();
}

void plSpotLightInfo::write(hsStream* S, plResManager* mgr)
{
    plOmniLightInfo::write(S, mgr);
    S->writeFloat(fFalloff);
    S->writeFloat(fSpotInner);
    S->writeFloat(fSpotOuter);
}

void plSpotLightInfo::IPrcWrite(pfPrcHelper* prc)
{
    plOmniLightInfo::IPrcWrite(prc);
    prc->startTag("SpotLight");
    prc->writeParam("Falloff", fFalloff);
    prc->writeParam("SpotInner", fSpotInner);
    prc->writeParam("SpotOuter", fSpotOuter);
    prc->endTag(true);
}

void plSpotLightInfo::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "SpotLight") {
        fFalloff = tag->getParam("Falloff", "0").to_float();
        fSpotInner = tag->getParam("SpotInner", "0").to_float();
        fSpotOuter = tag->getParam("SpotOuter", "0").to_float();
    } else {
        plOmniLightInfo::IPrcParse(tag, mgr);
    }
}
