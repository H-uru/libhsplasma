#include "plSimpleRegionSensor.h"

/* plSimpleRegionSensor */
plSimpleRegionSensor::plSimpleRegionSensor() : fEnterMsg(NULL), fExitMsg(NULL) { }

plSimpleRegionSensor::~plSimpleRegionSensor() {
    if (fEnterMsg != NULL)
        delete fEnterMsg;
    if (fExitMsg != NULL)
        delete fExitMsg;
}

IMPLEMENT_CREATABLE(plSimpleRegionSensor, kSimpleRegionSensor, plSingleModifier)

void plSimpleRegionSensor::read(hsStream* S, plResManager* mgr) {
    plSingleModifier::read(S, mgr);

    setEnterMsg(S->readBool() ? plMessage::Convert(mgr->ReadCreatable(S)) : NULL);
    setExitMsg(S->readBool() ? plMessage::Convert(mgr->ReadCreatable(S)) : NULL);
}

void plSimpleRegionSensor::write(hsStream* S, plResManager* mgr) {
    plSingleModifier::write(S, mgr);

    if (fEnterMsg != NULL) {
        S->writeBool(true);
        mgr->WriteCreatable(S, fEnterMsg);
    } else {
        S->writeBool(false);
    }
    if (fExitMsg != NULL) {
        S->writeBool(true);
        mgr->WriteCreatable(S, fExitMsg);
    } else {
        S->writeBool(false);
    }
}

void plSimpleRegionSensor::IPrcWrite(pfPrcHelper* prc) {
    plSingleModifier::IPrcWrite(prc);

    prc->startTag("EnterMsg");
    if (fEnterMsg != NULL) {
        prc->endTag(false);
        fEnterMsg->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
    prc->startTag("ExitMsg");
    if (fExitMsg != NULL) {
        prc->endTag(false);
        fExitMsg->prcWrite(prc);
        prc->closeTag();
    } else {
        prc->writeParam("NULL", true);
        prc->endTag(true);
    }
}

void plSimpleRegionSensor::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "EnterMsg") {
        if (tag->getParam("NULL", "false").toBool())
            setEnterMsg(NULL);
        else if (tag->hasChildren())
            setEnterMsg(plMessage::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
    } else if (tag->getName() == "ExitMsg") {
        if (tag->getParam("NULL", "false").toBool())
            setExitMsg(NULL);
        else if (tag->hasChildren())
            setExitMsg(plMessage::Convert(mgr->prcParseCreatable(tag->getFirstChild())));
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}

void plSimpleRegionSensor::setEnterMsg(plMessage* msg) {
    if (fEnterMsg != NULL)
        delete fEnterMsg;
    fEnterMsg = msg;
}

void plSimpleRegionSensor::setExitMsg(plMessage* msg) {
    if (fExitMsg != NULL)
        delete fExitMsg;
    fExitMsg = msg;
}


/* plSwimDetector */
plSwimDetector::plSwimDetector() { }

IMPLEMENT_CREATABLE(plSwimDetector, kSwimDetector, plSimpleRegionSensor)

void plSwimDetector::read(hsStream* S, plResManager* mgr) {
    plSimpleRegionSensor::read(S, mgr);
    S->readByte();
    S->readFloat();
    S->readFloat();
}

void plSwimDetector::write(hsStream* S, plResManager* mgr) {
    plSimpleRegionSensor::write(S, mgr);
    S->writeByte(0);
    S->writeFloat(0.0f);
    S->writeFloat(0.0f);
}


/* plAutoWalkRegion */
plAutoWalkRegion::plAutoWalkRegion() : fUnknown(0) { }

IMPLEMENT_CREATABLE(plAutoWalkRegion, kAutoWalkRegion, plSimpleRegionSensor)

void plAutoWalkRegion::read(hsStream* S, plResManager* mgr) {
    plSimpleRegionSensor::read(S, mgr);
    fUnknown = S->readInt();
}

void plAutoWalkRegion::write(hsStream* S, plResManager* mgr) {
    plSimpleRegionSensor::write(S, mgr);
    S->writeInt(fUnknown);
}

void plAutoWalkRegion::IPrcWrite(pfPrcHelper* prc) {
    plSimpleRegionSensor::IPrcWrite(prc);

    prc->startTag("AutoWalkParams");
    prc->writeParam("Unknown", fUnknown);
    prc->endTag(true);
}

void plAutoWalkRegion::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "AutoWalkParams") {
        fUnknown = tag->getParam("Unknown", "0").toUint();
    } else {
        plSimpleRegionSensor::IPrcParse(tag, mgr);
    }
}


/* plRidingAnimatedPhysicalDetector */
plRidingAnimatedPhysicalDetector::plRidingAnimatedPhysicalDetector() { }

IMPLEMENT_CREATABLE(plRidingAnimatedPhysicalDetector,
                    kRidingAnimatedPhysicalDetector,
                    plSimpleRegionSensor)
