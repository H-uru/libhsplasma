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

#include "plAccountUpdateMsg.h"

void plAccountUpdateMsg::read(hsStream* S, plResManager* mgr)
{
    plMessage::read(S, mgr);
    fUpdateType = S->readInt();
    fResult = S->readInt();
    fPlayer = S->readInt();
}

void plAccountUpdateMsg::write(hsStream* S, plResManager* mgr)
{
    plMessage::write(S, mgr);
    S->writeInt(fUpdateType);
    S->writeInt(fResult);
    S->writeInt(fPlayer);
}

void plAccountUpdateMsg::IPrcWrite(pfPrcHelper* prc)
{
    plMessage::IPrcWrite(prc);
    prc->startTag("AccountUpdate");
    prc->writeParam("UpdateType", fUpdateType);
    prc->writeParam("Result", fResult);
    prc->writeParam("Player", fPlayer);
}


void plAccountUpdateMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if(tag->getName() == "AccountUpdate") {
        fUpdateType = tag->getParam("UpdateType", "0").to_uint();
        fResult = tag->getParam("Result", "0").to_uint();
        fPlayer = tag->getParam("Player", "0").to_uint();
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}
