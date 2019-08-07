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

#include "proEventData.h"
#include <cstring>

/* proEventData */
const char* const proEventData::fEventNames[] = {
    "proEventData", "proCollisionEventData", "proPickedEventData",
    "proControlKeyEventData", "proVariableEventData", "proFacingEventData",
    "proContainedEventData", "proActivateEventData", "proCallbackEventData",
    "proResponderStateEventData", "proMultiStageEventData",
    "proSpawnedEventData", "proClickDragEventData", "proCoopEventData",
    "proOfferLinkBookEventData", "proBookEventData",
    "proClimbingBlockerHitEventData"
};

proEventData* proEventData::ICreateEventDataType(int type)
{
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
    case kClickDrag:    return new proClickDragEventData();
    case kCoop:         return new proCoopEventData();
    case kOfferLinkBook: return new proOfferLinkBookEventData();
    case kBook:         return new proBookEventData();
    case kClimbingBlockerHit: return new proClimbingBlockerHitEventData();
    default:            return nullptr;
    }
}

proEventData* proEventData::ICreateEventDataType(const char* typeName)
{
    int type = -1;
    for (int i=0; i<kNone; i++) {
        if (strcmp(typeName, fEventNames[i]) == 0)
           type = i;
    }
    if (type < 0)
        throw pfPrcTagException(__FILE__, __LINE__, typeName);
    return ICreateEventDataType(type);
}

proEventData* proEventData::Read(hsStream* S, plResManager* mgr)
{
    proEventData* event = ICreateEventDataType(S->readInt());
    if (event)
        event->IRead(S, mgr);
    return event;
}

void proEventData::write(hsStream* S, plResManager* mgr)
{
    S->writeInt(fEventType);
    IWrite(S, mgr);
}

void proEventData::prcWrite(pfPrcHelper* prc)
{
    prc->writeSimpleTag(fEventNames[fEventType]);
    IPrcWrite(prc);
    prc->closeTag();
}

proEventData* proEventData::PrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    proEventData* event = ICreateEventDataType(tag->getName().c_str());
    if (event) {
        const pfPrcTag* child = tag->getFirstChild();
        while (child) {
            event->IPrcParse(child, mgr);
            child = child->getNextSibling();
        }
    }
    return event;
}

void proEventData::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
}


/* proCollisionEventData */
void proCollisionEventData::IRead(hsStream* S, plResManager* mgr)
{
    fEnter = S->readBool();
    fHitter = mgr->readKey(S);
    fHittee = mgr->readKey(S);
}

void proCollisionEventData::IWrite(hsStream* S, plResManager* mgr)
{
    S->writeBool(fEnter);
    mgr->writeKey(S, fHitter);
    mgr->writeKey(S, fHittee);
}

void proCollisionEventData::IPrcWrite(pfPrcHelper* prc)
{
    prc->startTag("CollisionParams");
    prc->writeParam("Enter", fEnter);
    prc->endTag(true);

    prc->writeSimpleTag("Hitter");
    plResManager::PrcWriteKey(prc, fHitter);
    prc->closeTag();
    prc->writeSimpleTag("Hittee");
    plResManager::PrcWriteKey(prc, fHittee);
    prc->closeTag();
}

void proCollisionEventData::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "CollisionParams") {
        fEnter = tag->getParam("Enter", "false").to_bool();
    } else if (tag->getName() == "Hitter") {
        if (tag->hasChildren())
            fHitter = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Hittee") {
        if (tag->hasChildren())
            fHittee = mgr->prcParseKey(tag->getFirstChild());
    } else {
        proEventData::IPrcParse(tag, mgr);
    }
}


/* proPickedEventData */
void proPickedEventData::IRead(hsStream* S, plResManager* mgr)
{
    fPicker = mgr->readKey(S);
    fPicked = mgr->readKey(S);
    fEnabled = S->readBool();
    fHitPoint.read(S);
}

void proPickedEventData::IWrite(hsStream* S, plResManager* mgr)
{
    mgr->writeKey(S, fPicker);
    mgr->writeKey(S, fPicked);
    S->writeBool(fEnabled);
    fHitPoint.write(S);
}

void proPickedEventData::IPrcWrite(pfPrcHelper* prc)
{
    prc->startTag("PickedParams");
    prc->writeParam("Eabled", fEnabled);
    prc->endTag(true);

    prc->writeSimpleTag("Picker");
    plResManager::PrcWriteKey(prc, fPicker);
    prc->closeTag();
    prc->writeSimpleTag("Picked");
    plResManager::PrcWriteKey(prc, fPicked);
    prc->closeTag();
    prc->writeSimpleTag("HitPoint");
    fHitPoint.prcWrite(prc);
    prc->closeTag();
}

