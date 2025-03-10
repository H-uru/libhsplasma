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

#include "plCloneSpawnModifier.h"

void plCloneSpawnModifier::read(hsStream* S, plResManager* mgr)
{
    if (S->getVer().isMoul()) {
        plSingleModifier::read(S, mgr);
        fTemplateName = S->readSafeStr();
        fUserData = S->readInt();
    } else {
        // This is bad, but also never used in earlier Plasma versions
        fTemplateName = S->readSafeStr();
        plSingleModifier::read(S, mgr);
    }
}

void plCloneSpawnModifier::write(hsStream* S, plResManager* mgr)
{
    if (S->getVer().isMoul()) {
        plSingleModifier::write(S, mgr);
        S->writeSafeStr(fTemplateName);
        S->writeInt(fUserData);
    } else {
        // This is bad, but also never used in earlier Plasma versions
        S->writeSafeStr(fTemplateName);
        plSingleModifier::write(S, mgr);
    }
}

void plCloneSpawnModifier::IPrcWrite(pfPrcHelper* prc)
{
    plSingleModifier::IPrcWrite(prc);

    prc->startTag("SpawnParams");
    prc->writeParam("TemplateName", fTemplateName);
    prc->writeParam("UserData", fUserData);
    prc->endTag(true);
}

void plCloneSpawnModifier::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "SpawnParams") {
        fTemplateName = tag->getParam("TemplateName", "");
        fUserData = tag->getParam("UserData", "0").to_uint();
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}

