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

#include "plTimerCallbackMsg.h"

void plTimerCallbackMsg::read(hsStream* S, plResManager* mgr)
{
    plMessage::read(S, mgr);
    fID = S->readInt();
    fTime = S->readFloat();
}

void plTimerCallbackMsg::write(hsStream* S, plResManager* mgr)
{
    plMessage::write(S, mgr);
    S->writeInt(fID);
    S->writeFloat(fTime);
}

void plTimerCallbackMsg::IPrcWrite(pfPrcHelper* prc)
{
    plMessage::IPrcWrite(prc);

    prc->startTag("TimerCallback");
    prc->writeParam("ID", fID);
    prc->writeParam("Time", fTime);
    prc->endTag(true);
}

void plTimerCallbackMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "TimerCallback") {
        fID = tag->getParam("ID", "0").to_uint();
        fTime = tag->getParam("Time", "0").to_float();
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}
