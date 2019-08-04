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

#include "plResponderMsg.h"

/* plOneShotMsg */
void plOneShotMsg::read(hsStream* S, plResManager* mgr)
{
    plMessage::read(S, mgr);
    fCallbacks.read(S, mgr);
}

void plOneShotMsg::write(hsStream* S, plResManager* mgr)
{
    plMessage::write(S, mgr);
    fCallbacks.write(S, mgr);
}

void plOneShotMsg::IPrcWrite(pfPrcHelper* prc)
{
    plMessage::IPrcWrite(prc);
    fCallbacks.prcWrite(prc);
}

void plOneShotMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if  (tag->getName() == "plOneShotCallbacks") {
        fCallbacks.prcParse(tag, mgr);
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}
