#include "plSoundBuffer.h"

// plWAVHeader //
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

unsigned short plWAVHeader::getFormatTag() const { return fFormatTag; }
unsigned short plWAVHeader::getNumChannels() const { return fNumChannels; }
unsigned int plWAVHeader::getNumSamplesPerSec() const { return fNumSamplesPerSec; }
unsigned int plWAVHeader::getAvgBytesPerSec() const { return fAvgBytesPerSec; }
unsigned short plWAVHeader::getBlockAlign() const { return fBlockAlign; }
unsigned short plWAVHeader::getBitsPerSample() const { return fBitsPerSample; }

void plWAVHeader::setFormatTag(unsigned short tag) { fFormatTag = tag; }
void plWAVHeader::setNumChannels(unsigned short channels) { fNumChannels = channels; }
void plWAVHeader::setNumSamplesPerSec(unsigned int samples) { fNumSamplesPerSec = samples; }
void plWAVHeader::setAvgBytesPerSec(unsigned int bytes) { fAvgBytesPerSec = bytes; }
void plWAVHeader::setBlockAlign(unsigned short align) { fBlockAlign = align; }
void plWAVHeader::setBitsPerSample(unsigned short bits) { fBitsPerSample = bits; }


// plSoundBuffer //
plSoundBuffer::plSoundBuffer() : fDataLength(0), fData(NULL), fFlags(0) { }

plSoundBuffer::~plSoundBuffer() {
    if (fData != NULL)
        delete[] fData;
}

IMPLEMENT_CREATABLE(plSoundBuffer, kSoundBuffer, hsKeyedObject)

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
    prc->writeParam("Length", fDataLength);
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

plWAVHeader& plSoundBuffer::getHeader() { return fHeader; }
const plWAVHeader& plSoundBuffer::getHeader() const { return fHeader; }

plString plSoundBuffer::getFileName() const { return fFileName; }
unsigned int plSoundBuffer::getFlags() const { return fFlags; }
size_t plSoundBuffer::getDataLength() const { return fDataLength; }
unsigned char* plSoundBuffer::getData() const { return fData; }

void plSoundBuffer::setFileName(const plString& name) { fFileName = name; }
void plSoundBuffer::setFlags(unsigned int flags) { fFlags = flags; }
void plSoundBuffer::setDataLength(size_t length) { fDataLength = length; }

void plSoundBuffer::setData(size_t length, const unsigned char* data) {
    if (fData != NULL)
        delete[] fData;

    if (length == 0 || data == NULL) {
        // Length can still be meaningful; don't modify it!
        fData = NULL;
    } else {
        fDataLength = length;
        fData = new unsigned char[length];
        memcpy(fData, data, length);
    }
}
