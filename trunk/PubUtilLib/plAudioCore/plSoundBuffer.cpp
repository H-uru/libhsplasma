#include "plSoundBuffer.h"

// plWAVHeader //
void plWAVHeader::read(hsStream* S) {
    fFormatTag = S->readShort();
    fNumChannels = S->readShort();
    fNumSamplesPerSec = S->readInt();
    fAvgBytesPerSec = S->readInt();
    fBlockAlign = S->readShort();
    fBitsPerSample = S->readShort();
}

void plWAVHeader::write(hsStream* S) {
    S->writeShort(fFormatTag);
    S->writeShort(fNumChannels);
    S->writeInt(fNumSamplesPerSec);
    S->writeInt(fAvgBytesPerSec);
    S->writeShort(fBlockAlign);
    S->writeShort(fBitsPerSample);
}

void plWAVHeader::prcWrite(pfPrcHelper* prc) {
    prc->startTag("WavHeader");
    prc->writeParam("Format", fFormatTag);
    prc->writeParam("Channels", fNumChannels);
    prc->writeParam("SamplesPerSec", fNumSamplesPerSec);
    prc->writeParam("BytesPerSec", fAvgBytesPerSec);
    prc->writeParam("BlockAlign", fBlockAlign);
    prc->writeParam("BitsPerSample", fBitsPerSample);
    prc->endTag(true);
}


// plSoundBuffer //
plSoundBuffer::plSoundBuffer() : fData(NULL) { }

plSoundBuffer::~plSoundBuffer() {
    if (fData) delete[] fData;
}

IMPLEMENT_CREATABLE(plSoundBuffer, kSoundBuffer, hsKeyedObject)

void plSoundBuffer::read(hsStream* S) {
    hsKeyedObject::read(S);

    fFlags = S->readInt();
    fDataLength = S->readInt();
    fFileName = S->readSafeStr();
    fHeader.read(S);

    fValid = false;
    if (!(fFlags & kIsExternal)) {
        fData = new unsigned char[fDataLength];
        S->read(fDataLength, fData);
        fValid = true;
    } else {
        fValid = true;
        fData = NULL;
    }
}

void plSoundBuffer::write(hsStream* S) {
    hsKeyedObject::write(S);

    if (fData == NULL)
        fFlags |= kIsExternal;
    S->writeInt(fFlags);
    S->writeInt(fDataLength);
    plString writeFileName = fFileName;
    if (!fFileName.empty()) {
        writeFileName = strrchr(fFileName, '\\');
        if (writeFileName != NULL)
            fFileName = writeFileName;
    }
    S->writeSafeStr(fFileName);
    fHeader.write(S);

    if (!(fFlags & kIsExternal))
        S->write(fDataLength, fData);
}

void plSoundBuffer::prcWrite(pfPrcHelper* prc) {
    hsKeyedObject::prcWrite(prc);

    prc->startTag("SoundBuffer");
    prc->writeParam("Flags", fFlags);
    prc->writeParam("Length", fDataLength);
    if (fFileName != NULL)
        prc->writeParam("Filename", fFileName);
    prc->endTag(true);
    fHeader.prcWrite(prc);
}

