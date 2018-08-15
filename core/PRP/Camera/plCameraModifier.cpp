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

#include "plCameraModifier.h"

/* plCameraModifier::CamTrans */
void plCameraModifier::CamTrans::read(hsStream* S, plResManager* mgr) {
    fTransTo = mgr->readKey(S);
    fCutPos = S->readBool();
    fCutPOA = S->readBool();
    fIgnore = S->readBool();
    fVelocity = S->readFloat();
    fAccel = S->readFloat();
    fDecel = S->readFloat();
    fPOAVelocity = S->readFloat();
    fPOAAccel = S->readFloat();
    fPOADecel = S->readFloat();
}

void plCameraModifier::CamTrans::write(hsStream* S, plResManager* mgr) {
    mgr->writeKey(S, fTransTo);
    S->writeBool(fCutPos);
    S->writeBool(fCutPOA);
    S->writeBool(fIgnore);
    S->writeFloat(fVelocity);
    S->writeFloat(fAccel);
    S->writeFloat(fDecel);
    S->writeFloat(fPOAVelocity);
    S->writeFloat(fPOAAccel);
    S->writeFloat(fPOADecel);
}

void plCameraModifier::CamTrans::prcWrite(pfPrcHelper* prc) {
    prc->startTag("CamTrans");
    prc->writeParam("CutPos", fCutPos);
    prc->writeParam("CutPOA", fCutPOA);
    prc->writeParam("Ignore", fIgnore);
    prc->writeParam("Velocity", fVelocity);
    prc->writeParam("Accel", fAccel);
    prc->writeParam("Decel", fDecel);
    prc->writeParam("POAVelocity", fPOAVelocity);
    prc->writeParam("POAAccel", fPOAAccel);
    prc->writeParam("POADecel", fPOADecel);
    prc->endTag();
      prc->writeSimpleTag("TransTo");
      plResManager::PrcWriteKey(prc, fTransTo);
      prc->closeTag();
    prc->closeTag();
}

void plCameraModifier::CamTrans::prcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() != "CamTrans")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fCutPos = tag->getParam("CutPos", "false").to_bool();
    fCutPOA = tag->getParam("CutPOA", "false").to_bool();
    fIgnore = tag->getParam("Ignore", "false").to_bool();
    fVelocity = tag->getParam("Velocity", "0").to_float();
    fAccel = tag->getParam("Accel", "0").to_float();
    fDecel = tag->getParam("Decel", "0").to_float();
    fPOAVelocity = tag->getParam("POAVelocity", "0").to_float();
    fPOAAccel = tag->getParam("POAAccel", "0").to_float();
    fPOADecel = tag->getParam("POADecel", "0").to_float();

    const pfPrcTag* child = tag->getFirstChild();
    if (child != NULL) {
        if (child->getName() == "TransTo") {
            if (child->hasChildren())
                fTransTo = mgr->prcParseKey(child->getFirstChild());
        } else {
            throw pfPrcTagException(__FILE__, __LINE__, child->getName());
        }
    }
}


/* plCameraModifier */
plCameraModifier::~plCameraModifier() {
    for (auto trans = fTrans.begin(); trans != fTrans.end(); ++trans)
        delete *trans;
    for (auto msg = fMessageQueue.begin(); msg != fMessageQueue.end(); ++msg)
        delete *msg;
    for (auto inst = fFOVInstructions.begin(); inst != fFOVInstructions.end(); ++inst)
        delete *inst;
}

void plCameraModifier::read(hsStream* S, plResManager* mgr) {
    hsKeyedObject::read(S, mgr);

    clearTrans();
    fBrain = mgr->readKey(S);
    fTrans.resize(S->readInt());
    for (size_t i=0; i<fTrans.size(); i++) {
        fTrans[i] = new CamTrans();
        fTrans[i]->read(S, mgr);
    }
    fFOVw = S->readFloat();
    fFOVh = S->readFloat();

    clearMessageQueue();
    fMessageQueue.resize(S->readInt());
    fSenderQueue.resize(fMessageQueue.size());
    for (size_t i=0; i<fMessageQueue.size(); i++)
        fMessageQueue[i] = plMessage::Convert(mgr->ReadCreatable(S));
    for (size_t i=0; i<fSenderQueue.size(); i++)
        fSenderQueue[i] = mgr->readKey(S);

    clearFOVInstructions();
    fFOVInstructions.resize(S->readInt());
    for (size_t i=0; i<fFOVInstructions.size(); i++)
        fFOVInstructions[i] = plCameraMsg::Convert(mgr->ReadCreatable(S));

    fAnimated = S->readBool();
    fStartAnimOnPush = S->readBool();
    fStopAnimOnPop = S->readBool();
    fResetAnimOnPop = S->readBool();
}

