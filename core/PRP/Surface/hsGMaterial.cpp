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

#include "hsGMaterial.h"

hsGMaterial::hsGMaterial() : fCompFlags(0), fLoadFlags(0) { }

void hsGMaterial::read(hsStream* S, plResManager* mgr) {
    plSynchedObject::read(S, mgr);

    fLoadFlags = S->readInt();
    fCompFlags = S->readInt();
    fLayers.setSize(S->readInt());
    fPiggyBacks.setSize(S->readInt());

    for (size_t i=0; i<fLayers.getSize(); i++)
        fLayers[i] = mgr->readKey(S);
    for (size_t i=0; i<fPiggyBacks.getSize(); i++)
        fPiggyBacks[i] = mgr->readKey(S);
}

void hsGMaterial::write(hsStream* S, plResManager* mgr) {
    plSynchedObject::write(S, mgr);

    S->writeInt(fLoadFlags);
    S->writeInt(fCompFlags);
    S->writeInt(fLayers.getSize());
    S->writeInt(fPiggyBacks.getSize());

    for (size_t i=0; i<fLayers.getSize(); i++)
        mgr->writeKey(S, fLayers[i]);
    for (size_t i=0; i<fPiggyBacks.getSize(); i++)
        mgr->writeKey(S, fPiggyBacks[i]);
}

void hsGMaterial::IPrcWrite(pfPrcHelper* prc) {
    plSynchedObject::IPrcWrite(prc);

    prc->startTag("MaterialParams");
    prc->writeParamHex("LoadFlags", fLoadFlags);
    prc->writeParamHex("CompFlags", fCompFlags);
    prc->endTag(true);

    prc->writeSimpleTag("Layers");
    for (size_t i=0; i<fLayers.getSize(); i++)
        fLayers[i]->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("PiggyBacks");
    for (size_t i=0; i<fPiggyBacks.getSize(); i++)
        fPiggyBacks[i]->prcWrite(prc);
    prc->closeTag();
}

void hsGMaterial::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "MaterialParams") {
        fLoadFlags = tag->getParam("LoadFlags", "0").toUint();
        fCompFlags = tag->getParam("CompFlags", "0").toUint();
    } else if (tag->getName() == "Layers") {
        fLayers.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fLayers.getSize(); i++) {
            fLayers[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "PiggyBacks") {
        fPiggyBacks.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fPiggyBacks.getSize(); i++) {
            fPiggyBacks[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        plSynchedObject::IPrcParse(tag, mgr);
    }
}
