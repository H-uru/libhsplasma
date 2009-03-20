#include "plCrossfade.h"

/* plCrossfade */
plCrossfade::plCrossfade()
           : fFirstIdx(0), fSecondIdx(0), fStartType(0), fEndType(0),
             fFlags(0), fRegistered(false) { }

IMPLEMENT_CREATABLE(plCrossfade, kCrossfade, plSingleModifier)

void plCrossfade::read(hsStream* S, plResManager* mgr) {
    plSingleModifier::read(S, mgr);

    fFirstIdx = S->readShort();
    fSecondIdx = S->readShort();
    fStartType = S->readInt();
    fEndType = S->readInt();
    fFlags = S->readInt();
    fRegistered = S->readBool();
}

void plCrossfade::write(hsStream* S, plResManager* mgr) {
    plSingleModifier::write(S, mgr);

    S->writeShort(fFirstIdx);
    S->writeShort(fSecondIdx);
    S->writeInt(fStartType);
    S->writeInt(fEndType);
    S->writeInt(fFlags);
    S->writeBool(fRegistered);
}

void plCrossfade::IPrcWrite(pfPrcHelper* prc) {
    plSingleModifier::IPrcWrite(prc);

    prc->startTag("CrossfadeParams");
    prc->writeParam("First", fFirstIdx);
    prc->writeParam("Second", fSecondIdx);
    prc->writeParam("StartType", fStartType);
    prc->writeParam("EndType", fEndType);
    prc->writeParamHex("Flags", fFlags);
    prc->writeParam("Registered", fRegistered);
    prc->endTag(true);
}

void plCrossfade::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "CrossfadeParams") {
        fFirstIdx = tag->getParam("First", "0").toUint();
        fSecondIdx = tag->getParam("Second", "0").toUint();
        fStartType = tag->getParam("StartType", "0").toUint();
        fEndType = tag->getParam("EndType", "0").toUint();
        fFlags = tag->getParam("Flags", "0").toUint();
        fRegistered = tag->getParam("Registered", "false").toBool();
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}

unsigned short plCrossfade::getFirstIdx() const { return fFirstIdx; }
unsigned short plCrossfade::getSecondIdx() const { return fSecondIdx; }
unsigned int plCrossfade::getStartType() const { return fStartType; }
unsigned int plCrossfade::getEndType() const { return fEndType; }
unsigned int plCrossfade::getFlags() const { return fFlags; }
bool plCrossfade::isRegistered() const { return fRegistered; }

void plCrossfade::setFirstIdx(unsigned short idx) { fFirstIdx = idx; }
void plCrossfade::setSecondIdx(unsigned short idx) { fSecondIdx = idx; }
void plCrossfade::setStartType(unsigned int type) { fStartType = type; }
void plCrossfade::setEndType(unsigned int type) { fEndType = type; }
void plCrossfade::setFlags(unsigned int flags) { fFlags = flags; }
void plCrossfade::setRegistered(bool registered) { fRegistered = registered; }


/* plCrossfadeMsg */
IMPLEMENT_CREATABLE(plCrossfadeMsg, kCrossfadeMsg, plMessage)
