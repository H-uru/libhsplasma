#include "proEventData.h"

// proEventData //
const char* const proEventData::fEventNames[] = {
    "proEventData", "proCollisionEventData", "proPickedEventData",
    "proControlKeyEventData", "proVariableEventData", "proFacingEventData",
    "proContainedEventData", "proActivateEventData", "proCallbackEventData",
    "proResponderStateEventData", "proMultiStageEventData",
    "proSpawnedEventData", "proClickDragEventData", "proCoopEventData",
    "proOfferLinkBookEventData", "proBookEventData",
    "proClimbingBlockerHitEventData"
};

proEventData::proEventData() : fEventType(0) { }
proEventData::~proEventData() { }

proEventData* proEventData::ICreateEventDataType(int type) {
    switch (type) {
    case kCollision:    return new proCollisionEventData();
    case kPicked:       return new proPickedEventData();
    case kControlKey:   return new proControlKeyEventData();
    case kVariable:     return new proVariableEventData();
    case kFacing:       return new proFacingEventData();
    case kContained:    return new proContainedEventData();
    case kActivate:     return new proActivateEventData();
    case kCallback:     return new proCallbackEventData();
    case kResponderState: return new proResponderStateEventData();
    case kMultiStage:   return new proMultiStageEventData();
    case kSpawned:      return new proSpawnedEventData();
    case kClickDrag:    return NULL;
    case kCoop:         return new proCoopEventData();
    case kOfferLinkBook: return new proOfferLinkBookEventData();
    case kBook:         return new proBookEventData();
    case kClimbingBlockerHit: return new proClimbingBlockerHitEventData();
    default:            return NULL;
    }
}

proEventData* proEventData::read(hsStream* S, plResManager* mgr) {
    proEventData* event = ICreateEventDataType(S->readInt());
    if (event != NULL)
        event->IRead(S, mgr);
    return event;
}

void proEventData::write(hsStream* S, plResManager* mgr) {
    S->writeInt(fEventType);
    IWrite(S, mgr);
}

void proEventData::prcWrite(pfPrcHelper* prc) {
    prc->writeSimpleTag(fEventNames[fEventType]);
    IPrcWrite(prc);
    prc->closeTag();
}


// proCollisionEventData //
proCollisionEventData::proCollisionEventData() : fEnter(false) {
    fEventType = kCollision;
}

void proCollisionEventData::IRead(hsStream* S, plResManager* mgr) {
    fEnter = S->readBool();
    fHitter = mgr->readKey(S);
    fHittee = mgr->readKey(S);
}

void proCollisionEventData::IWrite(hsStream* S, plResManager* mgr) {
    S->writeBool(fEnter);
    mgr->writeKey(S, fHitter);
    mgr->writeKey(S, fHittee);
}

void proCollisionEventData::IPrcWrite(pfPrcHelper* prc) {
    prc->startTag("Params");
    prc->writeParam("Enter", fEnter);
    prc->endTag(true);
    
    prc->writeSimpleTag("Hitter");
    fHitter->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Hittee");
    fHittee->prcWrite(prc);
    prc->closeTag();
}


// proPickedEventData //
proPickedEventData::proPickedEventData() : fEnabled(false) {
    fEventType = kPicked;
}

void proPickedEventData::IRead(hsStream* S, plResManager* mgr) {
    fPicker = mgr->readKey(S);
    fPicked = mgr->readKey(S);
    fEnabled = S->readBool();
    fHitPoint.read(S);
}

void proPickedEventData::IWrite(hsStream* S, plResManager* mgr) {
    mgr->writeKey(S, fPicker);
    mgr->writeKey(S, fPicked);
    S->writeBool(fEnabled);
    fHitPoint.write(S);
}

void proPickedEventData::IPrcWrite(pfPrcHelper* prc) {
    prc->startTag("Params");
    prc->writeParam("Eabled", fEnabled);
    prc->endTag(true);
    
    prc->writeSimpleTag("Picker");
    fPicker->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Picked");
    fPicked->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("HitPoint");
    fHitPoint.prcWrite(prc);
    prc->closeTag();
}


// proControlKeyEventData //
proControlKeyEventData::proControlKeyEventData() : fControlKey(0), fDown(false) {
    fEventType = kControlKey;
}

void proControlKeyEventData::IRead(hsStream* S, plResManager* mgr) {
    fControlKey = S->readInt();
    fDown = S->readBool();
}

void proControlKeyEventData::IWrite(hsStream* S, plResManager* mgr) {
    S->writeInt(fControlKey);
    S->writeInt(fDown);
}

void proControlKeyEventData::IPrcWrite(pfPrcHelper* prc) {
    prc->startTag("Params");
    prc->writeParam("ControlKey", fControlKey);
    prc->writeParam("Down", fDown);
    prc->endTag(true);
}


