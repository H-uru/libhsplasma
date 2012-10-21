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

#ifndef _PLSOUNDBUFFER_H
#define _PLSOUNDBUFFER_H

#include "PRP/KeyedObject/hsKeyedObject.h"

class PLASMA_DLL plWAVHeader {
public:
    enum { kPCMFormatTag = 0x1 };

protected:
    unsigned short fFormatTag, fNumChannels;
    unsigned int fNumSamplesPerSec, fAvgBytesPerSec;
    unsigned short fBlockAlign, fBitsPerSample;

public:
    plWAVHeader() : fFormatTag(0), fNumChannels(0), fNumSamplesPerSec(0),
                    fAvgBytesPerSec(0), fBlockAlign(0), fBitsPerSample(0) { }

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

public:
    unsigned short getFormatTag() const { return fFormatTag; }
    unsigned short getNumChannels() const { return fNumChannels; }
    unsigned int getNumSamplesPerSec() const { return fNumSamplesPerSec; }
    unsigned int getAvgBytesPerSec() const { return fAvgBytesPerSec; }
    unsigned short getBlockAlign() const { return fBlockAlign; }
    unsigned short getBitsPerSample() const { return fBitsPerSample; }

    void setFormatTag(unsigned short tag) { fFormatTag = tag; }
    void setNumChannels(unsigned short channels) { fNumChannels = channels; }
    void setNumSamplesPerSec(unsigned int samples) { fNumSamplesPerSec = samples; }
    void setAvgBytesPerSec(unsigned int bytes) { fAvgBytesPerSec = bytes; }
    void setBlockAlign(unsigned short align) { fBlockAlign = align; }
    void setBitsPerSample(unsigned short bits) { fBitsPerSample = bits; }
};


class PLASMA_DLL plSoundBuffer : public virtual hsKeyedObject {
    CREATABLE(plSoundBuffer, kSoundBuffer, hsKeyedObject)

public:
    enum Flags {
        kIsExternal = 0x1,
        kAlwaysExternal = 0x2,
        kOnlyLeftChannel = 0x4,
        kOnlyRightChannel = 0x8,
        kStreamCompressed = 0x10
    };

protected:
    plWAVHeader fHeader;
    plString fFileName;
    size_t fDataLength;
    unsigned char* fData;
    unsigned int fFlags;

public:
    plSoundBuffer() : fDataLength(0), fData(NULL), fFlags(0) { }
    virtual ~plSoundBuffer();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const plWAVHeader& getHeader() const { return fHeader; }
    plWAVHeader& getHeader() { return fHeader; }

    plString getFileName() const { return fFileName; }
    unsigned int getFlags() const { return fFlags; }
    size_t getDataLength() const { return fDataLength; }
    unsigned char* getData() const { return fData; }

    void setFileName(const plString& name) { fFileName = name; }
    void setFlags(unsigned int flags) { fFlags = flags; }
    void setData(size_t length, const unsigned char* data);
};

#endif
