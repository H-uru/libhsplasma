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

#include "plSpawnModifier.h"

/* plSpawnMod */
void plSpawnMod::read(hsStream* S, plResManager* mgr)
{
    plModifier::read(S, mgr);

    fAge = S->readSafeStr();
    fPage = S->readSafeStr();
    fObjName = S->readSafeStr();
    fBool1 = S->readBool();
    fDisableDraw = S->readBool();
}

void plSpawnMod::write(hsStream* S, plResManager* mgr)
{
    plModifier::write(S, mgr);

    S->writeSafeStr(fAge);
    S->writeSafeStr(fPage);
    S->writeSafeStr(fObjName);
    S->writeBool(fBool1);
    S->writeBool(fDisableDraw);
}

void plSpawnMod::IPrcWrite(pfPrcHelper* prc)
{
    plModifier::IPrcWrite(prc);

    prc->startTag("SpawnParams");
    prc->writeParam("Age", fAge);
    prc->writeParam("Page", fPage);
    prc->writeParam("ObjName", fObjName);
    prc->writeParam("Bool1", fBool1);
    prc->writeParam("DisableDraw", fDisableDraw);
    prc->endTag(true);
}

void plSpawnMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "SpawnParams") {
        fAge = tag->getParam("Age", "");
        fPage = tag->getParam("Page", "");
        fObjName = tag->getParam("ObjName", "");
        fBool1 = tag->getParam("Bool1", "false").to_bool();
        fDisableDraw = tag->getParam("DisableDraw", "false").to_bool();
    } else {
        plModifier::IPrcParse(tag, mgr);
    }
}
