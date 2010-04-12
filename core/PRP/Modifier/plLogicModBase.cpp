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

#include "plLogicModBase.h"

plLogicModBase::plLogicModBase()
              : fNotify(NULL), fDisabled(false) {
    fLogicFlags.setName(kLocalElement, "kLocalElement");
    fLogicFlags.setName(kReset, "kReset");
    fLogicFlags.setName(kTriggered, "kTriggered");
    fLogicFlags.setName(kOneShot, "kOneShot");
    fLogicFlags.setName(kRequestingTrigger, "kRequestingTrigger");
    fLogicFlags.setName(kTypeActivator, "kTypeActivator");
    fLogicFlags.setName(kMultiTrigger, "kMultiTrigger");
}

plLogicModBase::~plLogicModBase() {
    for (size_t i=0; i<fCommandList.getSize(); i++)
        delete fCommandList[i];
    delete fNotify;
}

void plLogicModBase::read(hsStream* S, plResManager* mgr) {
    plSingleModifier::read(S, mgr);

    clearCommands();
    fCommandList.setSizeNull(S->readInt());
    for (size_t i=0; i<fCommandList.getSize(); i++)
        fCommandList[i] = plMessage::Convert(mgr->ReadCreatable(S));

    setNotify(plNotifyMsg::Convert(mgr->ReadCreatable(S)));
    fLogicFlags.read(S);
    fDisabled = S->readBool();
}

void plLogicModBase::write(hsStream* S, plResManager* mgr) {
    plSingleModifier::write(S, mgr);

    S->writeInt(fCommandList.getSize());
    for (size_t i=0; i<fCommandList.getSize(); i++)
        mgr->WriteCreatable(S, fCommandList[i]);

    mgr->WriteCreatable(S, fNotify);
    fLogicFlags.write(S);
    S->writeBool(fDisabled);
}

void plLogicModBase::IPrcWrite(pfPrcHelper* prc) {
    plSingleModifier::IPrcWrite(prc);

    prc->startTag("LogicModParams");
    prc->writeParam("Disabled", fDisabled);
    prc->endTag(true);

    prc->writeSimpleTag("Commands");
    for (size_t i=0; i<fCommandList.getSize(); i++)
        fCommandList[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Notify");
    fNotify->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("LogicFlags");
    fLogicFlags.prcWrite(prc);
    prc->closeTag();
}

void plLogicModBase::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "LogicModParams") {
        fDisabled = tag->getParam("Disabled", "false").toBool();
    } else if (tag->getName() == "Commands") {
        clearCommands();
        fCommandList.setSizeNull(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fCommandList.getSize(); i++) {
            fCommandList[i] = plMessage::Convert(mgr->prcParseCreatable(child));
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Notify") {
        if (tag->hasChildren())
            setNotify(plNotifyMsg::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
    } else if (tag->getName() == "LogicFlags") {
        if (tag->hasChildren())
            fLogicFlags.prcParse(tag->getFirstChild());
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}

void plLogicModBase::delCommand(size_t idx) {
    delete fCommandList[idx];
    fCommandList.remove(idx);
}

void plLogicModBase::clearCommands() {
    for (size_t i=0; i<fCommandList.getSize(); i++)
        delete fCommandList[i];
    fCommandList.clear();
}

void plLogicModBase::setNotify(plNotifyMsg* notify) {
    delete fNotify;
    fNotify = notify;
}
