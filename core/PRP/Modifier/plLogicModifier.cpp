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

#include "plLogicModifier.h"

plLogicModifier::plLogicModifier() : fMyCursor(0) { }

void plLogicModifier::read(hsStream* S, plResManager* mgr) {
    plLogicModBase::read(S, mgr);

    size_t count = S->readInt();
    fConditionList.setSize(count);
    for (size_t i=0; i<count; i++)
        fConditionList[i] = mgr->readKey(S);
    fMyCursor = S->readInt();

    if (S->getVer() >= pvEoa)
        fParent = mgr->readKey(S);
}

void plLogicModifier::write(hsStream* S, plResManager* mgr) {
    plLogicModBase::write(S, mgr);

    S->writeInt(fConditionList.getSize());
    for (size_t i=0; i<fConditionList.getSize(); i++)
        mgr->writeKey(S, fConditionList[i]);
    S->writeInt(fMyCursor);

    if (S->getVer() >= pvEoa)
        mgr->writeKey(S, fParent);
}

void plLogicModifier::IPrcWrite(pfPrcHelper* prc) {
    plLogicModBase::IPrcWrite(prc);

    prc->writeSimpleTag("Conditions");
    for (size_t i=0; i<fConditionList.getSize(); i++)
        fConditionList[i]->prcWrite(prc);
    prc->closeTag();

    prc->startTag("LogicModifierParams");
    prc->writeParam("MyCursor", fMyCursor);
    prc->endTag(true);

    prc->writeSimpleTag("Parent");
    fParent->prcWrite(prc);
    prc->closeTag();
}

void plLogicModifier::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Conditions") {
        fConditionList.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fConditionList.getSize(); i++) {
            fConditionList[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "LogicModifierParams") {
        fMyCursor = tag->getParam("MyCursor", "0").toUint();
    } else if (tag->getName() == "Parent") {
        if (tag->hasChildren())
            fParent = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plLogicModBase::IPrcParse(tag, mgr);
    }
}
