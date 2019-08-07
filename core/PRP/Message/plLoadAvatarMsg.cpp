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

#include "plLoadAvatarMsg.h"

plLoadAvatarMsg::~plLoadAvatarMsg()
{
    delete fInitialTask;
}

void plLoadAvatarMsg::read(hsStream* S, plResManager* mgr)
{
    plLoadCloneMsg::read(S, mgr);

    fIsPlayer = S->readBool();
    fSpawnPoint = mgr->readKey(S);
    if (S->readBool()) {
        setInitialTask(mgr->ReadCreatableC<plAvTask>(S));
    } else {
        setInitialTask(nullptr);
    }

    if (S->getVer().isMoul() || S->getVer().isUniversal())
        fUserStr = S->readSafeStr();
}

void plLoadAvatarMsg::write(hsStream* S, plResManager* mgr)
{
    plLoadCloneMsg::write(S, mgr);

    S->writeBool(fIsPlayer);
    mgr->writeKey(S, fSpawnPoint);

    if (getInitialTask()) {
        S->writeBool(true);
        mgr->WriteCreatable(S, fInitialTask);
    } else {
        S->writeBool(false);
    }

    if (S->getVer().isMoul() || S->getVer().isUniversal())
        S->writeSafeStr(fUserStr);
}

void plLoadAvatarMsg::IPrcWrite(pfPrcHelper* prc)
{
    plLoadCloneMsg::IPrcWrite(prc);

    prc->startTag("AvatarParams");
    prc->writeParam("IsPlayer", fIsPlayer);
    prc->writeParam("UserStr", fUserStr);
    prc->endTag(true);

    prc->writeSimpleTag("SpawnPoint");
    plResManager::PrcWriteKey(prc, fSpawnPoint);
    prc->closeTag();

    if (getInitialTask()) {
        prc->writeSimpleTag("InitialTask");
        fInitialTask->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("InitialTask");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
}

void plLoadAvatarMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "AvatarParams") {
        fIsPlayer = tag->getParam("IsPlayer", "false").to_bool();
        fUserStr = tag->getParam("UserStr", "");
    } else if (tag->getName() == "InitialTask") {
        if (tag->hasChildren())
            setInitialTask(mgr->prcParseCreatableC<plAvTask>(tag->getFirstChild()));
        else
            setInitialTask(nullptr);
    } else if (tag->getName() == "SpawnPoint") {
        fSpawnPoint = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plLoadCloneMsg::IPrcParse(tag, mgr);
    }
}

void plLoadAvatarMsg::setInitialTask(plAvTask* task)
{
    delete fInitialTask;
    fInitialTask = task;
}
