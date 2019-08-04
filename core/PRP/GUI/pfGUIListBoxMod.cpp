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

#include "pfGUIListBoxMod.h"

/* pfGUIListElement */
void pfGUIListElement::read(hsStream* S)
{
    fSelected = S->readBool();
}

void pfGUIListElement::write(hsStream* S)
{
    S->writeBool(fSelected);
}

void pfGUIListElement::prcWrite(pfPrcHelper* prc)
{
    prc->startTag("pfGUIListElement");
    prc->writeParam("Selected", fSelected);
    prc->endTag(true);
}

void pfGUIListElement::prcParse(const pfPrcTag* tag)
{
    if (tag->getName() != "pfGUIListElement")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fSelected = tag->getParam("Selected", "false").to_bool();
}


/* pfGUIListBoxMod */
pfGUIListBoxMod::pfGUIListBoxMod()
{
    fFlags.setName(kSingleSelect, "kSingleSelect");
    fFlags.setName(kDragAndDropCapable, "kDragAndDropCapable");
    fFlags.setName(kDisableSelection, "kDisableSelection");
    fFlags.setName(kDisableKeyActions, "kDisableKeyActions");
    fFlags.setName(kAllowMultipleElementsPerRow, "kAllowMultipleElementsPerRow");
    fFlags.setName(kScrollLeftToRight, "kScrollLeftToRight");
    fFlags.setName(kAllowMousePassThrough, "kAllowMousePassThrough");
    fFlags.setName(kGrowLeavesAndProcessOxygen, "kGrowLeavesAndProcessOxygen");
    fFlags.setName(kHandsOffMultiSelect, "kHandsOffMultiSelect");
    fFlags.setName(kForbidNoSelection, "kForbidNoSelection");
}

void pfGUIListBoxMod::read(hsStream* S, plResManager* mgr)
{
    pfGUIControlMod::read(S, mgr);

    if (S->readBool())
        fScrollCtrl = mgr->readKey(S);
}

void pfGUIListBoxMod::write(hsStream* S, plResManager* mgr)
{
    pfGUIControlMod::write(S, mgr);

    if (fScrollCtrl.Exists()) {
        S->writeBool(true);
        mgr->writeKey(S, fScrollCtrl);
    } else {
        S->writeBool(false);
    }
}

void pfGUIListBoxMod::IPrcWrite(pfPrcHelper* prc)
{
    pfGUIControlMod::IPrcWrite(prc);

    prc->writeSimpleTag("ScrollControl");
    plResManager::PrcWriteKey(prc, fScrollCtrl);
    prc->closeTag();
}

void pfGUIListBoxMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "ScrollControl") {
        if (tag->hasChildren())
            fScrollCtrl = mgr->prcParseKey(tag->getFirstChild());
    } else {
        pfGUIControlMod::IPrcParse(tag, mgr);
    }
}
