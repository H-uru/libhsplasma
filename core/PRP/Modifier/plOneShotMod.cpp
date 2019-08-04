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

#include "plOneShotMod.h"

void plOneShotMod::read(hsStream* S, plResManager* mgr)
{
    plMultiModifier::read(S, mgr);

    fAnimName = S->readSafeStr();
    fSeekDuration = S->readFloat();
    fDrivable = S->readBool();
    fReversable = S->readBool();
    fSmartSeek = S->readBool();

    if (S->getVer() > 0x02006304) { /*TODO: Verify! */
        fNoSeek = S->readBool();
    }
}

void plOneShotMod::write(hsStream* S, plResManager* mgr)
{
    plMultiModifier::write(S, mgr);

    S->writeSafeStr(fAnimName);
    S->writeFloat(fSeekDuration);
    S->writeBool(fDrivable);
    S->writeBool(fReversable);
    S->writeBool(fSmartSeek);
    S->writeBool(fNoSeek);
}

void plOneShotMod::IPrcWrite(pfPrcHelper* prc)
{
    plMultiModifier::IPrcWrite(prc);

    prc->startTag("Animation");
    prc->writeParam("Name", fAnimName);
    prc->writeParam("SeekDuration", fSeekDuration);
    prc->writeParam("Drivable", fDrivable);
    prc->writeParam("Reversable", fReversable);
    prc->writeParam("SmartSeek", fSmartSeek);
    prc->writeParam("NoSeek", fNoSeek);
    prc->endTag(true);
}

void plOneShotMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Animation") {
        fAnimName = tag->getParam("Name", "");
        fSeekDuration = tag->getParam("SeekDuration", "0").to_float();
        fDrivable = tag->getParam("Drivable", "false").to_bool();
        fReversable = tag->getParam("Reversable", "false").to_bool();
        fSmartSeek = tag->getParam("SmartSeek", "false").to_bool();
        fNoSeek = tag->getParam("NoSeek", "true").to_bool();
    } else {
        plMultiModifier::IPrcParse(tag, mgr);
    }
}
