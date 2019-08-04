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

#include "plExcludeRegionMsg.h"

void plExcludeRegionMsg::read(hsStream* S, plResManager* mgr)
{
    plMessage::read(S, mgr);
    fCmd = S->readByte();
    if (S->getVer().isUru() || S->getVer().isUniversal())
        fSynchFlags = S->readInt();
    else
        fSynchFlags = 0;
}

void plExcludeRegionMsg::write(hsStream* S, plResManager* mgr)
{
    plMessage::write(S, mgr);
    S->writeByte(fCmd);
    if (S->getVer().isUru() || S->getVer().isUniversal())
        S->writeInt(fSynchFlags);
}

void plExcludeRegionMsg::IPrcWrite(pfPrcHelper* prc)
{
    plMessage::IPrcWrite(prc);

    prc->startTag("ExcludeParams");
    prc->writeParam("Command", fCmd);
    prc->writeParamHex("SynchFlags", fSynchFlags);
    prc->endTag(true);
}

void plExcludeRegionMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "ExcludeParams") {
        fCmd = tag->getParam("Command", "0").to_uint();
        fSynchFlags = tag->getParam("SynchFlags", "0").to_uint();
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}
