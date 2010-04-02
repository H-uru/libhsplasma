#include "plAGApplicator.h"

/* plAGApplicator */
plAGApplicator::plAGApplicator() : fChannel(NULL), fEnabled(true) { }

plAGApplicator::~plAGApplicator() {
    if (fChannel != NULL)
        delete fChannel;
}

void plAGApplicator::read(hsStream* S, plResManager* mgr) {
    fEnabled = S->readBool();
    fChannelName = S->readSafeStr();
}

void plAGApplicator::write(hsStream* S, plResManager* mgr) {
    S->writeBool(fEnabled);
    S->writeSafeStr(fChannelName);
}

void plAGApplicator::IPrcWrite(pfPrcHelper* prc) {
    prc->startTag("AGApplicatorParams");
    prc->writeParam("Enabled", fEnabled);
    prc->writeParam("ChannelName", fChannelName);
    prc->endTag(true);
}

void plAGApplicator::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "AGApplicatorParams") {
        fEnabled = tag->getParam("Enabled", "false").toBool();
        fChannelName = tag->getParam("ChannelName", "");
    } else {
        plCreatable::IPrcParse(tag, mgr);
    }
}

void plAGApplicator::setChannel(plAGChannel* chan) {
    if (fChannel != NULL)
        delete fChannel;
    fChannel = chan;
}


/* plSoundVolumeApplicator */
plSoundVolumeApplicator::plSoundVolumeApplicator() : fIndex(0) { }

void plSoundVolumeApplicator::read(hsStream* S, plResManager* mgr) {
    plAGApplicator::read(S, mgr);
    fIndex = S->readInt();
}

void plSoundVolumeApplicator::write(hsStream* S, plResManager* mgr) {
    plAGApplicator::write(S, mgr);
    S->writeInt(fIndex);
}

void plSoundVolumeApplicator::IPrcWrite(pfPrcHelper* prc) {
    plAGApplicator::IPrcWrite(prc);

    prc->startTag("SoundVolumeApplicatorParams");
    prc->writeParam("Index", fIndex);
    prc->endTag(true);
}

void plSoundVolumeApplicator::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "SoundVolumeApplicatorParams") {
        fIndex = tag->getParam("Index", "0").toUint();
    } else {
        plAGApplicator::IPrcParse(tag, mgr);
    }
}
