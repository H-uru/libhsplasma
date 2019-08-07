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

#include "plScaleController.h"

/* plSimpleScaleController */
plSimpleScaleController::~plSimpleScaleController()
{
    delete fValue;
}

void plSimpleScaleController::read(hsStream* S, plResManager* mgr)
{
    if (S->readInt() != 0) {
        setValue(new plScaleValueController());
        fValue->read(S, mgr);
    } else {
        setValue(nullptr);
    }
}

void plSimpleScaleController::write(hsStream* S, plResManager* mgr)
{
    if (fValue) {
        S->writeInt(1);
        fValue->write(S, mgr);
    } else {
        S->writeInt(0);
    }
}

void plSimpleScaleController::IPrcWrite(pfPrcHelper* prc)
{
    if (fValue) {
        fValue->prcWrite(prc);
    } else {
        prc->startTag("plScaleValueController");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
}

void plSimpleScaleController::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "plScaleValueController") {
        if (!tag->getParam("NULL", "false").to_bool()) {
            setValue(new plScaleValueController());
            fValue->prcParse(tag, mgr);
        } else {
            setValue(nullptr);
        }
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

void plSimpleScaleController::setValue(plScaleValueController* value)
{
    delete fValue;
    fValue = value;
}