void proPickedEventData::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "PickedParams") {
        fEnabled = tag->getParam("Enabled", "false").to_bool();
    } else if (tag->getName() == "Picker") {
        if (tag->hasChildren())
            fPicker = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Picked") {
        if (tag->hasChildren())
            fPicked = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "HitPoint") {
        if (tag->hasChildren())
            fHitPoint.prcParse(tag);
    } else {
        proEventData::IPrcParse(tag, mgr);
    }
}


/* proControlKeyEventData */
void proControlKeyEventData::IRead(hsStream* S, plResManager* mgr)
{
    fControlKey = S->readInt();
    fDown = S->readBool();
}

void proControlKeyEventData::IWrite(hsStream* S, plResManager* mgr)
{
    S->writeInt(fControlKey);
    S->writeBool(fDown);
}

void proControlKeyEventData::IPrcWrite(pfPrcHelper* prc)
{
    prc->startTag("ControlKeyParams");
    prc->writeParam("ControlKey", fControlKey);
    prc->writeParam("Down", fDown);
    prc->endTag(true);
}

void proControlKeyEventData::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "ControlKeyParams") {
        fControlKey = tag->getParam("ControlKey", "0").to_int();
        fDown = tag->getParam("Down", "false").to_bool();
    } else {
        proEventData::IPrcParse(tag, mgr);
    }
}


/* proVariableEventData */
void proVariableEventData::IRead(hsStream* S, plResManager* mgr)
{
    fName = S->readSafeStr();
    fDataType = S->readInt();
    fNumber = S->readFloat();
    fKey = mgr->readKey(S);
}

void proVariableEventData::IWrite(hsStream* S, plResManager* mgr)
{
    S->writeSafeStr(fName);
    S->writeInt(fDataType);
    S->writeFloat(fNumber);
    mgr->writeKey(S, fKey);
}

void proVariableEventData::IPrcWrite(pfPrcHelper* prc)
{
    prc->startTag("VariableParams");
    prc->writeParam("Name", fName);
    prc->writeParam("DataType", fDataType);
    prc->writeParam("Number", fNumber);
    prc->endTag();
    plResManager::PrcWriteKey(prc, fKey);
    prc->closeTag();
}

void proVariableEventData::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "VariableParams") {
        fName = tag->getParam("Name", "");
        fDataType = tag->getParam("DataType", "0").to_int();
        fNumber = tag->getParam("Number", "0").to_float();
        if (tag->hasChildren())
            fKey = mgr->prcParseKey(tag->getFirstChild());
    } else {
        proEventData::IPrcParse(tag, mgr);
    }
}


/* proFacingEventData */
void proFacingEventData::IRead(hsStream* S, plResManager* mgr)
{
    fFacer = mgr->readKey(S);
    fFacee = mgr->readKey(S);
    fDot = S->readFloat();
    fEnabled = S->readBool();
}

void proFacingEventData::IWrite(hsStream* S, plResManager* mgr)
{
    mgr->writeKey(S, fFacer);
    mgr->writeKey(S, fFacee);
    S->writeFloat(fDot);
    S->writeBool(fEnabled);
}

void proFacingEventData::IPrcWrite(pfPrcHelper* prc)
{
    prc->startTag("FacingParams");
    prc->writeParam("Dot", fDot);
    prc->writeParam("Enabled", fEnabled);
    prc->endTag(true);

    prc->writeSimpleTag("Facer");
    plResManager::PrcWriteKey(prc, fFacer);
    prc->closeTag();
    prc->writeSimpleTag("Facee");
    plResManager::PrcWriteKey(prc, fFacee);
    prc->closeTag();
}

void proFacingEventData::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "FacingParams") {
        fDot = tag->getParam("Dot", "0").to_float();
        fEnabled = tag->getParam("Enabled", "false").to_bool();
    } else if (tag->getName() == "Facer") {
        if (tag->hasChildren())
            fFacer = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Facee") {
        if (tag->hasChildren())
            fFacee = mgr->prcParseKey(tag->getFirstChild());
    } else {
        proEventData::IPrcParse(tag, mgr);
    }
}


/* proContainedEventData */
void proContainedEventData::IRead(hsStream* S, plResManager* mgr)
{
    fContained = mgr->readKey(S);
    fContainer = mgr->readKey(S);
    fEntering = S->readBool();
}

void proContainedEventData::IWrite(hsStream* S, plResManager* mgr)
{
    mgr->writeKey(S, fContained);
    mgr->writeKey(S, fContainer);
    S->writeBool(fEntering);
}

