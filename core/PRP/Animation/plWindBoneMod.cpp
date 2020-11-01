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

#include "plWindBoneMod.h"
#include <algorithm>

/* plWindBoneOscillator */
void plWindBoneOscillator::read(hsStream* S)
{
    fDistX = S->readFloat();
    fDistY = S->readFloat();
    fDirX = S->readFloat();
    fDirY = S->readFloat();
    fSpeed = S->readFloat();
}

void plWindBoneOscillator::write(hsStream* S)
{
    S->writeFloat(fDistX);
    S->writeFloat(fDistY);
    S->writeFloat(fDirX);
    S->writeFloat(fDirY);
    S->writeFloat(fSpeed);
}

void plWindBoneOscillator::prcWrite(pfPrcHelper* prc)
{
    prc->startTag("plWindBoneOscillator");
    prc->writeParam("DistX", fDistX);
    prc->writeParam("DistY", fDistY);
    prc->writeParam("DirX", fDirX);
    prc->writeParam("DirY", fDirY);
    prc->writeParam("Speed", fSpeed);
    prc->endTag(true);
}

void plWindBoneOscillator::prcParse(const pfPrcTag* tag)
{
    if (tag->getName() != "plWindBoneOscillator")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fDistX = tag->getParam("DistX", "0").to_float();
    fDistY = tag->getParam("DistY", "0").to_float();
    fDirX = tag->getParam("DirX", "0").to_float();
    fDirY = tag->getParam("DirY", "0").to_float();
    fSpeed = tag->getParam("Speed", "0").to_float();
}


/* plWindBoneMod */
void plWindBoneMod::read(hsStream* S, plResManager* mgr)
{
    plModifier::read(S, mgr);

    for (size_t i=0; i<kNumOscillators; i++)
        fOscillators[i].read(S);
}

void plWindBoneMod::write(hsStream* S, plResManager* mgr)
{
    plModifier::write(S, mgr);

    for (size_t i=0; i<kNumOscillators; i++)
        fOscillators[i].write(S);
}

void plWindBoneMod::IPrcWrite(pfPrcHelper* prc)
{
    plModifier::IPrcWrite(prc);

    prc->writeSimpleTag("Oscillators");
    for (size_t i=0; i<kNumOscillators; i++)
        fOscillators[i].prcWrite(prc);
    prc->closeTag();
}

void plWindBoneMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Oscillators") {
        if (tag->countChildren() != kNumOscillators)
            throw pfPrcParseException(__FILE__, __LINE__, "Incorrect number of oscillators");

        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<kNumOscillators; i++) {
            fOscillators[i].prcParse(child);
            child = child->getNextSibling();
        }
    } else {
        plModifier::IPrcParse(tag, mgr);
    }
}

void plWindBoneMod::removeTarget(const plKey& target)
{
    auto it = std::find(fTargets.begin(), fTargets.end(), target);

    if (it == fTargets.end())
        throw hsBadParamException(__FILE__, __LINE__, "Trying to remove invalid target");

    fTargets.erase(it);
}
