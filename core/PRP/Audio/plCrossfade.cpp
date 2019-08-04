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

#include "plCrossfade.h"

/* plCrossfade */
void plCrossfade::read(hsStream* S, plResManager* mgr)
{
    plSingleModifier::read(S, mgr);

    fFirstIdx = S->readShort();
    fSecondIdx = S->readShort();
    fStartType = S->readInt();
    fEndType = S->readInt();
    fFlags = S->readInt();
    fRegistered = S->readBool();
}

void plCrossfade::write(hsStream* S, plResManager* mgr)
{
    plSingleModifier::write(S, mgr);

    S->writeShort(fFirstIdx);
    S->writeShort(fSecondIdx);
    S->writeInt(fStartType);
    S->writeInt(fEndType);
    S->writeInt(fFlags);
    S->writeBool(fRegistered);
}

void plCrossfade::IPrcWrite(pfPrcHelper* prc)
{
    plSingleModifier::IPrcWrite(prc);

    prc->startTag("CrossfadeParams");
    prc->writeParam("First", fFirstIdx);
    prc->writeParam("Second", fSecondIdx);
    prc->writeParam("StartType", fStartType);
    prc->writeParam("EndType", fEndType);
    prc->writeParamHex("Flags", fFlags);
    prc->writeParam("Registered", fRegistered);
    prc->endTag(true);
}

void plCrossfade::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "CrossfadeParams") {
        fFirstIdx = tag->getParam("First", "0").to_uint();
        fSecondIdx = tag->getParam("Second", "0").to_uint();
        fStartType = tag->getParam("StartType", "0").to_uint();
        fEndType = tag->getParam("EndType", "0").to_uint();
        fFlags = tag->getParam("Flags", "0").to_uint();
        fRegistered = tag->getParam("Registered", "false").to_bool();
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}
