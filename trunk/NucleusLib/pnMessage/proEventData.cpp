#include "proEventData.h"
#include "../../PubUtilLib/plResMgr/plResManager.h"

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

proEventData* proEventData::read(hsStream* S) {
    proEventData* event = ICreateEventDataType(S->readInt());
    if (event != NULL)
        event->IRead(S);
    return event;
}

void proEventData::write(hsStream* S) {
    S->writeInt(fEventType);
    IWrite(S);
}


// proCollisionEventData //
proCollisionEventData::proCollisionEventData() : fEnter(false) {
    fEventType = kCollision;
}

void proCollisionEventData::IRead(hsStream* S) {
    fEnter = S->readBool();
    fHitter = plResManager::inst->readKey(S);
    fHittee = plResManager::inst->readKey(S);
}

void proCollisionEventData::IWrite(hsStream* S) {
    S->writeBool(fEnter);
    plResManager::inst->writeKey(S, fHitter);
    plResManager::inst->writeKey(S, fHittee);
}


// proPickedEventData //
proPickedEventData::proPickedEventData() : fEnabled(false) {
    fEventType = kPicked;
}

void proPickedEventData::IRead(hsStream* S) {
    fPicker = plResManager::inst->readKey(S);
    fPicked = plResManager::inst->readKey(S);
    fEnabled = S->readBool();
    fHitPoint.read(S);
}

void proPickedEventData::IWrite(hsStream* S) {
    plResManager::inst->writeKey(S, fPicker);
    plResManager::inst->writeKey(S, fPicked);
    S->writeBool(fEnabled);
    fHitPoint.write(S);
}


// proControlKeyEventData //
proControlKeyEventData::proControlKeyEventData() : fControlKey(0), fDown(false) {
    fEventType = kControlKey;
}

void proControlKeyEventData::IRead(hsStream* S) {
    fControlKey = S->readInt();
    fDown = S->readBool();
}

void proControlKeyEventData::IWrite(hsStream* S) {
    S->writeInt(fControlKey);
    S->writeInt(fDown);
}


// proVariableEventData //
proVariableEventData::proVariableEventData() : fNumber(0.0f) {
    fEventType = kVariable;
    fDataType = kNotta;
}

void proVariableEventData::IRead(hsStream* S) {
    fName = S->readSafeStr();
    fDataType = S->readInt();
    fNumber = S->readFloat();
    fKey = plResManager::inst->readKey(S);
}

void proVariableEventData::IWrite(hsStream* S) {
    S->writeSafeStr(fName);
    S->writeInt(fDataType);
    S->writeFloat(fNumber);
    plResManager::inst->writeKey(S, fKey);
}


// proFacingEventData //
proFacingEventData::proFacingEventData() : dot(0.0f), enabled(false) {
    fEventType = kFacing;
}

void proFacingEventData::IRead(hsStream* S) {
    fFacer = plResManager::inst->readKey(S);
    fFacee = plResManager::inst->readKey(S);
    dot = S->readFloat();
    enabled = S->readBool();
}

void proFacingEventData::IWrite(hsStream* S) {
    plResManager::inst->writeKey(S, fFacer);
    plResManager::inst->writeKey(S, fFacee);
    S->writeFloat(dot);
    S->writeFloat(enabled);
}


// proContainedEventData //
proContainedEventData::proContainedEventData() : fEntering(false) {
    fEventType = kContained;
}

void proContainedEventData::IRead(hsStream* S) {
    fContained = plResManager::inst->readKey(S);
    fContainer = plResManager::inst->readKey(S);
    fEntering = S->readBool();
}

void proContainedEventData::IWrite(hsStream* S) {
    plResManager::inst->writeKey(S, fContained);
    plResManager::inst->writeKey(S, fContainer);
    S->writeBool(fEntering);
}


// proActivateEventData //
proActivateEventData::proActivateEventData() : fActive(false), fActivate(false) {
    fEventType = kActivate;
}

