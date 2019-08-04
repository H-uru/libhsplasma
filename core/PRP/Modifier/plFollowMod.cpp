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

#include "plFollowMod.h"

void plFollowMod::read(hsStream* S, plResManager* mgr)
{
    plSingleModifier::read(S, mgr);

    fLeaderType = plFollowMod::FollowLeaderType(S->readByte());
    fMode = S->readByte();
    fLeader = mgr->readKey(S);
}

void plFollowMod::write(hsStream* S, plResManager* mgr)
{
    plSingleModifier::write(S, mgr);

    S->writeByte(fLeaderType);
    S->writeByte(fMode);
    mgr->writeKey(S, fLeader);
}

void plFollowMod::IPrcWrite(pfPrcHelper* prc)
{
    plSingleModifier::IPrcWrite(prc);

    prc->startTag("Flags");
    prc->writeParam("leaderType", static_cast<uint8_t>(fLeaderType));
    prc->writeParamHex("mode", fMode);
    prc->endTag(true);

    prc->writeSimpleTag("Leader");
    plResManager::PrcWriteKey(prc, fLeader);
    prc->closeTag();
}

void plFollowMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Leader") {
        if (tag->hasChildren())
            fLeader = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Flags") {
        fLeaderType = static_cast<FollowLeaderType>(tag->getParam("leaderType", "0").to_uint());
        fMode = tag->getParam("mode", "7").to_uint();
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}
