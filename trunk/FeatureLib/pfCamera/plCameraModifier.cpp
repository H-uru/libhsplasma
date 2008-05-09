#include "plCameraModifier.h"

/* plCameraModifier1::CamTrans */
plCameraModifier1::CamTrans::CamTrans()
                : fCutPos(false), fCutPOA(false), fIgnore(false), fAccel(60.0f),
                  fDecel(60.0f), fVelocity(60.0f), fPOAAccel(60.0f),
                  fPOADecel(60.0f), fPOAVelocity(60.0f) { }

plCameraModifier1::CamTrans::~CamTrans() { }

void plCameraModifier1::CamTrans::read(hsStream* S, plResManager* mgr) {
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

void plCameraModifier1::CamTrans::write(hsStream* S, plResManager* mgr) {
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

void plCameraModifier1::CamTrans::prcWrite(pfPrcHelper* prc) {
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
      prc->writeSimpleTag("TansTo");
      fTransTo->prcWrite(prc);
      prc->closeTag();
    prc->closeTag();
}

void plCameraModifier1::CamTrans::prcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() != "CamTrans")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fCutPos = tag->getParam("CutPos", "false").toBool();
    fCutPOA = tag->getParam("CutPOA", "false").toBool();
    fIgnore = tag->getParam("Ignore", "false").toBool();
    fVelocity = tag->getParam("Velocity", "0").toFloat();
    fAccel = tag->getParam("Accel", "0").toFloat();
    fDecel = tag->getParam("Decel", "0").toFloat();
    fPOAVelocity = tag->getParam("POAVelocity", "0").toFloat();
    fPOAAccel = tag->getParam("POAAccel", "0").toFloat();
    fPOADecel = tag->getParam("POADecel", "0").toFloat();

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


/* plCameraModifier1 */
plCameraModifier1::plCameraModifier1()
                 : fFrom(0.0f, 0.0f, 0.0f), fAt(0.0f, 1.0f, 0.0f),
                   fFOVw(45.0f), fFOVh(33.75f), fAnimated(false),
                   fStartAnimOnPush(false), fStopAnimOnPop(false),
                   fResetAnimOnPop(false) { }

plCameraModifier1::~plCameraModifier1() {
    for (size_t i=0; i<fTrans.getSize(); i++)
        delete fTrans[i];
    for (size_t i=0; i<fMessageQueue.getSize(); i++)
        delete fMessageQueue[i];
    for (size_t i=0; i<fFOVInstructions.getSize(); i++)
        delete fFOVInstructions[i];
}

IMPLEMENT_CREATABLE(plCameraModifier1, kCameraModifier1, plSingleModifier)

void plCameraModifier1::read(hsStream* S, plResManager* mgr) {
    hsKeyedObject::read(S, mgr);

    fBrain = mgr->readKey(S);
    fTrans.setSizeNull(S->readInt());
    for (size_t i=0; i<fTrans.getSize(); i++) {
        fTrans[i] = new CamTrans();
        fTrans[i]->read(S, mgr);
    }
    fFOVw = S->readFloat();
    fFOVh = S->readFloat();

    fMessageQueue.setSizeNull(S->readInt());
    fSenderQueue.setSize(fMessageQueue.getSize());
    for (size_t i=0; i<fMessageQueue.getSize(); i++)
        fMessageQueue[i] = plMessage::Convert(mgr->ReadCreatable(S));
    for (size_t i=0; i<fSenderQueue.getSize(); i++)
        fSenderQueue[i] = mgr->readKey(S);

    fFOVInstructions.setSizeNull(S->readInt());
    for (size_t i=0; i<fFOVInstructions.getSize(); i++)
        fFOVInstructions[i] = plCameraMsg::Convert(mgr->ReadCreatable(S));

    fAnimated = S->readBool();
    fStartAnimOnPush = S->readBool();
    fStopAnimOnPop = S->readBool();
    fResetAnimOnPop = S->readBool();
}

void plCameraModifier1::write(hsStream* S, plResManager* mgr) {
    hsKeyedObject::write(S, mgr);

    mgr->writeKey(S, fBrain);
    S->writeInt(fTrans.getSize());
    for (size_t i=0; i<fTrans.getSize(); i++)
        fTrans[i]->write(S, mgr);
    S->writeFloat(fFOVw);
    S->writeFloat(fFOVh);

    S->writeInt(fMessageQueue.getSize());
    for (size_t i=0; i<fMessageQueue.getSize(); i++)
        mgr->WriteCreatable(S, fMessageQueue[i]);
    for (size_t i=0; i<fSenderQueue.getSize(); i++)
        mgr->writeKey(S, fSenderQueue[i]);

    S->writeInt(fFOVInstructions.getSize());
    for (size_t i=0; i<fFOVInstructions.getSize(); i++)
        mgr->WriteCreatable(S, fFOVInstructions[i]);

    S->writeBool(fAnimated);
    S->writeBool(fStartAnimOnPush);
    S->writeBool(fStopAnimOnPop);
    S->writeBool(fResetAnimOnPop);
}

void plCameraModifier1::IPrcWrite(pfPrcHelper* prc) {
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
    fBrain->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Transforms");
    for (size_t i=0; i<fTrans.getSize(); i++)
        fTrans[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("MessageQueue");
    for (size_t i=0; i<fMessageQueue.getSize(); i++) {
        prc->writeSimpleTag("Message");
        fMessageQueue[i]->prcWrite(prc);
        prc->closeTag();
        prc->writeSimpleTag("Sender");
        fSenderQueue[i]->prcWrite(prc);
        prc->closeTag();
    }
    prc->closeTag();

    prc->writeSimpleTag("FOVInstructions");
    for (size_t i=0; i<fFOVInstructions.getSize(); i++)
        fFOVInstructions[i]->prcWrite(prc);
    prc->closeTag();
}

void plCameraModifier1::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "CameraModParams") {
        fFOVw = tag->getParam("FOVw", "45").toFloat();
        fFOVh = tag->getParam("FOVh", "33.75").toFloat();
        fAnimated = tag->getParam("Animated", "false").toBool();
        fStartAnimOnPush = tag->getParam("StartAnimOnPush", "false").toBool();
        fStopAnimOnPop = tag->getParam("StopAnimOnPop", "false").toBool();
        fResetAnimOnPop = tag->getParam("ResetAnimOnPop", "false").toBool();
    } else if (tag->getName() == "Brain") {
        if (tag->hasChildren())
            fBrain = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Transforms") {
        fTrans.setSizeNull(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fTrans.getSize(); i++) {
            fTrans[i] = new CamTrans();
            fTrans[i]->prcParse(child, mgr);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "MessageQueue") {
        fMessageQueue.setSizeNull(tag->countChildren() / 2);
        fSenderQueue.setSize(fMessageQueue.getSize());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fMessageQueue.getSize(); i++) {
            fMessageQueue[i] = plMessage::Convert(mgr->prcParseCreatable(child));
            child = child->getNextSibling();
            fSenderQueue[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "FOVInstructions") {
        fFOVInstructions.setSizeNull(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fFOVInstructions.getSize(); i++) {
            fFOVInstructions[i] = plCameraMsg::Convert(mgr->prcParseCreatable(child));
            child = child->getNextSibling();
        }
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}