void plCameraModifier::write(hsStream* S, plResManager* mgr) {
    hsKeyedObject::write(S, mgr);

    mgr->writeKey(S, fBrain);
    S->writeInt(fTrans.size());
    for (size_t i=0; i<fTrans.size(); i++)
        fTrans[i]->write(S, mgr);
    S->writeFloat(fFOVw);
    S->writeFloat(fFOVh);

    S->writeInt(fMessageQueue.size());
    for (size_t i=0; i<fMessageQueue.size(); i++)
        mgr->WriteCreatable(S, fMessageQueue[i]);
    for (size_t i=0; i<fSenderQueue.size(); i++)
        mgr->writeKey(S, fSenderQueue[i]);

    S->writeInt(fFOVInstructions.size());
    for (size_t i=0; i<fFOVInstructions.size(); i++)
        mgr->WriteCreatable(S, fFOVInstructions[i]);

    S->writeBool(fAnimated);
    S->writeBool(fStartAnimOnPush);
    S->writeBool(fStopAnimOnPop);
    S->writeBool(fResetAnimOnPop);
}

bool plCameraModifier::orderAfter(const hsKeyedObject* other) const {
    // No strong association between plCameraModifier and plAGMasterMod,
    // so just ensure this is always sorted after all plAGMasterMods
    // TODO: Improve this if possible
    if (other->getKey()->getType() == kAGMasterMod)
        return true;
    return plSingleModifier::orderAfter(other);
}

void plCameraModifier::IPrcWrite(pfPrcHelper* prc) {
    hsKeyedObject::IPrcWrite(prc);

    prc->startTag("CameraModParams");
    prc->writeParam("FOVw", fFOVw);
    prc->writeParam("FOVh", fFOVh);
    prc->writeParam("Animated", fAnimated);
    prc->writeParam("StartAnimOnPush", fStartAnimOnPush);
    prc->writeParam("StopAnimOnPop", fStopAnimOnPop);
    prc->writeParam("ResetAnimOnPop", fResetAnimOnPop);
    prc->endTag(true);

    prc->writeSimpleTag("Brain");
    plResManager::PrcWriteKey(prc, fBrain);
    prc->closeTag();

    prc->writeSimpleTag("Transforms");
    for (size_t i=0; i<fTrans.size(); i++)
        fTrans[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("MessageQueue");
    for (size_t i=0; i<fMessageQueue.size(); i++) {
        prc->writeSimpleTag("Message");
        fMessageQueue[i]->prcWrite(prc);
        prc->closeTag();
        prc->writeSimpleTag("Sender");
        plResManager::PrcWriteKey(prc, fSenderQueue[i]);
        prc->closeTag();
    }
    prc->closeTag();

    prc->writeSimpleTag("FOVInstructions");
    for (size_t i=0; i<fFOVInstructions.size(); i++)
        fFOVInstructions[i]->prcWrite(prc);
    prc->closeTag();
}

void plCameraModifier::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "CameraModParams") {
        fFOVw = tag->getParam("FOVw", "45").to_float();
        fFOVh = tag->getParam("FOVh", "33.75").to_float();
        fAnimated = tag->getParam("Animated", "false").to_bool();
        fStartAnimOnPush = tag->getParam("StartAnimOnPush", "false").to_bool();
        fStopAnimOnPop = tag->getParam("StopAnimOnPop", "false").to_bool();
        fResetAnimOnPop = tag->getParam("ResetAnimOnPop", "false").to_bool();
    } else if (tag->getName() == "Brain") {
        if (tag->hasChildren())
            fBrain = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Transforms") {
        clearTrans();
        fTrans.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fTrans.size(); i++) {
            fTrans[i] = new CamTrans();
            fTrans[i]->prcParse(child, mgr);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "MessageQueue") {
        clearMessageQueue();
        fMessageQueue.resize(tag->countChildren() / 2);
        fSenderQueue.resize(fMessageQueue.size());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fMessageQueue.size(); i++) {
            if (child->getName() != "Message")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            fMessageQueue[i] = plMessage::Convert(mgr->prcParseCreatable(child->getFirstChild()));
            child = child->getNextSibling();
            if (child->getName() != "Sender")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            fSenderQueue[i] = mgr->prcParseKey(child->getFirstChild());
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "FOVInstructions") {
        clearFOVInstructions();
        fFOVInstructions.resize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fFOVInstructions.size(); i++) {
            fFOVInstructions[i] = plCameraMsg::Convert(mgr->prcParseCreatable(child));
            child = child->getNextSibling();
        }
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}

void plCameraModifier::delTrans(size_t idx) {
    delete fTrans[idx];
    fTrans.erase(fTrans.begin() + idx);
}

void plCameraModifier::clearTrans() {
    for (auto trans = fTrans.begin(); trans != fTrans.end(); ++trans)
        delete *trans;
    fTrans.clear();
}

void plCameraModifier::delMessage(size_t idx) {
    delete fMessageQueue[idx];
    fMessageQueue.erase(fMessageQueue.begin() + idx);
    fSenderQueue.erase(fSenderQueue.begin() + idx);
}

void plCameraModifier::clearMessageQueue() {
    for (auto msg = fMessageQueue.begin(); msg != fMessageQueue.end(); ++msg)
        delete *msg;
    fMessageQueue.clear();
    fSenderQueue.clear();
}

void plCameraModifier::delFOVInstruction(size_t idx) {
    delete fFOVInstructions[idx];
    fFOVInstructions.erase(fFOVInstructions.begin() + idx);
}

void plCameraModifier::clearFOVInstructions() {
    for (auto inst = fFOVInstructions.begin(); inst != fFOVInstructions.end(); ++inst)
        delete *inst;
    fFOVInstructions.clear();
}
