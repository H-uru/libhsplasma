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

#include "plStereizer.h"

void plStereizer::read(hsStream* S, plResManager* mgr)
{
    plSingleModifier::read(S, mgr);

    fAmbientDist = S->readFloat();
    fTransition = S->readFloat();
    fMaxSepDist = S->readFloat();
    fMinSepDist = S->readFloat();
    fTanAng = S->readFloat();
    fInitPos.read(S);
}

void plStereizer::write(hsStream* S, plResManager* mgr)
{
    plSingleModifier::write(S, mgr);

    S->writeFloat(fAmbientDist);
    S->writeFloat(fTransition);
    S->writeFloat(fMaxSepDist);
    S->writeFloat(fMinSepDist);
    S->writeFloat(fTanAng);
    fInitPos.write(S);
}

void plStereizer::IPrcWrite(pfPrcHelper* prc)
{
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

void plStereizer::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "StereizerParams") {
        fAmbientDist = tag->getParam("AmbientDist", "0").to_float();
        fTransition = tag->getParam("Transition", "0").to_float();
        fMaxSepDist = tag->getParam("MaxSepDist", "0").to_float();
        fMinSepDist = tag->getParam("MinSepDist", "0").to_float();
        fTanAng = tag->getParam("TanAng", "0").to_float();
    } else if (tag->getName() == "InitPos") {
        if (tag->hasChildren())
            fInitPos.prcParse(tag->getFirstChild());
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}
