/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "plSoundBuffer.h"
#include <cstring>

/* plWAVHeader */
void plWAVHeader::read(hsStream* S)
{
    fFormatTag = S->readShort();
    fNumChannels = S->readShort();
    fNumSamplesPerSec = S->readInt();
    fAvgBytesPerSec = S->readInt();
    fBlockAlign = S->readShort();
    fBitsPerSample = S->readShort();
}

void plWAVHeader::write(hsStream* S)
{
    S->writeShort(fFormatTag);
    S->writeShort(fNumChannels);
    S->writeInt(fNumSamplesPerSec);
    S->writeInt(fAvgBytesPerSec);
    S->writeShort(fBlockAlign);
    S->writeShort(fBitsPerSample);
}

void plWAVHeader::prcWrite(pfPrcHelper* prc)
{
    prc->startTag("WavHeader");
    prc->writeParam("Format", fFormatTag);
    prc->writeParam("Channels", fNumChannels);
    prc->writeParam("SamplesPerSec", fNumSamplesPerSec);
    prc->writeParam("BytesPerSec", fAvgBytesPerSec);
    prc->writeParam("BlockAlign", fBlockAlign);
    prc->writeParam("BitsPerSample", fBitsPerSample);
    prc->endTag(true);
}

void plWAVHeader::prcParse(const pfPrcTag* tag)
{
    if (tag->getName() != "WavHeader")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fFormatTag = tag->getParam("Format", "0").to_uint();
    fNumChannels = tag->getParam("Channels", "0").to_uint();
    fNumSamplesPerSec = tag->getParam("SamplesPerSec", "0").to_uint();
    fAvgBytesPerSec = tag->getParam("BytesPerSec", "0").to_uint();
    fBlockAlign = tag->getParam("BlockAlign", "0").to_uint();
    fBitsPerSample = tag->getParam("BitsPerSample", "0").to_uint();
}


/* plSoundBuffer */
plSoundBuffer::~plSoundBuffer()
{
    delete[] fData;
}

void plSoundBuffer::read(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::read(S, mgr);

    fFlags = S->readInt();
    fDataLength = S->readInt();
    fFileName = S->readSafeStr();
    fHeader.read(S);

    if (S->getVer() < MAKE_VERSION(2, 0, 63, 8)) {
        S->readInt();
        S->readInt();
        S->readByte();
        S->readByte();
    }

    if (!(fFlags & kIsExternal)) {
        fData = new unsigned char[fDataLength];
        S->read(fDataLength, fData);
    } else {
        fData = nullptr;
    }
}

void plSoundBuffer::write(hsStream* S, plResManager* mgr)
{
    hsKeyedObject::write(S, mgr);

    if (fData == nullptr)
        fFlags |= kIsExternal;
    S->writeInt(fFlags);
    S->writeInt(fDataLength);
    ST::string writeFileName = fFileName;
    if (!fFileName.empty()) {
        writeFileName = strrchr(fFileName.c_str(), '\\');
        if (writeFileName != NULL)
            fFileName = writeFileName;
    }
    S->writeSafeStr(fFileName);
    fHeader.write(S);

    if (!(fFlags & kIsExternal))
        S->write(fDataLength, fData);
}

void plSoundBuffer::IPrcWrite(pfPrcHelper* prc)
{
    hsKeyedObject::IPrcWrite(prc);

    prc->startTag("SoundBuffer");
    prc->writeParamHex("Flags", fFlags);
    prc->writeParam("Length", (unsigned long)fDataLength);
    prc->writeParam("Filename", fFileName);
    prc->endTag(fData == nullptr);
    if (fData) {
        prc->writeHexStream(fDataLength, fData);
        prc->closeTag();
    }
    fHeader.prcWrite(prc);
}

void plSoundBuffer::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "SoundBuffer") {
        fFlags = tag->getParam("Flags", "0").to_uint();
        fDataLength = tag->getParam("Length", "0").to_uint();
        fFileName = tag->getParam("Filename", "");
        if (!tag->getContents().empty()) {
            fData = new unsigned char[fDataLength];
            tag->readHexStream(fDataLength, fData);
        }
    } else if (tag->getName() == "WavHeader") {
        fHeader.prcParse(tag);
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}

void plSoundBuffer::setData(size_t length, const unsigned char* data)
{
    delete[] fData;

    if (length == 0 || data == nullptr) {
        fDataLength = length;   // Length can be specified with a null datum
        fData = nullptr;
    } else {
        fDataLength = length;
        fData = new unsigned char[length];
        memcpy(fData, data, length);
    }
}
