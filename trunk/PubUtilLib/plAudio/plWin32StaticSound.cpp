#include "plWin32StaticSound.h"

/* plWin32StaticSound */
IMPLEMENT_CREATABLE(plWin32StaticSound, kWin32StaticSound, plWin32Sound)


/* plWin32GroupedSound */
IMPLEMENT_CREATABLE(plWin32GroupedSound, kWin32GroupedSound, plWin32StaticSound)

void plWin32GroupedSound::IRead(hsStream* S, plResManager* mgr) {
    plWin32Sound::IRead(S, mgr);

    unsigned short count = S->readShort();
    fStartPositions.setSizeNull(count);
    fVolumes.setSizeNull(count);
    for (unsigned short i=0; i<count; i++) {
        fStartPositions[i] = S->readInt();
        fVolumes[i] = S->readFloat();
    }
}

void plWin32GroupedSound::IWrite(hsStream* S, plResManager* mgr) {
    plWin32Sound::IWrite(S, mgr);

    S->writeShort(fStartPositions.getSize());
    for (unsigned short i=0; i<fStartPositions.getSize(); i++) {
        S->writeInt(fStartPositions[i]);
        S->writeFloat(fVolumes[i]);
    }
}

void plWin32GroupedSound::IPrcWrite(pfPrcHelper* prc) {
    plWin32Sound::IPrcWrite(prc);

    prc->writeSimpleTag("Volumes");
    for (unsigned short i=0; i<fStartPositions.getSize(); i++) {
        prc->startTag("VolumeSet");
        prc->writeParam("position", fStartPositions[i]);
        prc->writeParam("volume", fVolumes[i]);
        prc->endTag(true);
    }
    prc->closeTag();
}


/* plWin32LinkSound */
IMPLEMENT_CREATABLE(plWin32LinkSound, kWin32LinkSound, plWin32StaticSound)

void plWin32LinkSound::read(hsStream* S, plResManager* mgr) {
    plSound::read(S, mgr);
    fSynchFlags |= kLocalOnly;
    fProperties |= kPropDontFade;
}
