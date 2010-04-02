#include "plSoundBuffer.h"

/* plWAVHeader */
plWAVHeader::plWAVHeader()
           : fFormatTag(0), fNumChannels(0), fNumSamplesPerSec(0),
             fAvgBytesPerSec(0), fBlockAlign(0), fBitsPerSample(0) { }

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

void plWAVHeader::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "WavHeader")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fFormatTag = tag->getParam("Format", "0").toUint();
    fNumChannels = tag->getParam("Channels", "0").toUint();
    fNumSamplesPerSec = tag->getParam("SamplesPerSec", "0").toUint();
    fAvgBytesPerSec = tag->getParam("BytesPerSec", "0").toUint();
    fBlockAlign = tag->getParam("BlockAlign", "0").toUint();
    fBitsPerSample = tag->getParam("BitsPerSample", "0").toUint();
}


/* plSoundBuffer */
plSoundBuffer::plSoundBuffer() : fDataLength(0), fData(NULL), fFlags(0) { }

plSoundBuffer::~plSoundBuffer() {
    if (fData != NULL)
        delete[] fData;
}

void plSoundBuffer::read(hsStream* S, plResManager* mgr) {
    hsKeyedObject::read(S, mgr);

    fFlags = S->readInt();
    fDataLength = S->readInt();
    fFileName = S->readSafeStr();
    fHeader.read(S);

    if (!(fFlags & kIsExternal)) {
        fData = new unsigned char[fDataLength];
        S->read(fDataLength, fData);
    } else {
        fData = NULL;
    }
}

void plSoundBuffer::write(hsStream* S, plResManager* mgr) {
    hsKeyedObject::write(S, mgr);

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

void plSoundBuffer::IPrcWrite(pfPrcHelper* prc) {
    hsKeyedObject::IPrcWrite(prc);

    prc->startTag("SoundBuffer");
    prc->writeParamHex("Flags", fFlags);
    prc->writeParam("Length", (unsigned long)fDataLength);
    prc->writeParam("Filename", fFileName);
    prc->endTag(fData == NULL);
    if (fData != NULL) {
        prc->writeHexStream(fDataLength, fData);
        prc->closeTag();
    }
    fHeader.prcWrite(prc);
}

void plSoundBuffer::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "SoundBuffer") {
        fFlags = tag->getParam("Flags", "0").toUint();
        fDataLength = tag->getParam("Length", "0").toUint();
        fFileName = tag->getParam("Filename", "");
        if (tag->getContents().getSize() != 0) {
            fData = new unsigned char[fDataLength];
            tag->readHexStream(fDataLength, fData);
        }
    } else if (tag->getName() == "WavHeader") {
        fHeader.prcParse(tag);
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}

void plSoundBuffer::setData(size_t length, const unsigned char* data) {
    if (fData != NULL)
        delete[] fData;

    if (length == 0 || data == NULL) {
        fDataLength = length;   // Length can be specified with a null datum
        fData = NULL;
    } else {
        fDataLength = length;
        fData = new unsigned char[length];
        memcpy(fData, data, length);
    }
}
