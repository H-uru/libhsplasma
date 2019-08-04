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

#include "plAnimationEventConditionalObject.h"

void plAnimationEventConditionalObject::read(hsStream* S, plResManager* mgr)
{
    plConditionalObject::read(S, mgr);
    fTarget = mgr->readKey(S);
    fAction = (CallbackEvent)S->readInt();
}

void plAnimationEventConditionalObject::write(hsStream* S, plResManager* mgr)
{
    plConditionalObject::write(S, mgr);
    mgr->writeKey(S, fTarget);
    S->writeInt(fAction);
}

void plAnimationEventConditionalObject::IPrcWrite(pfPrcHelper* prc)
{
    plConditionalObject::IPrcWrite(prc);
    prc->writeSimpleTag("Target");
    plResManager::PrcWriteKey(prc, fTarget);
    prc->closeTag();
    prc->startTag("Action");
    prc->writeParam("value", fAction);
    prc->endTag(true);
}

void plAnimationEventConditionalObject::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Target") {
        if (tag->hasChildren())
            fTarget = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Action") {
        fAction = (CallbackEvent)tag->getParam("value", "0").to_int();
    } else {
        plConditionalObject::IPrcParse(tag, mgr);
    }
}
