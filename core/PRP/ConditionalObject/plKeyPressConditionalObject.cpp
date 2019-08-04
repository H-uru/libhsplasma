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

#include "plKeyPressConditionalObject.h"

void plKeyPressConditionalObject::read(hsStream* S, plResManager* mgr)
{
    plConditionalObject::read(S, mgr);
    fKeyEvent = (plKeyDef)S->readInt();
}

void plKeyPressConditionalObject::write(hsStream* S, plResManager* mgr)
{
    plConditionalObject::write(S, mgr);
    S->writeInt(fKeyEvent);
}

void plKeyPressConditionalObject::IPrcWrite(pfPrcHelper* prc)
{
    plConditionalObject::IPrcWrite(prc);
    prc->startTag("KeyEvent");
    prc->writeParam("value", fKeyEvent);
    prc->endTag(true);
}

void plKeyPressConditionalObject::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "KeyEvent") {
        fKeyEvent = (plKeyDef)tag->getParam("value", "0").to_int();
    } else {
        plConditionalObject::IPrcParse(tag, mgr);
    }
}
