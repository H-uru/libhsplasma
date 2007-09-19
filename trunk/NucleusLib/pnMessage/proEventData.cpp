#include "proEventData.h"

// proEventData //
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
