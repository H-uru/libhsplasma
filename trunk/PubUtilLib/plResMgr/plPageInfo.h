#ifndef _PLPAGEINFO_H
#define _PLPAGEINFO_H

#include "../../CoreLib/hsStream.h"
#include "../../NucleusLib/pnKeyedObject/plUoid.h"

class plPageInfo {
public:
    enum Flags {
        kPartialPatchFile = 0x1,
        kOldDataChecksum = 0x2,
        kOldIdxChecksum = 0x4,
        kBasicChecksum = 0x8,
        kPatchHeaderOnly = 0x10,
        kChecksumMask = kBasicChecksum | kOldIdxChecksum | kOldDataChecksum,
        kPatchFlags = kPatchHeaderOnly | kPartialPatchFile
    };

protected:
    plLocation location;
    char* age;
    char* page;
    unsigned int idxChecksum, checksum;
    int releaseVersion;
    unsigned int dataStart, idxStart, flags;

public:
    unsigned int nObjects;
    bool holdFlag;

public:
    plPageInfo();
    ~plPageInfo();

    void IInit();
    bool isValid();

    void read(hsStream* S);
    void write(hsStream* S);
    void writeSums(hsStream* S);

    const char* getAge();
    const char* getChapter();
    const char* getPage();
    unsigned int getChecksum();
    unsigned int getDataStart();
    unsigned int getIndexStart();
    unsigned int getFlags();
    plLocation& getLocation();

    void setChecksum(unsigned int);
    void setReleaseVersion(unsigned int);
    void setDataStart(unsigned int);
    void setIndexStart(unsigned int);
    void setFlags(unsigned int);
    void setLocation(plLocation&);
    void setNames(char*, char*);
};

#endif

