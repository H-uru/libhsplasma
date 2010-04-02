#include "plNetMsgLoadClone.h"

plNetMsgLoadClone::plNetMsgLoadClone()
                 : fIsPlayer(false), fIsLoading(false), fIsInitialState(false) { }

void plNetMsgLoadClone::read(hsStream* S, plResManager* mgr) {
    plNetMsgGameMessage::read(S, mgr);

    fObject.read(S, mgr);
    fIsPlayer = S->readBool();
    fIsLoading = S->readBool();
    fIsInitialState = S->readBool();
}

void plNetMsgLoadClone::write(hsStream* S, plResManager* mgr) {
    plNetMsgGameMessage::write(S, mgr);

    fObject.write(S, mgr);
    S->writeBool(fIsPlayer);
    S->writeBool(fIsLoading);
    S->writeBool(fIsInitialState);
}

void plNetMsgLoadClone::IPrcWrite(pfPrcHelper* prc) {
    plNetMsgGameMessage::IPrcWrite(prc);

    prc->startTag("LoadCloneParams");
    prc->writeParam("IsPlayer", fIsPlayer);
    prc->writeParam("IsLoading", fIsLoading);
    prc->writeParam("IsInitialState", fIsInitialState);
    prc->endTag(true);

    prc->startTag("Object");
    fObject.prcWrite(prc);
    prc->closeTag();
}

void plNetMsgLoadClone::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "LoadCloneParams") {
        fIsPlayer = tag->getParam("IsPlayer", "false").toBool();
        fIsLoading = tag->getParam("IsLoading", "false").toBool();
        fIsInitialState = tag->getParam("IsInitialState", "false").toBool();
    } else if (tag->getName() == "Object") {
        if (tag->hasChildren())
            fObject.prcParse(tag->getFirstChild(), mgr);
    } else {
        plNetMsgGameMessage::IPrcParse(tag, mgr);
    }
}
