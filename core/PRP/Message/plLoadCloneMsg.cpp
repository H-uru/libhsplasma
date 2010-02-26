#include "plLoadCloneMsg.h"

plLoadCloneMsg::plLoadCloneMsg() {
    fBCastFlags |= kNetPropagate;
}

plLoadCloneMsg::~plLoadCloneMsg() { }

IMPLEMENT_CREATABLE(plLoadCloneMsg, kLoadCloneMsg, plMessage)

void plLoadCloneMsg::read(hsStream* S, plResManager* mgr) {
    plMessage::read(S, mgr);
    
    fCloneKey = mgr->readKey(S);
    fRequestorKey = mgr->readKey(S);
    fOriginatingPlayerID = S->readIntSwap();
    fUserData = S->readIntSwap();
    fValidMsg = S->readByte();
    fIsLoading = S->readByte();
    fTriggerMsg = plMessage::Convert(mgr->ReadCreatable(S));
}

void plLoadCloneMsg::write(hsStream* S, plResManager* mgr) {
    plMessage::write(S, mgr);
    
    mgr->writeKey(S, fCloneKey);
    mgr->writeKey(S, fRequestorKey);
    S->writeIntSwap(fOriginatingPlayerID);
    S->writeIntSwap(fUserData);
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
        if (fTriggerMsg != NULL)
            delete fTriggerMsg;
        if (tag->getParam("NULL", "false").toBool())
            fTriggerMsg = NULL;
        else
            fTriggerMsg = plMessage::Convert(mgr->prcParseCreatable(tag));
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}
