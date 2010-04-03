#include "plAvBrainGeneric.h"

plAvBrainGeneric::plAvBrainGeneric()
                : fCurStage(0), fType(kGeneric), fExitFlags(kExitNormal),
                  fMode(kNormal), fForward(true), fStartMessage(NULL),
                  fEndMessage(NULL), fFadeIn(6.0f), fFadeOut(0.0f),
                  fMoveMode(kMoveAbsolute), fBodyUsage(plAGAnim::kBodyUnknown)
                  { }

plAvBrainGeneric::~plAvBrainGeneric() {
    for (size_t i=0; i<fStages.getSize(); i++)
        delete fStages[i];
    if (fStartMessage != NULL)
        delete fStartMessage;
    if (fEndMessage != NULL)
        delete fEndMessage;
}

void plAvBrainGeneric::read(hsStream* S, plResManager* mgr) {
    plArmatureBrain::read(S, mgr);

    clearStages();
    fStages.setSizeNull(S->readInt());
    for (size_t i=0; i<fStages.getSize(); i++) {
        fStages[i] = plAnimStage::Convert(mgr->ReadCreatable(S));
        fStages[i]->readAux(S);
    }

    fCurStage = S->readInt();
    fType = (BrainType)S->readInt();
    fExitFlags = S->readInt();
    fMode = (Mode)S->readByte();
    fForward = S->readBool();

    if (S->readBool())
        setStartMessage(plMessage::Convert(mgr->ReadCreatable(S)));
    else
        setStartMessage(NULL);

    if (S->readBool())
        setEndMessage(plMessage::Convert(mgr->ReadCreatable(S)));
    else
        setEndMessage(NULL);

    fFadeIn = S->readFloat();
    fFadeOut = S->readFloat();
    fMoveMode = (MoveMode)S->readByte();
    fBodyUsage = (plAGAnim::BodyUsage)S->readByte();
    fRecipient = mgr->readKey(S);
}

void plAvBrainGeneric::write(hsStream* S, plResManager* mgr) {
    plArmatureBrain::write(S, mgr);

    S->writeInt(fStages.getSize());
    for (size_t i=0; i<fStages.getSize(); i++) {
        mgr->WriteCreatable(S, fStages[i]);
        fStages[i]->writeAux(S);
    }

    S->writeInt(fCurStage);
    S->writeInt(fType);
    S->writeInt(fExitFlags);
    S->writeByte(fMode);
    S->writeBool(fForward);

    S->writeBool(fStartMessage != NULL);
    if (fStartMessage != NULL)
        mgr->WriteCreatable(S, fStartMessage);

    S->writeBool(fEndMessage != NULL);
    if (fEndMessage != NULL)
        mgr->WriteCreatable(S, fEndMessage);

    S->writeFloat(fFadeIn);
    S->writeFloat(fFadeOut);
    S->writeByte(fMoveMode);
    S->writeByte(fBodyUsage);
    mgr->writeKey(S, fRecipient);
}

void plAvBrainGeneric::IPrcWrite(pfPrcHelper* prc) {
    plArmatureBrain::IPrcWrite(prc);

    prc->startTag("Stages");
    prc->writeParam("Current", fCurStage);
    prc->endTag();
    for (size_t i=0; i<fStages.getSize(); i++) {
        prc->writeSimpleTag("Stage");
        fStages[i]->prcWrite(prc);
        fStages[i]->prcWriteAux(prc);
        prc->closeTag();
    }
    prc->closeTag();

    prc->startTag("AvBrainGenericParams");
    prc->writeParam("Type", fType);
    prc->writeParamHex("ExitFlags", fExitFlags);
    prc->writeParam("Mode", fMode);
    prc->writeParam("Forward", fForward);
    prc->writeParam("FadeIn", fFadeIn);
    prc->writeParam("FadeOut", fFadeOut);
    prc->writeParam("MoveMode", fMoveMode);
    prc->writeParam("BodyUsage", fBodyUsage);
    prc->endTag(true);

    if (fStartMessage != NULL) {
        prc->writeSimpleTag("StartMessage");
        fStartMessage->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("StartMessage");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }

    if (fEndMessage != NULL) {
        prc->writeSimpleTag("EndMessage");
        fEndMessage->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->startTag("EndMessage");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }

    prc->writeSimpleTag("Recipient");
    fRecipient->prcWrite(prc);
    prc->closeTag();
}

void plAvBrainGeneric::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Stages") {
        fCurStage = tag->getParam("Current", "0").toInt();
        clearStages();
        fStages.setSizeNull(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fStages.getSize(); i++) {
            if (child->getName() != "Stage")
                throw pfPrcTagException(__FILE__, __LINE__, child->getName());
            const pfPrcTag* stageChild = child->getFirstChild();
            while (stageChild != NULL) {
                fStages[i] = new plAnimStage();
                if (stageChild->getName() == "plAnimStage") {
                    fStages[i]->prcParse(stageChild, mgr);
                } else if (stageChild->getName() == "plAnimStage_Aux") {
                    fStages[i]->prcParseAux(stageChild);
                } else {
                    throw pfPrcTagException(__FILE__, __LINE__, stageChild->getName());
                }
                stageChild = stageChild->getNextSibling();
            }
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "AvBrainGenericParams") {
        fType = (BrainType)tag->getParam("Type", "0").toUint();
        fExitFlags = tag->getParam("ExitFlags", "0").toUint();
        fMode = (Mode)tag->getParam("Mode", "0").toUint();
        fForward = tag->getParam("Forward", "False").toBool();
        fFadeIn = tag->getParam("FadeIn", "0").toFloat();
        fFadeOut = tag->getParam("FadeOut", "0").toFloat();
        fMoveMode = (MoveMode)tag->getParam("MoveMode", "0").toUint();
        fBodyUsage = (plAGAnim::BodyUsage)tag->getParam("BodyUsage", "0").toUint();
    } else if (tag->getName() == "StartMessage") {
        if (tag->getParam("NULL", "False").toBool()) {
            setStartMessage(NULL);
        } else if (tag->hasChildren()) {
            setStartMessage(plMessage::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
        }
    } else if (tag->getName() == "EndMessage") {
        if (tag->getParam("NULL", "False").toBool()) {
            setEndMessage(NULL);
        } else if (tag->hasChildren()) {
            setEndMessage(plMessage::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
        }
    } else if (tag->getName() == "Recipient") {
        if (tag->hasChildren())
            fRecipient = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plArmatureBrain::IPrcParse(tag, mgr);
    }
}

void plAvBrainGeneric::delStage(size_t idx) {
    delete fStages[idx];
    fStages.remove(idx);
}

void plAvBrainGeneric::clearStages() {
    for (size_t i=0; i<fStages.getSize(); i++)
        delete fStages[i];
    fStages.setSize(0);
}

void plAvBrainGeneric::setStartMessage(plMessage* msg) {
    if (fStartMessage != NULL)
        delete fStartMessage;
    fStartMessage = msg;
}

void plAvBrainGeneric::setEndMessage(plMessage* msg) {
    if (fEndMessage != NULL)
        delete fEndMessage;
    fEndMessage = msg;
}
