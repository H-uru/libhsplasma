#include "plLoadAvatarMsg.h"

plLoadAvatarMsg::plLoadAvatarMsg() : fInitialTask(NULL) { }

plLoadAvatarMsg::~plLoadAvatarMsg() {
    if (fInitialTask != NULL)
        delete fInitialTask;
}

IMPLEMENT_CREATABLE(plLoadAvatarMsg, kLoadAvatarMsg, plLoadCloneMsg)

void plLoadAvatarMsg::read(hsStream* S, plResManager* mgr) {
    plLoadCloneMsg::read(S, mgr);

    fIsPlayer = S->readBool();
    fSpawnPoint = mgr->readKey(S);
    if (S->readBool()) {
        setInitialTask(plAvTask::Convert(mgr->ReadCreatable(S)));
    } else {
        setInitialTask(NULL);
    }

    if (S->getVer() == pvLive || S->getVer() == pvUniversal)
        fUserStr = S->readSafeStr();
}

void plLoadAvatarMsg::write(hsStream* S, plResManager* mgr) {
    plLoadCloneMsg::write(S, mgr);

    S->writeBool(fIsPlayer);
    mgr->writeKey(S, fSpawnPoint);

    if (getInitialTask() != NULL) {
        S->writeBool(true);
        mgr->WriteCreatable(S, fInitialTask);
    } else {
        S->writeBool(false);
    }

    if (S->getVer() == pvLive || S->getVer() == pvUniversal)
        S->writeSafeStr(fUserStr);
}

void plLoadAvatarMsg::IPrcWrite(pfPrcHelper* prc) {
    plLoadCloneMsg::IPrcWrite(prc);

    prc->startTag("AvatarParams");
    prc->writeParam("IsPlayer", fIsPlayer);
    prc->writeParam("UserStr", fUserStr);
    prc->endTag(true);

    prc->writeSimpleTag("SpawnPoint");
    fSpawnPoint->prcWrite(prc);
    prc->closeTag();

    if (getInitialTask() != NULL) {
        prc->writeSimpleTag("InitialTask");
        fInitialTask->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("InitialTask");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
}

void plLoadAvatarMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "AvatarParams") {
        fIsPlayer = tag->getParam("IsPlayer", "false").toBool();
        fUserStr = tag->getParam("UserStr", "");
    } else if (tag->getName() == "InitialTask") {
        if (tag->hasChildren())
            setInitialTask(plAvTask::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
        else
            setInitialTask(NULL);
    } else if (tag->getName() == "SpawnPoint") {
        fSpawnPoint = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plLoadCloneMsg::IPrcParse(tag, mgr);
    }
}

bool plLoadAvatarMsg::getIsPlayer() const {
    return fIsPlayer;
}

plKey plLoadAvatarMsg::getSpawnPoint() const {
    return fSpawnPoint;
}

plAvTask* plLoadAvatarMsg::getInitialTask() const {
    return fInitialTask;
}

plString plLoadAvatarMsg::getUserStr() const {
    return fUserStr;
}

void plLoadAvatarMsg::setIsPlayer(bool IsPlayer) {
    fIsPlayer = IsPlayer;
}

void plLoadAvatarMsg::setSpawnPoint(plKey SpawnPoint) {
    fSpawnPoint = SpawnPoint;
}

void plLoadAvatarMsg::setInitialTask(plAvTask* InitialTask) {
    if (fInitialTask != NULL)
        delete fInitialTask;
    fInitialTask = InitialTask;
}

void plLoadAvatarMsg::setUserStr(plString UserStr) {
    fUserStr = UserStr;
}
