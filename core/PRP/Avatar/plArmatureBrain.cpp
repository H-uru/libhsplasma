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

#include "plArmatureBrain.h"

/* plArmatureBrain */
void plArmatureBrain::read(hsStream* S, plResManager* mgr)
{
    // Yay for uselessness
    if (!S->getVer().isNewPlasma()) {
        if (S->readInt() != 0)
            throw hsBadParamException(__FILE__, __LINE__, "plArmatureBrain must start with a 0 int");
        if (S->readBool())
            throw hsBadParamException(__FILE__, __LINE__, "plArmatureBrain must contain a null plKey");
        fAvBrainUserInt  = S->readInt(); // 0 in POTS, 927 in UU
        fAvBrainUserFloat = S->readFloat(); // 0.0 in POTS, 1.0 in UU
        fAvBrainUserDouble = S->readDouble(); // 0.0 in POTS, 1.0 in UU
    }
}

void plArmatureBrain::write(hsStream* S, plResManager* mgr)
{
    if (!S->getVer().isNewPlasma()) {
        S->writeInt(0);
        S->writeBool(false); // actually a null plKey
        S->writeInt(fAvBrainUserInt);
        S->writeFloat(fAvBrainUserFloat);
        S->writeDouble(fAvBrainUserDouble);
    }
}


/* plAvBrainHuman */
void plAvBrainHuman::read(hsStream* S, plResManager* mgr)
{
    plArmatureBrain::read(S, mgr);

    if (S->getVer().isMoul() || S->getVer().isUniversal())
        fIsCustomAvatar = S->readBool();
    else
        fIsCustomAvatar = false;
}

void plAvBrainHuman::write(hsStream* S, plResManager* mgr)
{
    plArmatureBrain::write(S, mgr);

    if (S->getVer().isMoul() || S->getVer().isUniversal())
        S->writeBool(fIsCustomAvatar);
}

void plAvBrainHuman::IPrcWrite(pfPrcHelper* prc)
{
    prc->startTag("HumanParams");
    prc->writeParam("IsCustomAvatar", fIsCustomAvatar);
    prc->endTag(true);
}

void plAvBrainHuman::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "HumanParams") {
        fIsCustomAvatar = tag->getParam("IsCustomAvatar", "false").to_bool();
    } else {
        plArmatureBrain::IPrcParse(tag, mgr);
    }
}
