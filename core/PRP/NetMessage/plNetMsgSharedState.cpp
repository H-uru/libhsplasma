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

#include "plNetMsgSharedState.h"

/* plNetMsgSharedState */
void plNetMsgSharedState::read(hsStream* S, plResManager* mgr)
{
    plNetMsgStreamedObject::read(S, mgr);

    fState.read(getStream());
    fLockRequest = S->readByte();
}

void plNetMsgSharedState::write(hsStream* S, plResManager* mgr)
{
    plNetMsgStreamedObject::write(S, mgr);

    S->writeByte(fLockRequest);
}

void plNetMsgSharedState::IPrcWrite(pfPrcHelper* prc)
{
    plNetMsgObject::IPrcWrite(prc); // Skip the binary stream

    prc->writeSimpleTag("State");
    fState.prcWrite(prc);
    prc->closeTag();
}

void plNetMsgSharedState::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "State") {
        if (tag->hasChildren())
            fState.prcParse(tag);
    } else {
        // Skip the binary stream
        plNetMsgObject::IPrcParse(tag, mgr);
    }
}