// proVariableEventData //
proVariableEventData::proVariableEventData() : fNumber(0.0f) {
    fEventType = kVariable;
    fDataType = kNotta;
}

void proVariableEventData::IRead(hsStream* S, plResManager* mgr) {
    fName = S->readSafeStr();
    fDataType = S->readInt();
    fNumber = S->readFloat();
    fKey = mgr->readKey(S);
}

void proVariableEventData::IWrite(hsStream* S, plResManager* mgr) {
    S->writeSafeStr(fName);
    S->writeInt(fDataType);
    S->writeFloat(fNumber);
    mgr->writeKey(S, fKey);
}

void proVariableEventData::IPrcWrite(pfPrcHelper* prc) {
    prc->startTag("Params");
    prc->writeParam("Name", fName);
    prc->writeParam("DataType", fDataType);
    prc->writeParam("Number", fNumber);
    prc->endTag(true);

    fKey->prcWrite(prc);
}


// proFacingEventData //
proFacingEventData::proFacingEventData() : dot(0.0f), enabled(false) {
    fEventType = kFacing;
}

void proFacingEventData::IRead(hsStream* S, plResManager* mgr) {
    fFacer = mgr->readKey(S);
    fFacee = mgr->readKey(S);
    dot = S->readFloat();
    enabled = S->readBool();
}

void proFacingEventData::IWrite(hsStream* S, plResManager* mgr) {
    mgr->writeKey(S, fFacer);
    mgr->writeKey(S, fFacee);
    S->writeFloat(dot);
    S->writeFloat(enabled);
}

void proFacingEventData::IPrcWrite(pfPrcHelper* prc) {
    prc->startTag("Params");
    prc->writeParam("Dot", dot);
    prc->writeParam("Enabled", enabled);
    prc->endTag(true);
    
    prc->writeSimpleTag("Facer");
    fFacer->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Facee");
    fFacee->prcWrite(prc);
    prc->closeTag();
}


// proContainedEventData //
proContainedEventData::proContainedEventData() : fEntering(false) {
    fEventType = kContained;
}

void proContainedEventData::IRead(hsStream* S, plResManager* mgr) {
    fContained = mgr->readKey(S);
    fContainer = mgr->readKey(S);
    fEntering = S->readBool();
}

void proContainedEventData::IWrite(hsStream* S, plResManager* mgr) {
    mgr->writeKey(S, fContained);
    mgr->writeKey(S, fContainer);
    S->writeBool(fEntering);
}

void proContainedEventData::IPrcWrite(pfPrcHelper* prc) {
    prc->startTag("Params");
    prc->writeParam("Entering", fEntering);
    prc->endTag(true);
    
    prc->writeSimpleTag("Contained");
    fContained->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Container");
    fContainer->prcWrite(prc);
    prc->closeTag();
}


// proActivateEventData //
proActivateEventData::proActivateEventData() : fActive(false), fActivate(false) {
    fEventType = kActivate;
}

void proActivateEventData::IRead(hsStream* S, plResManager* mgr) {
    fActive = S->readBool();
    fActivate = S->readBool();
}

void proActivateEventData::IWrite(hsStream* S, plResManager* mgr) {
    S->writeBool(fActive);
    S->writeBool(fActivate);
}

void proActivateEventData::IPrcWrite(pfPrcHelper* prc) {
    prc->startTag("Params");
    prc->writeParam("Active", fActive);
    prc->writeParam("Activate", fActivate);
    prc->endTag(true);
}


// proCallbackEventData //
proCallbackEventData::proCallbackEventData() : fCallbackEventType(0) {
    fEventType = kCallback;
}

void proCallbackEventData::IRead(hsStream* S, plResManager* mgr) {
    fCallbackEventType = S->readInt();
}

void proCallbackEventData::IWrite(hsStream* S, plResManager* mgr) {
    S->writeInt(fCallbackEventType);
}

void proCallbackEventData::IPrcWrite(pfPrcHelper* prc) {
    prc->startTag("Params");
    prc->writeParam("CallbackEventType", fCallbackEventType);
    prc->endTag(true);
}


// proResponderStateEventData //
proResponderStateEventData::proResponderStateEventData() : fState(0) {
    fEventType = kResponderState;
}

void proResponderStateEventData::IRead(hsStream* S, plResManager* mgr) {
    fState = S->readInt();
}

void proResponderStateEventData::IWrite(hsStream* S, plResManager* mgr) {
    S->writeInt(fState);
}

void proResponderStateEventData::IPrcWrite(pfPrcHelper* prc) {
    prc->startTag("Params");
    prc->writeParam("State", fState);
    prc->endTag(true);
}


