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

#include "plVolumeSensorConditionalObject.h"

/* plVolumeSensorConditionalObject */
void plVolumeSensorConditionalObject::read(hsStream* S, plResManager* mgr)
{
    plConditionalObject::read(S, mgr);
    fTrigNum = S->readInt();
    fType = S->readInt();
    fFirst = S->readBool();
}

void plVolumeSensorConditionalObject::write(hsStream* S, plResManager* mgr)
{
    plConditionalObject::write(S, mgr);
    S->writeInt(fTrigNum);
    S->writeInt(fType);
    S->writeBool(fFirst);
}

void plVolumeSensorConditionalObject::IPrcWrite(pfPrcHelper* prc)
{
    plConditionalObject::IPrcWrite(prc);
    prc->startTag("VolumeSensorParams");
    prc->writeParam("TrigNum", fTrigNum);
    prc->writeParam("Type", fType);
    prc->writeParam("First", fFirst);
    prc->endTag(true);
}

void plVolumeSensorConditionalObject::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "VolumeSensorParams") {
        fTrigNum = tag->getParam("TrigNum", "0").to_int();
        fType = tag->getParam("Type", "0").to_int();
        fFirst = tag->getParam("First", "false").to_bool();
    } else {
        plConditionalObject::IPrcParse(tag, mgr);
    }
}