void proContainedEventData::IPrcWrite(pfPrcHelper* prc)
{
    prc->startTag("ContainedParams");
    prc->writeParam("Entering", fEntering);
    prc->endTag(true);

    prc->writeSimpleTag("Contained");
    plResManager::PrcWriteKey(prc, fContained);
    prc->closeTag();
    prc->writeSimpleTag("Container");
    plResManager::PrcWriteKey(prc, fContainer);
    prc->closeTag();
}

void proContainedEventData::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "ContainedParams") {
        fEntering = tag->getParam("Entering", "false").to_bool();
    } else if (tag->getName() == "Contained") {
        if (tag->hasChildren())
            fContained = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Container") {
        if (tag->hasChildren())
            fContainer = mgr->prcParseKey(tag->getFirstChild());
    } else {
        proEventData::IPrcParse(tag, mgr);
    }
}


/* proActivateEventData */
void proActivateEventData::IRead(hsStream* S, plResManager* mgr)
{
    fActive = S->readBool();
    fActivate = S->readBool();
}

void proActivateEventData::IWrite(hsStream* S, plResManager* mgr)
{
    S->writeBool(fActive);
    S->writeBool(fActivate);
}

void proActivateEventData::IPrcWrite(pfPrcHelper* prc)
{
    prc->startTag("ActivateParams");
    prc->writeParam("Active", fActive);
    prc->writeParam("Activate", fActivate);
    prc->endTag(true);
}

void proActivateEventData::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "ActivateParams") {
        fActive = tag->getParam("Active", "false").to_bool();
        fActivate = tag->getParam("Activate", "false").to_bool();
    } else {
        proEventData::IPrcParse(tag, mgr);
    }
}


/* proCallbackEventData */
void proCallbackEventData::IRead(hsStream* S, plResManager* mgr)
{
    fCallbackEventType = S->readInt();
}

void proCallbackEventData::IWrite(hsStream* S, plResManager* mgr)
{
    S->writeInt(fCallbackEventType);
}

void proCallbackEventData::IPrcWrite(pfPrcHelper* prc)
{
    prc->startTag("CallbackParams");
    prc->writeParam("CallbackEventType", fCallbackEventType);
    prc->endTag(true);
}

void proCallbackEventData::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "CallbackParams") {
        fCallbackEventType = tag->getParam("CallbackEventType", "0").to_int();
    } else {
        proEventData::IPrcParse(tag, mgr);
    }
}


/* proResponderStateEventData */
void proResponderStateEventData::IRead(hsStream* S, plResManager* mgr)
{
    fState = S->readInt();
}

void proResponderStateEventData::IWrite(hsStream* S, plResManager* mgr)
{
    S->writeInt(fState);
}

void proResponderStateEventData::IPrcWrite(pfPrcHelper* prc)
{
    prc->startTag("ResponderStateParams");
    prc->writeParam("State", fState);
    prc->endTag(true);
}

void proResponderStateEventData::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "ResponderStateParams") {
        fState = tag->getParam("State", "0").to_int();
    } else {
        proEventData::IPrcParse(tag, mgr);
    }
}


/* proMultiStageEventData */
void proMultiStageEventData::IRead(hsStream* S, plResManager* mgr)
{
    fStage = S->readInt();
    fEvent = S->readInt();
    fAvatar = mgr->readKey(S);
}

void proMultiStageEventData::IWrite(hsStream* S, plResManager* mgr)
{
    S->writeInt(fStage);
    S->writeInt(fEvent);
    mgr->writeKey(S, fAvatar);
}

void proMultiStageEventData::IPrcWrite(pfPrcHelper* prc)
{
    prc->startTag("MultiStageParams");
    prc->writeParam("Stage", fStage);
    prc->writeParam("Event", fEvent);
    prc->endTag(true);

    prc->writeSimpleTag("Avatar");
    plResManager::PrcWriteKey(prc, fAvatar);
    prc->closeTag();
}

void proMultiStageEventData::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "MultiStageParams") {
        fStage = tag->getParam("Stage", "0").to_int();
        fEvent = tag->getParam("Event", "0").to_int();
    } else if (tag->getName() == "Avatar") {
        if (tag->hasChildren())
            fAvatar = mgr->prcParseKey(tag->getFirstChild());
    } else {
        proEventData::IPrcParse(tag, mgr);
    }
}


/* proSpawnedEventData */
void proSpawnedEventData::IRead(hsStream* S, plResManager* mgr)
{
    fSpawner = mgr->readKey(S);
    fSpawnee = mgr->readKey(S);
}

