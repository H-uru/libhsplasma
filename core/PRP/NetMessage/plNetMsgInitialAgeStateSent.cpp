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

#include "plNetMsgInitialAgeStateSent.h"

void plNetMsgInitialAgeStateSent::read(hsStream* S, plResManager* mgr)
{
    plNetMessage::read(S, mgr);
    fNumInitialStates = S->readInt();
}

void plNetMsgInitialAgeStateSent::write(hsStream* S, plResManager* mgr)
{
    plNetMessage::write(S, mgr);
    S->writeInt(fNumInitialStates);
}

void plNetMsgInitialAgeStateSent::IPrcWrite(pfPrcHelper* prc)
{
    plNetMessage::IPrcWrite(prc);

    prc->startTag("InitialAgeStateParams");
    prc->writeParam("NumInitialStates", fNumInitialStates);
    prc->endTag(true);
}

void plNetMsgInitialAgeStateSent::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "InitialAgeStateParams") {
        fNumInitialStates = tag->getParam("NumInitialStates", "0").to_uint();
    } else {
        plNetMessage::IPrcParse(tag, mgr);
    }
}
