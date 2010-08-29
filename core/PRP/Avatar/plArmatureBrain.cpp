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
void plArmatureBrain::read(hsStream* S, plResManager* mgr) {
    // Yay for uselessness
    S->readInt();
    if (S->readBool())
        mgr->readKey(S);
    S->readInt();
    S->readFloat();
    S->readDouble();
}

void plArmatureBrain::write(hsStream* S, plResManager* mgr) {
    S->writeInt(0);
    S->writeBool(false);
    S->writeInt(0);
    S->writeFloat(0.0f);
    S->writeDouble(0.0);
}

void plArmatureBrain::IPrcWrite(pfPrcHelper* prc) { }

void plArmatureBrain::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    plCreatable::IPrcParse(tag, mgr);
}


/* plAvBrainHuman */
plAvBrainHuman::plAvBrainHuman() : fIsCustomAvatar(false) { }

void plAvBrainHuman::read(hsStream* S, plResManager* mgr) {
    plArmatureBrain::read(S, mgr);

    if (S->getVer().isMoul() || S->getVer().isUniversal())
        fIsCustomAvatar = S->readBool();
    else
        fIsCustomAvatar = false;
}

void plAvBrainHuman::write(hsStream* S, plResManager* mgr) {
    plArmatureBrain::write(S, mgr);

    if (S->getVer().isMoul() || S->getVer().isUniversal())
        S->writeBool(fIsCustomAvatar);
}

void plAvBrainHuman::IPrcWrite(pfPrcHelper* prc) {
    prc->startTag("HumanParams");
    prc->writeParam("IsCustomAvatar", fIsCustomAvatar);
    prc->endTag(true);
}

void plAvBrainHuman::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "HumanParams") {
        fIsCustomAvatar = tag->getParam("IsCustomAvatar", "false").toBool();
    } else {
        plArmatureBrain::IPrcParse(tag, mgr);
    }
}
