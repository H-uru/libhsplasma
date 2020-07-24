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

#include "plTransitionMsg.h"

void plTransitionMsg::read(hsStream* S, plResManager* mgr)
{
    plMessageWithCallbacks::read(S, mgr);

    fEffect = S->readInt();
    fLengthInSecs = S->readFloat();
    fHoldUntilNext = S->readInt();
}

void plTransitionMsg::write(hsStream* S, plResManager* mgr)
{
    plMessageWithCallbacks::write(S, mgr);

    S->writeInt(fEffect);
    S->writeFloat(fLengthInSecs);
    S->writeInt(fHoldUntilNext);
}

void plTransitionMsg::IPrcWrite(pfPrcHelper* prc)
{
    plMessageWithCallbacks::IPrcWrite(prc);

    prc->startTag("TransitionParams");
    prc->writeParam("Effect", fEffect);
    prc->writeParam("Length", fLengthInSecs);
    prc->writeParam("HoldUntilNext", fHoldUntilNext);
    prc->endTag(true);
}

void plTransitionMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "TransitionParams") {
        fEffect = tag->getParam("Effect", "0").to_uint();
        fLengthInSecs = tag->getParam("Length", "0").to_float();
        fHoldUntilNext = tag->getParam("HoldUntilNext", "0").to_int();
    } else {
        plMessageWithCallbacks::IPrcParse(tag, mgr);
    }
}
