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

#include "plFadeOpacityMod.h"

void plFadeOpacityMod::read(hsStream* S, plResManager* mgr)
{
    plSingleModifier::read(S, mgr);
    fFadeUp = S->readFloat();
    fFadeDown = S->readFloat();
}

void plFadeOpacityMod::write(hsStream* S, plResManager* mgr)
{
    plSingleModifier::write(S, mgr);
    S->writeFloat(fFadeUp);
    S->writeFloat(fFadeDown);
}

void plFadeOpacityMod::IPrcWrite(pfPrcHelper* prc)
{
    plSingleModifier::IPrcWrite(prc);

    prc->startTag("FadeParams");
    prc->writeParam("Up", fFadeUp);
    prc->writeParam("Down", fFadeDown);
    prc->endTag(true);
}

void plFadeOpacityMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "FadeParams") {
        fFadeUp = tag->getParam("Up", "0").to_float();
        fFadeDown = tag->getParam("Down", "0").to_float();
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}
