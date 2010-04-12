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

#include "pfGUIProgressCtrl.h"

pfGUIProgressCtrl::pfGUIProgressCtrl() {
    fFlags.setName(kReverseValues, "kReverseValues");
    fFlags.setName(kLeftRightOrientation, "kLeftRightOrientation");
    fFlags.setName(kMapToScreenRange, "kMapToScreenRange");
    fFlags.setName(kTriggerOnlyOnMouseUp, "kTriggerOnlyOnMouseUp");
    fFlags.setName(kMapToAnimationRange, "kMapToAnimationRange");
}

void pfGUIProgressCtrl::read(hsStream* S, plResManager* mgr) {
    pfGUIValueCtrl::read(S, mgr);

    fAnimationKeys.setSize(S->readInt());
    for (size_t i=0; i<fAnimationKeys.getSize(); i++)
        fAnimationKeys[i] = mgr->readKey(S);

    fAnimName = S->readSafeStr();
}

void pfGUIProgressCtrl::write(hsStream* S, plResManager* mgr) {
    pfGUIValueCtrl::write(S, mgr);

    S->writeInt(fAnimationKeys.getSize());
    for (size_t i=0; i<fAnimationKeys.getSize(); i++)
        mgr->writeKey(S, fAnimationKeys[i]);

    S->writeSafeStr(fAnimName);
}

void pfGUIProgressCtrl::IPrcWrite(pfPrcHelper* prc) {
    pfGUIValueCtrl::IPrcWrite(prc);

    prc->startTag("Animation");
    prc->writeParam("Name", fAnimName);
    prc->endTag();
    for (size_t i=0; i<fAnimationKeys.getSize(); i++)
        fAnimationKeys[i]->prcWrite(prc);
    prc->closeTag();
}

void pfGUIProgressCtrl::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Animation") {
        fAnimName = tag->getParam("Name", "");
        fAnimationKeys.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fAnimationKeys.getSize(); i++) {
            fAnimationKeys[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        pfGUIValueCtrl::IPrcParse(tag, mgr);
    }
}
