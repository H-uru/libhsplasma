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

#include "plAvTaskMsg.h"

/* plAvTaskMsg */
plAvTaskMsg::plAvTaskMsg() : fTask(NULL) { }

plAvTaskMsg::~plAvTaskMsg() {
    delete fTask;
}

void plAvTaskMsg::read(hsStream* S, plResManager* mgr) {
    plAvatarMsg::read(S, mgr);

    if (S->readBool())
        setTask(plAvTask::Convert(mgr->ReadCreatable(S)));
    else
        setTask(NULL);
}

void plAvTaskMsg::write(hsStream* S, plResManager* mgr) {
    plAvatarMsg::write(S, mgr);

    if (fTask != NULL) {
        S->writeBool(true);
        mgr->WriteCreatable(S, fTask);
    } else {
        S->writeBool(false);
    }
}

void plAvTaskMsg::IPrcWrite(pfPrcHelper* prc) {
    plAvatarMsg::IPrcWrite(prc);

    if (fTask != NULL) {
        prc->writeSimpleTag("Task");
        fTask->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("Task");
        prc->writeParam("NULL", true);
        prc->endTag();
    }
}

void plAvTaskMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Task") {
        if (tag->getParam("NULL", "false").toBool())
            setTask(NULL);
        else if (tag->hasChildren())
            setTask(plAvTask::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
    } else {
        plAvatarMsg::IPrcParse(tag, mgr);
    }
}

void plAvTaskMsg::setTask(plAvTask* task) {
    delete fTask;
    fTask = task;
}


/* plAvPushBrainMsg */
plAvPushBrainMsg::plAvPushBrainMsg() : fBrain(NULL) { }

plAvPushBrainMsg::~plAvPushBrainMsg() {
    delete fBrain;
}

void plAvPushBrainMsg::read(hsStream* S, plResManager* mgr) {
    plAvTaskMsg::read(S, mgr);
    setBrain(plArmatureBrain::Convert(mgr->ReadCreatable(S)));
}

void plAvPushBrainMsg::write(hsStream* S, plResManager* mgr) {
    plAvTaskMsg::write(S, mgr);
    mgr->WriteCreatable(S, fBrain);
}

void plAvPushBrainMsg::IPrcWrite(pfPrcHelper* prc) {
    plAvTaskMsg::IPrcWrite(prc);

    if (fBrain != NULL) {
        prc->writeSimpleTag("Brain");
        fBrain->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("Brain");
        prc->writeParam("NULL", true);
        prc->endTag();
    }
}

void plAvPushBrainMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Brain") {
        if (tag->getParam("NULL", "false").toBool())
            setBrain(NULL);
        else if (tag->hasChildren())
            setBrain(plArmatureBrain::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
    } else {
        plAvTaskMsg::IPrcParse(tag, mgr);
    }
}

void plAvPushBrainMsg::setBrain(plArmatureBrain* brain) {
    delete fBrain;
    fBrain = brain;
}