void proActivateEventData::IRead(hsStream* S) {
    fActive = S->readBool();
    fActivate = S->readBool();
}

void proActivateEventData::IWrite(hsStream* S) {
    S->writeBool(fActive);
    S->writeBool(fActivate);
}


// proCallbackEventData //
proCallbackEventData::proCallbackEventData() : fCallbackEventType(0) {
    fEventType = kCallback;
}

void proCallbackEventData::IRead(hsStream* S) {
    fCallbackEventType = S->readInt();
}

void proCallbackEventData::IWrite(hsStream* S) {
    S->writeInt(fCallbackEventType);
}


// proResponderStateEventData //
proResponderStateEventData::proResponderStateEventData() : fState(0) {
    fEventType = kResponderState;
}

void proResponderStateEventData::IRead(hsStream* S) {
    fState = S->readInt();
}

void proResponderStateEventData::IWrite(hsStream* S) {
    S->writeInt(fState);
}


// proMultiStageEventData //
proMultiStageEventData::proMultiStageEventData() : fStage(0), fEvent(kNothing) {
    fEventType = kMultiStage;
}

void proMultiStageEventData::IRead(hsStream* S) {
    fStage = S->readInt();
    fEvent = S->readInt();
    fAvatar = plResManager::inst->readKey(S);
}

void proMultiStageEventData::IWrite(hsStream* S) {
    S->writeInt(fStage);
    S->writeInt(fEvent);
    plResManager::inst->writeKey(S, fAvatar);
}


// proSpawnedEventData //
proSpawnedEventData::proSpawnedEventData() {
    fEventType = kSpawned;
}

void proSpawnedEventData::IRead(hsStream* S) {
    fSpawner = plResManager::inst->readKey(S);
    fSpawnee = plResManager::inst->readKey(S);
}

void proSpawnedEventData::IWrite(hsStream* S) {
    plResManager::inst->writeKey(S, fSpawner);
    plResManager::inst->writeKey(S, fSpawnee);
}


// proClickDragEventData //
proClickDragEventData::proClickDragEventData() {
    fEventType = kClickDrag;
}


// proCoopEventData //
proCoopEventData::proCoopEventData() : fID(0), fSerial(0) {
    fEventType = kCoop;
}

void proCoopEventData::IRead(hsStream* S) {
    fID = S->readInt();
    fSerial = S->readShort();
}

void proCoopEventData::IWrite(hsStream* S) {
    S->writeInt(fID);
    S->writeShort(fSerial);
}


// proOfferLinkBookEventData //
proOfferLinkBookEventData::proOfferLinkBookEventData() : targetAge(0), offeree(0) {
    fEventType = kOfferLinkBook;
}

void proOfferLinkBookEventData::IRead(hsStream* S) {
    offerer = plResManager::inst->readKey(S);
    targetAge = S->readInt();
    offeree = S->readInt();
}

void proOfferLinkBookEventData::IWrite(hsStream* S) {
    plResManager::inst->writeKey(S, offerer);
    S->writeInt(targetAge);
    S->writeInt(offeree);
}


// proBookEventData //
proBookEventData::proBookEventData() : fEvent(0), fLinkID(0) {
    fEventType = kBook;
}

void proBookEventData::IRead(hsStream* S) {
    fEvent = S->readInt();
    fLinkID = S->readInt();
}

void proBookEventData::IWrite(hsStream* S) {
    S->writeInt(fEvent);
    S->writeInt(fLinkID);
}


// proClimbingBlockerHitEventData //
proClimbingBlockerHitEventData::proClimbingBlockerHitEventData() {
    fEventType = kClimbingBlockerHit;
}

void proClimbingBlockerHitEventData::IRead(hsStream* S) {
    fBlockerKey = plResManager::inst->readKey(S);
}

void proClimbingBlockerHitEventData::IWrite(hsStream* S) {
    plResManager::inst->writeKey(S, fBlockerKey);
}
