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
    : fNotify(), fDisabled()
{
    fLogicFlags.setName(kLocalElement, "kLocalElement");
    fLogicFlags.setName(kReset, "kReset");
    fLogicFlags.setName(kTriggered, "kTriggered");
    fLogicFlags.setName(kOneShot, "kOneShot");
    fLogicFlags.setName(kRequestingTrigger, "kRequestingTrigger");
    fLogicFlags.setName(kTypeActivator, "kTypeActivator");
    fLogicFlags.setName(kMultiTrigger, "kMultiTrigger");
}

plLogicModBase::~plLogicModBase()
{
    for (auto cmd = fCommandList.begin(); cmd != fCommandList.end(); ++cmd)
        delete *cmd;
    delete fNotify;
}

void plLogicModBase::read(hsStream* S, plResManager* mgr)
{
    plSingleModifier::read(S, mgr);

    clearCommands();
    fCommandList.resize(S->readInt());
    for (size_t i=0; i<fCommandList.size(); i++)
        fCommandList[i] = mgr->ReadCreatableC<plMessage>(S);

    setNotify(mgr->ReadCreatableC<plNotifyMsg>(S));
    fLogicFlags.read(S);
    fDisabled = S->readBool();
}

void plLogicModBase::write(hsStream* S, plResManager* mgr)
{
    plSingleModifier::write(S, mgr);

    S->writeInt(fCommandList.size());
    for (size_t i=0; i<fCommandList.size(); i++)
        mgr->WriteCreatable(S, fCommandList[i]);

    mgr->WriteCreatable(S, fNotify);
    fLogicFlags.write(S);
    S->writeBool(fDisabled);
}

void plLogicModBase::IPrcWrite(pfPrcHelper* prc)
{
    plSingleModifier::IPrcWrite(prc);

    prc->startTag("LogicModParams");
    prc->writeParam("Disabled", fDisabled);
    prc->endTag(true);

    prc->writeSimpleTag("Commands");
    for (size_t i=0; i<fCommandList.size(); i++)
        fCommandList[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Notify");
    fNotify->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("LogicFlags");
    fLogicFlags.prcWrite(prc);
    prc->closeTag();
}

void plLogicModBase::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "LogicModParams") {
        fDisabled = tag->getParam("Disabled", "false").to_bool();
    } else if (tag->getName() == "Commands") {
        clearCommands();
        fCommandList.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fCommandList.size(); i++) {
            fCommandList[i] = mgr->prcParseCreatableC<plMessage>(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Notify") {
        if (tag->hasChildren())
            setNotify(mgr->prcParseCreatableC<plNotifyMsg>(tag->getFirstChild()));
    } else if (tag->getName() == "LogicFlags") {
        if (tag->hasChildren())
            fLogicFlags.prcParse(tag->getFirstChild());
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}

void plLogicModBase::delCommand(size_t idx)
{
    delete fCommandList[idx];
    fCommandList.erase(fCommandList.begin() + idx);
}

void plLogicModBase::clearCommands()
{
    for (auto cmd = fCommandList.begin(); cmd != fCommandList.end(); ++cmd)
        delete *cmd;
    fCommandList.clear();
}

void plLogicModBase::setNotify(plNotifyMsg* notify)
{
    delete fNotify;
    fNotify = notify;
}
