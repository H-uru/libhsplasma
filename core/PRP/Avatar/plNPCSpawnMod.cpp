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

#include "plNPCSpawnMod.h"

plNPCSpawnMod::~plNPCSpawnMod()
{
    delete fNotify;
}

void plNPCSpawnMod::read(hsStream* S, plResManager* mgr)
{
    plSingleModifier::read(S, mgr);

    fModelName = S->readSafeStr();
    fAccountName = S->readSafeStr();
    fAutoSpawn = S->readBool();

    if (S->readBool())
        setNotify(mgr->ReadCreatableC<plNotifyMsg>(S));
}

void plNPCSpawnMod::write(hsStream* S, plResManager* mgr)
{
    plSingleModifier::write(S, mgr);

    S->writeSafeStr(fModelName);
    S->writeSafeStr(fAccountName);
    S->writeBool(fAutoSpawn);

    S->writeBool(fNotify != nullptr);
    if (fNotify)
        mgr->WriteCreatable(S, fNotify);
}

void plNPCSpawnMod::IPrcWrite(pfPrcHelper* prc)
{
    plSingleModifier::IPrcWrite(prc);

    prc->startTag("NPCSpawnParams");
    prc->writeParam("ModelName", fModelName);
    prc->writeParam("AccountName", fAccountName);
    prc->writeParam("AutoSpawn", fAutoSpawn);
    prc->endTag(true);

    if (fNotify) {
        prc->writeSimpleTag("Notify");
        fNotify->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("Notify");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
}

void plNPCSpawnMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "NPCSpawnParams") {
        fModelName = tag->getParam("ModelName", "");
        fAccountName = tag->getParam("AccountName", "");
        fAutoSpawn = tag->getParam("AutoSpawn", "false").to_bool();
    } else if (tag->getName() == "Notify") {
        if (tag->getParam("NULL", "false").to_bool()) {
            setNotify(nullptr);
        } else if (tag->hasChildren()) {
            setNotify(mgr->prcParseCreatableC<plNotifyMsg>(tag->getFirstChild()));
        }
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}

void plNPCSpawnMod::setNotify(plNotifyMsg* msg)
{
    delete fNotify;
    fNotify = msg;
}
