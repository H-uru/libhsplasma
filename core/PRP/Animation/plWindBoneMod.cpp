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

/* plWindBoneOscillator */
void plWindBoneOscillator::read(hsStream* S)
{
    fUnknown1 = S->readFloat();
    fUnknown2 = S->readFloat();
    fUnknown3 = S->readFloat();
    fUnknown4 = S->readFloat();
    fUnknown5 = S->readFloat();
}

void plWindBoneOscillator::write(hsStream* S)
{
    S->writeFloat(fUnknown1);
    S->writeFloat(fUnknown2);
    S->writeFloat(fUnknown3);
    S->writeFloat(fUnknown4);
    S->writeFloat(fUnknown5);
}

void plWindBoneOscillator::prcWrite(pfPrcHelper* prc)
{
    prc->startTag("plWindBoneOscillator");
    prc->writeParam("Unknown1", fUnknown1);
    prc->writeParam("Unknown2", fUnknown2);
    prc->writeParam("Unknown3", fUnknown3);
    prc->writeParam("Unknown4", fUnknown4);
    prc->writeParam("Unknown5", fUnknown5);
    prc->endTag(true);
}

void plWindBoneOscillator::prcParse(const pfPrcTag* tag)
{
    if (tag->getName() != "plWindBoneOscillator")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fUnknown1 = tag->getParam("Unknown1", "0").to_float();
    fUnknown2 = tag->getParam("Unknown2", "0").to_float();
    fUnknown3 = tag->getParam("Unknown3", "0").to_float();
    fUnknown4 = tag->getParam("Unknown4", "0").to_float();
    fUnknown5 = tag->getParam("Unknown5", "0").to_float();
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
