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

plMultistageBehMod::~plMultistageBehMod()
{
    for (auto stage = fStages.begin(); stage != fStages.end(); ++stage)
        delete *stage;
}

void plMultistageBehMod::read(hsStream* S, plResManager* mgr)
{
    plSingleModifier::read(S, mgr);

    fFreezePhys = S->readBool();
    fSmartSeek = S->readBool();
    fReverseFBControlsOnRelease = S->readBool();

    clearStages();
    fStages.resize(S->readInt());
    for (size_t i=0; i<fStages.size(); i++) {
        fStages[i] = new plAnimStage();
        fStages[i]->read(S, mgr);
    }

    fReceivers.resize(S->readInt());
    for (size_t i=0; i<fReceivers.size(); i++)
        fReceivers[i] = mgr->readKey(S);
}

void plMultistageBehMod::write(hsStream* S, plResManager* mgr)
{
    plSingleModifier::write(S, mgr);

    S->writeBool(fFreezePhys);
    S->writeBool(fSmartSeek);
    S->writeBool(fReverseFBControlsOnRelease);

    S->writeInt(fStages.size());
    for (size_t i=0; i<fStages.size(); i++)
        fStages[i]->write(S, mgr);

    S->writeInt(fReceivers.size());
    for (size_t i=0; i<fReceivers.size(); i++)
        mgr->writeKey(S, fReceivers[i]);
}

void plMultistageBehMod::IPrcWrite(pfPrcHelper* prc)
{
    plSingleModifier::IPrcWrite(prc);

    prc->startTag("MultistageBehParams");
    prc->writeParam("FreezePhys", fFreezePhys);
    prc->writeParam("SmartSeek", fSmartSeek);
    prc->writeParam("ReverseFBControlsOnRelease", fReverseFBControlsOnRelease);
    prc->endTag(true);

    prc->writeSimpleTag("Stages");
    for (size_t i=0; i<fStages.size(); i++)
        fStages[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Receivers");
    for (size_t i=0; i<fReceivers.size(); i++)
        plResManager::PrcWriteKey(prc, fReceivers[i]);
    prc->closeTag();
}

void plMultistageBehMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "MultistageBehParams") {
        fFreezePhys = tag->getParam("FreezePhys", "false").to_bool();
        fSmartSeek = tag->getParam("SmartSeek", "false").to_bool();
        fReverseFBControlsOnRelease = tag->getParam("ReverseFBControlsOnRelease", "false").to_bool();
    } else if (tag->getName() == "Stages") {
        clearStages();
        fStages.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fStages.size(); i++) {
            fStages[i] = new plAnimStage();
            fStages[i]->prcParse(child, mgr);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Receivers") {
        fReceivers.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fReceivers.size(); i++) {
            fReceivers[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}

void plMultistageBehMod::delStage(size_t idx)
{
    delete fStages[idx];
    fStages.erase(fStages.begin() + idx);
}

void plMultistageBehMod::clearStages()
{
    for (auto stage = fStages.begin(); stage != fStages.end(); ++stage)
        delete *stage;
    fStages.clear();
}
