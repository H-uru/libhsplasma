#include "plDirectMusicSound.h"

plDirectMusicSound::plDirectMusicSound() : fUnknown1(0) { }
plDirectMusicSound::~plDirectMusicSound() { }

IMPLEMENT_CREATABLE(plDirectMusicSound, kDirectMusicSound, plSound)

void plDirectMusicSound::read(hsStream* S, plResManager* mgr) {
    plSound::read(S, mgr);

    fUnknown1 = S->readInt();
    fFileName = S->readSafeStr();
}

void plDirectMusicSound::write(hsStream* S, plResManager* mgr) {
    plSound::write(S, mgr);

    S->writeInt(fUnknown1);
    S->writeSafeStr(fFileName);
}

void plDirectMusicSound::IPrcWrite(pfPrcHelper* prc) {
    plSound::IPrcWrite(prc);

    prc->startTag("DirectMusicParams");
    prc->writeParam("FileName", fFileName);
    prc->writeParamHex("Unknown", fUnknown1);
    prc->endTag(true);
}

void plDirectMusicSound::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "DirectMusicParams") {
        fFileName = tag->getParam("FileName", "");
        fUnknown1 = tag->getParam("Unknown", "0").toUint();
    } else {
        plSound::IPrcParse(tag, mgr);
    }
}
