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

#include "plBlower.h"

void plBlower::read(hsStream* S, plResManager* mgr)
{
    plSingleModifier::read(S, mgr);

    fMasterPower = S->readFloat();
    fDirectRate = S->readFloat();
    fImpulseRate = S->readFloat();
    fSpringKonst = S->readFloat();
}

void plBlower::write(hsStream* S, plResManager* mgr)
{
    plSingleModifier::write(S, mgr);

    S->writeFloat(fMasterPower);
    S->writeFloat(fDirectRate);
    S->writeFloat(fImpulseRate);
    S->writeFloat(fSpringKonst);
}

void plBlower::IPrcWrite(pfPrcHelper* prc)
{
    plSingleModifier::IPrcWrite(prc);

    prc->startTag("BlowerParams");
    prc->writeParam("MasterPower", fMasterPower);
    prc->writeParam("DirectRate", fDirectRate);
    prc->writeParam("ImpulseRate", fImpulseRate);
    prc->writeParam("SpringKonst", fSpringKonst);
    prc->endTag(true);
}

void plBlower::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "BlowerParams") {
        fMasterPower = tag->getParam("MasterPower", "0").to_float();
        fDirectRate = tag->getParam("DirectRate", "0").to_float();
        fImpulseRate = tag->getParam("ImpulseRate", "0").to_float();
        fSpringKonst = tag->getParam("SpringKonst", "0").to_float();
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}