// proMultiStageEventData //
proMultiStageEventData::proMultiStageEventData() : fStage(0), fEvent(kNothing) {
    fEventType = kMultiStage;
}

void proMultiStageEventData::IRead(hsStream* S, plResManager* mgr) {
    fStage = S->readInt();
    fEvent = S->readInt();
    fAvatar = mgr->readKey(S);
}

void proMultiStageEventData::IWrite(hsStream* S, plResManager* mgr) {
    S->writeInt(fStage);
    S->writeInt(fEvent);
    mgr->writeKey(S, fAvatar);
}

void proMultiStageEventData::IPrcWrite(pfPrcHelper* prc) {
    prc->startTag("Params");
    prc->writeParam("Stage", fStage);
    prc->writeParam("Event", fEvent);
    prc->endTag(true);
    
    prc->writeSimpleTag("Avatar");
    fAvatar->prcWrite(prc);
    prc->closeTag();
}


// proSpawnedEventData //
proSpawnedEventData::proSpawnedEventData() {
    fEventType = kSpawned;
}

void proSpawnedEventData::IRead(hsStream* S, plResManager* mgr) {
    fSpawner = mgr->readKey(S);
    fSpawnee = mgr->readKey(S);
}

void proSpawnedEventData::IWrite(hsStream* S, plResManager* mgr) {
    mgr->writeKey(S, fSpawner);
    mgr->writeKey(S, fSpawnee);
}

void proSpawnedEventData::IPrcWrite(pfPrcHelper* prc) {
    prc->writeSimpleTag("Spawner");
    fSpawner->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Spawnee");
    fSpawnee->prcWrite(prc);
    prc->closeTag();
}


// proClickDragEventData //
proClickDragEventData::proClickDragEventData() {
    fEventType = kClickDrag;
}


// proCoopEventData //
proCoopEventData::proCoopEventData() : fID(0), fSerial(0) {
    fEventType = kCoop;
}

void proCoopEventData::IRead(hsStream* S, plResManager* mgr) {
    fID = S->readInt();
    fSerial = S->readShort();
}

void proCoopEventData::IWrite(hsStream* S, plResManager* mgr) {
    S->writeInt(fID);
    S->writeShort(fSerial);
}

void proCoopEventData::IPrcWrite(pfPrcHelper* prc) {
    prc->startTag("Params");
    prc->writeParam("ID", fID);
    prc->writeParam("Serial", fSerial);
    prc->endTag(true);
}


// proOfferLinkBookEventData //
proOfferLinkBookEventData::proOfferLinkBookEventData() : targetAge(0), offeree(0) {
    fEventType = kOfferLinkBook;
}

void proOfferLinkBookEventData::IRead(hsStream* S, plResManager* mgr) {
    offerer = mgr->readKey(S);
    targetAge = S->readInt();
    offeree = S->readInt();
}

void proOfferLinkBookEventData::IWrite(hsStream* S, plResManager* mgr) {
    mgr->writeKey(S, offerer);
    S->writeInt(targetAge);
    S->writeInt(offeree);
}

void proOfferLinkBookEventData::IPrcWrite(pfPrcHelper* prc) {
    prc->startTag("Params");
    prc->writeParam("TargetAge", targetAge);
    prc->writeParam("Offeree", offeree);
    prc->endTag(true);
    
    prc->writeSimpleTag("Offerer");
    offerer->prcWrite(prc);
    prc->closeTag();
}


// proBookEventData //
proBookEventData::proBookEventData() : fEvent(0), fLinkID(0) {
    fEventType = kBook;
}

void proBookEventData::IRead(hsStream* S, plResManager* mgr) {
    fEvent = S->readInt();
    fLinkID = S->readInt();
}

void proBookEventData::IWrite(hsStream* S, plResManager* mgr) {
    S->writeInt(fEvent);
    S->writeInt(fLinkID);
}

void proBookEventData::IPrcWrite(pfPrcHelper* prc) {
    prc->startTag("Params");
    prc->writeParam("Event", fEvent);
    prc->writeParam("LinkID", fLinkID);
    prc->endTag(true);
}


// proClimbingBlockerHitEventData //
proClimbingBlockerHitEventData::proClimbingBlockerHitEventData() {
    fEventType = kClimbingBlockerHit;
}

void proClimbingBlockerHitEventData::IRead(hsStream* S, plResManager* mgr) {
    fBlockerKey = mgr->readKey(S);
}

void proClimbingBlockerHitEventData::IWrite(hsStream* S, plResManager* mgr) {
    mgr->writeKey(S, fBlockerKey);
}

void proClimbingBlockerHitEventData::IPrcWrite(pfPrcHelper* prc) {
    prc->writeSimpleTag("Blocker");
    fBlockerKey->prcWrite(prc);
    prc->closeTag();
}
