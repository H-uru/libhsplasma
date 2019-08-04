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

#include "pfGUIUpDownPairMod.h"
#include "pfGUIButtonMod.h"

void pfGUIUpDownPairMod::read(hsStream* S, plResManager* mgr)
{
    pfGUIValueCtrl::read(S, mgr);

    fUpControl = mgr->readKey(S);
    fDownControl = mgr->readKey(S);
    fMin = S->readFloat();  // Seriously...
    fMax = S->readFloat();
    fStep = S->readFloat();
}

void pfGUIUpDownPairMod::write(hsStream* S, plResManager* mgr)
{
    pfGUIValueCtrl::write(S, mgr);

    mgr->writeKey(S, fUpControl);
    mgr->writeKey(S, fDownControl);
    S->writeFloat(fMin);
    S->writeFloat(fMax);
    S->writeFloat(fStep);
}

void pfGUIUpDownPairMod::IPrcWrite(pfPrcHelper* prc)
{
    pfGUIValueCtrl::IPrcWrite(prc);

    prc->writeSimpleTag("UpControl");
    plResManager::PrcWriteKey(prc, fUpControl);
    prc->closeTag();
    prc->writeSimpleTag("DownControl");
    plResManager::PrcWriteKey(prc, fDownControl);
    prc->closeTag();
}

void pfGUIUpDownPairMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "UpControl") {
        if (tag->hasChildren())
            fUpControl = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "DownControl") {
        if (tag->hasChildren())
            fDownControl = mgr->prcParseKey(tag->getFirstChild());
    } else {
        pfGUIValueCtrl::IPrcParse(tag, mgr);
    }
}
