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

#include "plInterfaceInfoModifier.h"

void plInterfaceInfoModifier::read(hsStream* S, plResManager* mgr) {
    plSingleModifier::read(S, mgr);

    fKeyList.setSize(S->readInt());
    for (size_t i=0; i<fKeyList.getSize(); i++)
        fKeyList[i] = mgr->readKey(S);
}

void plInterfaceInfoModifier::write(hsStream* S, plResManager* mgr) {
    plSingleModifier::write(S, mgr);

    S->writeInt(fKeyList.getSize());
    for (size_t i=0; i<fKeyList.getSize(); i++)
        mgr->writeKey(S, fKeyList[i]);
}

void plInterfaceInfoModifier::IPrcWrite(pfPrcHelper* prc) {
    plSingleModifier::IPrcWrite(prc);

    prc->writeSimpleTag("Keys");
    for (size_t i=0; i<fKeyList.getSize(); i++)
        fKeyList[i]->prcWrite(prc);
    prc->closeTag();
}

void plInterfaceInfoModifier::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Keys") {
        fKeyList.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fKeyList.getSize(); i++) {
            fKeyList[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}
