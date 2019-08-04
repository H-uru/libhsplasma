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

#include "pfGUIValueCtrl.h"

void pfGUIValueCtrl::read(hsStream* S, plResManager* mgr)
{
    pfGUIControlMod::read(S, mgr);

    fMin = S->readFloat();
    fMax = S->readFloat();
    fStep = S->readFloat();
}

void pfGUIValueCtrl::write(hsStream* S, plResManager* mgr)
{
    pfGUIControlMod::write(S, mgr);

    S->writeFloat(fMin);
    S->writeFloat(fMax);
    S->writeFloat(fStep);
}

void pfGUIValueCtrl::IPrcWrite(pfPrcHelper* prc)
{
    pfGUIControlMod::IPrcWrite(prc);

    prc->startTag("ValueRange");
    prc->writeParam("Min", fMin);
    prc->writeParam("Max", fMax);
    prc->writeParam("Step", fStep);
    prc->endTag(true);
}

void pfGUIValueCtrl::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "ValueRange") {
        fMin = tag->getParam("Min", "0").to_float();
        fMax = tag->getParam("Max", "0").to_float();
        fStep = tag->getParam("Step", "0").to_float();
    } else {
        pfGUIControlMod::IPrcParse(tag, mgr);
    }
}
