#ifndef _PLSOUNDBUFFER_H
#define _PLSOUNDBUFFER_H

#include "NucleusLib/pnKeyedObject/hsKeyedObject.h"

class plWAVHeader {
public:
    enum { kPCMFormatTag = 0x1 };

public:
    unsigned short fFormatTag, fNumChannels;
    unsigned int fNumSamplesPerSec, fAvgBytesPerSec;
    unsigned short fBlockAlign, fBitsPerSample;

public:
    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
};

class plSoundBuffer : public hsKeyedObject {
public:
    enum Flags {
        kIsExternal = 0x1,
        kAlwaysExternal = 0x2,
        kOnlyLeftChannel = 0x4,
        kOnlyRightChannel = 0x8,
        kStreamCompressed = 0x10
    };

    enum ELoadReturnVal { kSuccess, kError, kNotComplete };

protected:
    plWAVHeader fHeader;
    //plAuidoFileReader* fReader;
    plString fFileName;
    unsigned int fDataLength;
    unsigned char* fData;
    unsigned int fFlags;
    bool fValid;
    unsigned int fDataRecord;

public:
    plSoundBuffer();
    virtual ~plSoundBuffer();

    DECLARE_CREATABLE(plSoundBuffer)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif

