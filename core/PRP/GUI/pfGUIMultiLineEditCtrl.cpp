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

#include "pfGUIMultiLineEditCtrl.h"

void pfGUIMultiLineEditCtrl::read(hsStream* S, plResManager* mgr)
{
    pfGUIControlMod::read(S, mgr);

    if (S->readBool())
        fScrollCtrl = mgr->readKey(S);
}

void pfGUIMultiLineEditCtrl::write(hsStream* S, plResManager* mgr)
{
    pfGUIControlMod::write(S, mgr);

    if (fScrollCtrl.Exists()) {
        S->writeBool(true);
        mgr->writeKey(S, fScrollCtrl);
    } else {
        S->writeBool(false);
    }
}

void pfGUIMultiLineEditCtrl::IPrcWrite(pfPrcHelper* prc)
{
    pfGUIControlMod::IPrcWrite(prc);

    prc->writeSimpleTag("ScrollControl");
    plResManager::PrcWriteKey(prc, fScrollCtrl);
    prc->closeTag();
}

void pfGUIMultiLineEditCtrl::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "ScrollControl") {
        if (tag->hasChildren())
            fScrollCtrl = mgr->prcParseKey(tag->getFirstChild());
    } else {
        pfGUIControlMod::IPrcParse(tag, mgr);
    }
}
