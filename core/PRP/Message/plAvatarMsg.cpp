#include "plAvatarMsg.h"

/* plAvatarMsg */
plAvatarMsg::plAvatarMsg() { }
plAvatarMsg::~plAvatarMsg() { }

IMPLEMENT_CREATABLE(plAvatarMsg, kAvatarMsg, plMessage)


/* plAvBrainGenericMsg */
plAvBrainGenericMsg::plAvBrainGenericMsg()
                   : fType(0), fWhichStage(0), fSetTime(false), fSetDirection(false),
                     fNewDirection(false), fNewTime(0.0f), fTransitionTime(0.0f) { }

plAvBrainGenericMsg::~plAvBrainGenericMsg() { }

IMPLEMENT_CREATABLE(plAvBrainGenericMsg, kAvBrainGenericMsg, plAvatarMsg)

void plAvBrainGenericMsg::read(hsStream* S, plResManager* mgr) {
    plMessage::read(S, mgr);

    fType = S->readInt();
    fWhichStage = S->readInt();
    fSetTime = S->readBool();
    fNewTime = S->readFloat();
    fSetDirection = S->readBool();
    fNewDirection = S->readBool();
    fTransitionTime = S->readFloat();
}

void plAvBrainGenericMsg::write(hsStream* S, plResManager* mgr) {
    plMessage::write(S, mgr);

    S->writeInt(fType);
    S->writeInt(fWhichStage);
    S->writeBool(fSetTime);
    S->writeFloat(fNewTime);
    S->writeBool(fSetDirection);
    S->writeBool(fNewDirection);
    S->writeFloat(fTransitionTime);
}

void plAvBrainGenericMsg::IPrcWrite(pfPrcHelper* prc) {
    plMessage::IPrcWrite(prc);

    prc->startTag("AvBrainGenericParams");
    prc->writeParam("Type", fType);
    prc->writeParam("Stage", fWhichStage);
    prc->writeParam("SetTime", fSetTime);
    prc->writeParam("NewTime", fNewTime);
    prc->writeParam("SetDirection", fSetDirection);
    prc->writeParam("NewDirection", fNewDirection);
    prc->writeParam("TransitionTime", fTransitionTime);
    prc->endTag(true);
}

void plAvBrainGenericMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "AvBrainGenericParams") {
        fType = tag->getParam("Type", "0").toUint();
        fWhichStage = tag->getParam("Stage", "0").toUint();
        fSetTime = tag->getParam("SetTime", "False").toBool();
        fNewTime = tag->getParam("NewTime", "0").toFloat();
        fSetDirection = tag->getParam("SetDirection", "False").toBool();
        fNewDirection = tag->getParam("NewDirection", "False").toBool();
        fTransitionTime = tag->getParam("TransitionTime", "0").toFloat();
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}
