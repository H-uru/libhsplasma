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

#include "plDrawInterface.h"

/* plDrawInterface */
void plDrawInterface::read(hsStream* S, plResManager* mgr) {
    plObjInterface::read(S, mgr);

    fDrawables.setSize(S->readInt());
    fDrawableKeys.setSize(fDrawables.getSize());
    for (size_t i=0; i<fDrawables.getSize(); i++) {
        fDrawableKeys[i] = S->readInt();
        fDrawables[i] = mgr->readKey(S);
    }
    fRegions.setSize(S->readInt());
    for (size_t i=0; i<fRegions.getSize(); i++)
        fRegions[i] = mgr->readKey(S);
}

void plDrawInterface::write(hsStream* S, plResManager* mgr) {
    plObjInterface::write(S, mgr);

    S->writeInt(fDrawables.getSize());
    for (size_t i=0; i<fDrawables.getSize(); i++) {
        S->writeInt(fDrawableKeys[i]);
        mgr->writeKey(S, fDrawables[i]);
    }
    S->writeInt(fRegions.getSize());
    for (size_t i=0; i<fRegions.getSize(); i++)
        mgr->writeKey(S, fRegions[i]);
}

void plDrawInterface::IPrcWrite(pfPrcHelper* prc) {
    plObjInterface::IPrcWrite(prc);

    prc->writeSimpleTag("Drawables");
    for (size_t i=0; i<fDrawables.getSize(); i++) {
        prc->startTag("Drawable");
        prc->writeParam("key", fDrawableKeys[i]);
        prc->endTag();
        fDrawables[i]->prcWrite(prc);
        prc->closeTag();
    }
    prc->closeTag();
    prc->writeSimpleTag("Regions");
    for (size_t i=0; i<fRegions.getSize(); i++)
        fRegions[i]->prcWrite(prc);
    prc->closeTag();
}

void plDrawInterface::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Drawables") {
        fDrawables.setSize(tag->countChildren());
        fDrawableKeys.setSizeNull(fDrawables.getSize());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fDrawables.getSize(); i++) {
            if (child->getName() != "Drawable")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            fDrawableKeys[i] = child->getParam("key", "0").toInt();
            if (child->hasChildren())
                fDrawables[i] = mgr->prcParseKey(child->getFirstChild());
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Regions") {
        fRegions.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fRegions.getSize(); i++) {
            fRegions[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        plObjInterface::IPrcParse(tag, mgr);
    }
}

void plDrawInterface::clearDrawables() {
    fDrawables.clear();
    fDrawableKeys.clear();
}

void plDrawInterface::addDrawable(plKey draw, int key) {
    fDrawables.append(draw);
    fDrawableKeys.append(key);
}

void plDrawInterface::delDrawable(size_t idx) {
    fDrawables.remove(idx);
    fDrawableKeys.remove(idx);
}


/* plInstanceDrawInterface */
plInstanceDrawInterface::plInstanceDrawInterface() : fTargetID(0) { }

void plInstanceDrawInterface::read(hsStream* S, plResManager* mgr) {
    plDrawInterface::read(S, mgr);

    fTargetID = S->readInt();
    fDrawable = mgr->readKey(S);
}

void plInstanceDrawInterface::write(hsStream* S, plResManager* mgr) {
    plDrawInterface::write(S, mgr);

    S->writeInt(fTargetID);
    mgr->writeKey(S, fDrawable);
}

void plInstanceDrawInterface::IPrcWrite(pfPrcHelper* prc) {
    plDrawInterface::IPrcWrite(prc);

    prc->startTag("Target");
    prc->writeParam("ID", fTargetID);
    prc->endTag();
    fDrawable->prcWrite(prc);
    prc->closeTag();
}

void plInstanceDrawInterface::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Target") {
        fTargetID = tag->getParam("ID", "0").toUint();
        if (tag->hasChildren())
            fDrawable = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plDrawInterface::IPrcParse(tag, mgr);
    }
}
