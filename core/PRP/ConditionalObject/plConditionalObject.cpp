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

#include "plConditionalObject.h"

/* plConditionalObject */
void plConditionalObject::read(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::read(S, mgr);
    fSatisfied = S->readBool();
    fToggle = S->readBool();
}

void plConditionalObject::write(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::write(S, mgr);
    S->writeBool(fSatisfied);
    S->writeBool(fToggle);
}

void plConditionalObject::IPrcWrite(pfPrcHelper* prc)
{
    hsKeyedObject::IPrcWrite(prc);
    prc->startTag("ConditionFlags");
    prc->writeParam("satisfied", fSatisfied);
    prc->writeParam("toggle", fToggle);
    prc->endTag(true);
}

void plConditionalObject::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "ConditionFlags") {
        fSatisfied = tag->getParam("satisfied", "false").to_bool();
        fToggle = tag->getParam("toggle", "false").to_bool();
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}
