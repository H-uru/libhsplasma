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

#include "plMultistageBehMod.h"

plMultistageBehMod::plMultistageBehMod()
                  : fFreezePhys(false), fSmartSeek(false),
                    fReverseFBControlsOnRelease(false) { }

plMultistageBehMod::~plMultistageBehMod() {
    for (size_t i=0; i<fStages.getSize(); i++)
        delete fStages[i];
}

void plMultistageBehMod::read(hsStream* S, plResManager* mgr) {
    plSingleModifier::read(S, mgr);

    fFreezePhys = S->readBool();
    fSmartSeek = S->readBool();
    fReverseFBControlsOnRelease = S->readBool();

    clearStages();
    fStages.setSizeNull(S->readInt());
    for (size_t i=0; i<fStages.getSize(); i++) {
        fStages[i] = new plAnimStage();
        fStages[i]->read(S, mgr);
    }

    fReceivers.setSize(S->readInt());
    for (size_t i=0; i<fReceivers.getSize(); i++)
        fReceivers[i] = mgr->readKey(S);
}

void plMultistageBehMod::write(hsStream* S, plResManager* mgr) {
    plSingleModifier::write(S, mgr);

    S->writeBool(fFreezePhys);
    S->writeBool(fSmartSeek);
    S->writeBool(fReverseFBControlsOnRelease);

    S->writeInt(fStages.getSize());
    for (size_t i=0; i<fStages.getSize(); i++)
        fStages[i]->write(S, mgr);

    S->writeInt(fReceivers.getSize());
    for (size_t i=0; i<fReceivers.getSize(); i++)
        mgr->writeKey(S, fReceivers[i]);
}

void plMultistageBehMod::IPrcWrite(pfPrcHelper* prc) {
    plSingleModifier::IPrcWrite(prc);

    prc->startTag("MultistageBehParams");
    prc->writeParam("FreezePhys", fFreezePhys);
    prc->writeParam("SmartSeek", fSmartSeek);
    prc->writeParam("ReverseFBControlsOnRelease", fReverseFBControlsOnRelease);
    prc->endTag(true);

    prc->writeSimpleTag("Stages");
    for (size_t i=0; i<fStages.getSize(); i++)
        fStages[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Receivers");
    for (size_t i=0; i<fReceivers.getSize(); i++)
        fReceivers[i]->prcWrite(prc);
    prc->closeTag();
}

void plMultistageBehMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "MultistageBehParams") {
        fFreezePhys = tag->getParam("FreezePhys", "false").toBool();
        fSmartSeek = tag->getParam("SmartSeek", "false").toBool();
        fReverseFBControlsOnRelease = tag->getParam("ReverseFBControlsOnRelease", "false").toBool();
    } else if (tag->getName() == "Stages") {
        clearStages();
        fStages.setSizeNull(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fStages.getSize(); i++) {
            fStages[i] = new plAnimStage();
            fStages[i]->prcParse(child, mgr);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Receivers") {
        fReceivers.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fReceivers.getSize(); i++) {
            fReceivers[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}

void plMultistageBehMod::delStage(size_t idx) {
    delete fStages[idx];
    fStages.remove(idx);
}

void plMultistageBehMod::clearStages() {
    for (size_t i=0; i<fStages.getSize(); i++)
        delete fStages[i];
    fStages.clear();
}
