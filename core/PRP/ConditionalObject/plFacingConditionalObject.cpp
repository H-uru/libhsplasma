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

#include "plFacingConditionalObject.h"

void plFacingConditionalObject::read(hsStream* S, plResManager* mgr)
{
    plConditionalObject::read(S, mgr);
    fTolerance = S->readFloat();
    fDirectional = S->readBool();
}

void plFacingConditionalObject::write(hsStream* S, plResManager* mgr)
{
    plConditionalObject::write(S, mgr);
    S->writeFloat(fTolerance);
    S->writeBool(fDirectional);
}

void plFacingConditionalObject::IPrcWrite(pfPrcHelper* prc)
{
    plConditionalObject::IPrcWrite(prc);
    prc->startTag("FacingParams");
    prc->writeParam("Tolerance", fTolerance);
    prc->writeParam("Directional", fDirectional);
    prc->endTag(true);
}

void plFacingConditionalObject::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "FacingParams") {
        fTolerance = tag->getParam("Tolerance", "0").to_float();
        fDirectional = tag->getParam("Directional", "false").to_bool();
    } else {
        plConditionalObject::IPrcParse(tag, mgr);
    }
}