void proSpawnedEventData::IWrite(hsStream* S, plResManager* mgr)
{
    mgr->writeKey(S, fSpawner);
    mgr->writeKey(S, fSpawnee);
}

void proSpawnedEventData::IPrcWrite(pfPrcHelper* prc)
{
    prc->writeSimpleTag("Spawner");
    plResManager::PrcWriteKey(prc, fSpawner);
    prc->closeTag();
    prc->writeSimpleTag("Spawnee");
    plResManager::PrcWriteKey(prc, fSpawnee);
    prc->closeTag();
}

void proSpawnedEventData::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Spawner") {
        if (tag->hasChildren())
            fSpawner = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Spawnee") {
        if (tag->hasChildren())
            fSpawnee = mgr->prcParseKey(tag->getFirstChild());
    } else {
        proEventData::IPrcParse(tag, mgr);
    }
}


/* proCoopEventData */
void proCoopEventData::IRead(hsStream* S, plResManager* mgr)
{
    fID = S->readInt();
    fSerial = S->readShort();
}

void proCoopEventData::IWrite(hsStream* S, plResManager* mgr)
{
    S->writeInt(fID);
    S->writeShort(fSerial);
}

void proCoopEventData::IPrcWrite(pfPrcHelper* prc)
{
    prc->startTag("CoopParams");
    prc->writeParam("ID", fID);
    prc->writeParam("Serial", fSerial);
    prc->endTag(true);
}

void proCoopEventData::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "CoopParams") {
        fID = tag->getParam("ID", "0").to_uint();
        fSerial = tag->getParam("Serial", "0").to_uint();
    } else {
        proEventData::IPrcParse(tag, mgr);
    }
}


/* proOfferLinkBookEventData */
void proOfferLinkBookEventData::IRead(hsStream* S, plResManager* mgr)
{
    fOfferer = mgr->readKey(S);
    fTargetAge = S->readInt();
    fOfferee = S->readInt();
}

void proOfferLinkBookEventData::IWrite(hsStream* S, plResManager* mgr)
{
    mgr->writeKey(S, fOfferer);
    S->writeInt(fTargetAge);
    S->writeInt(fOfferee);
}

void proOfferLinkBookEventData::IPrcWrite(pfPrcHelper* prc)
{
    prc->startTag("OfferParams");
    prc->writeParam("TargetAge", fTargetAge);
    prc->writeParam("Offeree", fOfferee);
    prc->endTag(true);

    prc->writeSimpleTag("Offerer");
    plResManager::PrcWriteKey(prc, fOfferer);
    prc->closeTag();
}

void proOfferLinkBookEventData::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "OfferParams") {
        fTargetAge = tag->getParam("TargetAge", "0").to_int();
        fOfferee = tag->getParam("Offeree", "0").to_int();
    } else if (tag->getName() == "Offerer") {
        if (tag->hasChildren())
            fOfferer = mgr->prcParseKey(tag->getFirstChild());
    } else {
        proEventData::IPrcParse(tag, mgr);
    }
}


/* proBookEventData */
void proBookEventData::IRead(hsStream* S, plResManager* mgr)
{
    fEvent = S->readInt();
    fLinkID = S->readInt();
}

void proBookEventData::IWrite(hsStream* S, plResManager* mgr)
{
    S->writeInt(fEvent);
    S->writeInt(fLinkID);
}

void proBookEventData::IPrcWrite(pfPrcHelper* prc)
{
    prc->startTag("BookParams");
    prc->writeParam("Event", fEvent);
    prc->writeParam("LinkID", fLinkID);
    prc->endTag(true);
}

void proBookEventData::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "BookParams") {
        fEvent = tag->getParam("Event", "0").to_uint();
        fLinkID = tag->getParam("LinkID", "0").to_uint();
    } else {
        proEventData::IPrcParse(tag, mgr);
    }
}


/* proClimbingBlockerHitEventData */
void proClimbingBlockerHitEventData::IRead(hsStream* S, plResManager* mgr)
{
    fBlockerKey = mgr->readKey(S);
}

void proClimbingBlockerHitEventData::IWrite(hsStream* S, plResManager* mgr)
{
    mgr->writeKey(S, fBlockerKey);
}

void proClimbingBlockerHitEventData::IPrcWrite(pfPrcHelper* prc)
{
    prc->writeSimpleTag("Blocker");
    plResManager::PrcWriteKey(prc, fBlockerKey);
    prc->closeTag();
}

void proClimbingBlockerHitEventData::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Blocker") {
        if (tag->hasChildren())
            fBlockerKey = mgr->prcParseKey(tag->getFirstChild());
    } else {
        proEventData::IPrcParse(tag, mgr);
    }
}
