#ifndef _PLSOUNDBUFFER_H
#define _PLSOUNDBUFFER_H

#include "PRP/KeyedObject/hsKeyedObject.h"

DllClass plWAVHeader {
public:
    enum { kPCMFormatTag = 0x1 };

protected:
    unsigned short fFormatTag, fNumChannels;
    unsigned int fNumSamplesPerSec, fAvgBytesPerSec;
    unsigned short fBlockAlign, fBitsPerSample;

public:
    plWAVHeader();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

    unsigned short getFormatTag() const;
    unsigned short getNumChannels() const;
    unsigned int getNumSamplesPerSec() const;
    unsigned int getAvgBytesPerSec() const;
    unsigned short getBlockAlign() const;
    unsigned short getBitsPerSample() const;

    void setFormatTag(unsigned short tag);
    void setNumChannels(unsigned short channels);
    void setNumSamplesPerSec(unsigned int samples);
    void setAvgBytesPerSec(unsigned int bytes);
    void setBlockAlign(unsigned short align);
    void setBitsPerSample(unsigned short bits);
};

DllClass plSoundBuffer : public hsKeyedObject {
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
    plSoundBuffer();
    virtual ~plSoundBuffer();

    DECLARE_CREATABLE(plSoundBuffer)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

    plWAVHeader& getHeader();
    const plWAVHeader& getHeader() const;
    
    plString getFileName() const;
    unsigned int getFlags() const;
    size_t getDataLength() const;
    unsigned char* getData() const;

    void setFileName(const plString& name);
    void setFlags(unsigned int flags);
    void setDataLength(size_t length);
    void setData(size_t length, const unsigned char* data);
};

#endif
