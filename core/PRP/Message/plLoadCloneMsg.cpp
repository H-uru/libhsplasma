#include "plLoadCloneMsg.h"

plLoadCloneMsg::plLoadCloneMsg()
              : fValidMsg(0), fIsLoading(0), fUserData(0),
                fOriginatingPlayerID(0), fTriggerMsg(NULL) {
    fBCastFlags |= kNetPropagate;
}

plLoadCloneMsg::~plLoadCloneMsg() {
    if (fTriggerMsg != NULL)
        delete fTriggerMsg;
}

IMPLEMENT_CREATABLE(plLoadCloneMsg, kLoadCloneMsg, plMessage)

void plLoadCloneMsg::read(hsStream* S, plResManager* mgr) {
    plMessage::read(S, mgr);

    fCloneKey = mgr->readKey(S);
    fRequestorKey = mgr->readKey(S);
    fOriginatingPlayerID = S->readInt();
    fUserData = S->readInt();
    fValidMsg = S->readByte();
    fIsLoading = S->readByte();
    setTriggerMsg(plMessage::Convert(mgr->ReadCreatable(S)));
}

void plLoadCloneMsg::write(hsStream* S, plResManager* mgr) {
    plMessage::write(S, mgr);

    mgr->writeKey(S, fCloneKey);
    mgr->writeKey(S, fRequestorKey);
    S->writeInt(fOriginatingPlayerID);
    S->writeInt(fUserData);
    S->writeByte(fValidMsg);
    S->writeByte(fIsLoading);
    mgr->WriteCreatable(S, fTriggerMsg);
}

void plLoadCloneMsg::IPrcWrite(pfPrcHelper* prc) {
    plMessage::IPrcWrite(prc);

    prc->writeSimpleTag("CloneKey");
    fCloneKey->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("RequestorKey");
    fRequestorKey->prcWrite(prc);
    prc->closeTag();

    prc->startTag("LoadCloneParams");
    prc->writeParam("OriginatingPlayerID", fOriginatingPlayerID);
    prc->writeParam("UserData", fUserData);
    prc->writeParam("Valid", fValidMsg);
    prc->writeParam("Loading", fIsLoading);
    prc->endTag(true);

    if (fTriggerMsg != NULL) {
        prc->writeSimpleTag("TriggerMsg");
        fTriggerMsg->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("TriggerMsg");
        prc->writeParam("NULL", "true");
        prc->endTag(true);
    }
}

void plLoadCloneMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "CloneKey") {
        if (tag->hasChildren())
            fCloneKey = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "RequestorKey") {
        if (tag->hasChildren())
            fRequestorKey = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "LoadCloneParams") {
        fOriginatingPlayerID = tag->getParam("OriginatingPlayerID", "0").toInt();
        fUserData = tag->getParam("UserData", "0").toInt();
        fValidMsg = tag->getParam("Valid", "0").toBool();
        fIsLoading = tag->getParam("Loading", "0").toBool();
    } else if (tag->getName() == "TriggerMsg") {
        if (tag->getParam("NULL", "false").toBool())
            setTriggerMsg(NULL);
        else if (tag->hasChildren())
            setTriggerMsg(plMessage::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}

plKey plLoadCloneMsg::getCloneKey() const {
    return fCloneKey;
}

plKey plLoadCloneMsg::getRequestorKey() const {
    return fRequestorKey;
}

unsigned char plLoadCloneMsg::getValidMsg() const {
    return fValidMsg;
}

unsigned char plLoadCloneMsg::getIsLoading() const {
    return fIsLoading;
}

unsigned int plLoadCloneMsg::getUserData() const {
    return fUserData;
}

unsigned int plLoadCloneMsg::getOriginatingPlayerID() const {
    return fOriginatingPlayerID;
}

plMessage* plLoadCloneMsg::getTriggerMsg() const {
    return fTriggerMsg;
}

void plLoadCloneMsg::setCloneKey(plKey CloneKey) {
    fCloneKey = CloneKey;
}

void plLoadCloneMsg::setRequestorKey(plKey RequestorKey) {
    fRequestorKey = RequestorKey;
}

void plLoadCloneMsg::setValidMsg(unsigned char ValidMsg) {
    fValidMsg = ValidMsg;
}

void plLoadCloneMsg::setIsLoading(unsigned char IsLoading) {
    fIsLoading = IsLoading;
}

void plLoadCloneMsg::setUserData(unsigned int UserData) {
    fUserData = UserData;
}

void plLoadCloneMsg::setOriginatingPlayerID(unsigned int OriginatingPlayerID) {
    fOriginatingPlayerID = OriginatingPlayerID;
}

void plLoadCloneMsg::setTriggerMsg(plMessage* TriggerMsg) {
    if (fTriggerMsg != NULL)
        delete fTriggerMsg;
    fTriggerMsg = TriggerMsg;
}
