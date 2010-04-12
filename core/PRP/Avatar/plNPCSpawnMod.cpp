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

plNPCSpawnMod::plNPCSpawnMod() : fAutoSpawn(false), fNotify(NULL) { }

plNPCSpawnMod::~plNPCSpawnMod() {
    delete fNotify;
}

void plNPCSpawnMod::read(hsStream* S, plResManager* mgr) {
    plSingleModifier::read(S, mgr);

    fModelName = S->readSafeStr();
    fAccountName = S->readSafeStr();
    fAutoSpawn = S->readBool();

    if (S->readBool())
        setNotify(plNotifyMsg::Convert(mgr->ReadCreatable(S)));
}

void plNPCSpawnMod::write(hsStream* S, plResManager* mgr) {
    plSingleModifier::write(S, mgr);

    S->writeSafeStr(fModelName);
    S->writeSafeStr(fAccountName);
    S->writeBool(fAutoSpawn);

    S->writeBool(fNotify != NULL);
    if (fNotify != NULL)
        mgr->WriteCreatable(S, fNotify);
}

void plNPCSpawnMod::IPrcWrite(pfPrcHelper* prc) {
    plSingleModifier::IPrcWrite(prc);

    prc->startTag("NPCSpawnParams");
    prc->writeParam("ModelName", fModelName);
    prc->writeParam("AccountName", fAccountName);
    prc->writeParam("AutoSpawn", fAutoSpawn);
    prc->endTag(true);

    if (fNotify != NULL) {
        prc->writeSimpleTag("Notify");
        fNotify->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("Notify");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
}

void plNPCSpawnMod::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "NPCSpawnParams") {
        fModelName = tag->getParam("ModelName", "");
        fAccountName = tag->getParam("AccountName", "");
        fAutoSpawn = tag->getParam("AutoSpawn", "false").toBool();
    } else if (tag->getName() == "Notify") {
        if (tag->getParam("NULL", "false").toBool()) {
            setNotify(NULL);
        } else if (tag->hasChildren()) {
            setNotify(plNotifyMsg::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
        }
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}

void plNPCSpawnMod::setNotify(plNotifyMsg* msg) {
    delete fNotify;
    fNotify = msg;
}
