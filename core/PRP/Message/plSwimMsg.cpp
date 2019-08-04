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

#include "plSwimMsg.h"

void plSwimMsg::read(hsStream* S, plResManager* mgr)
{
    plMessage::read(S, mgr);
    fIsEntering = S->readBool();
    fSwimRegion = mgr->readKey(S);
}

void plSwimMsg::write(hsStream* S, plResManager* mgr)
{
    plMessage::write(S, mgr);
    S->writeBool(fIsEntering);
    mgr->writeKey(S, fSwimRegion);
}

void plSwimMsg::IPrcWrite(pfPrcHelper* prc)
{
    plMessage::IPrcWrite(prc);

    prc->startTag("SwimMsgParams");
    prc->writeParam("IsEntering", fIsEntering);
    prc->endTag(true);

    prc->writeSimpleTag("SwimRegion");
    plResManager::PrcWriteKey(prc, fSwimRegion);
    prc->closeTag();
}

void plSwimMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "SwimMsgParams") {
        fIsEntering = tag->getParam("IsEntering", "false").to_bool();
    } else if (tag->getName() == "SwimRegion") {
        if (tag->hasChildren())
            fSwimRegion = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}
