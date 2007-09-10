#ifndef _PLPAGEINFO_H
#define _PLPAGEINFO_H

#include <vector>
#include "../../CoreLib/hsStream.h"
#include "../../NucleusLib/pnKeyedObject/plUoid.h"
#include "../../FeatureLib/pfPRC/pfPrcHelper.h"

DllClass plPageInfo {
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
    plString age, page;
    unsigned int idxChecksum, checksum;
    int releaseVersion;
    unsigned int dataStart, idxStart, flags;

    std::vector<short> classList;

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
    void prcWrite(pfPrcHelper* prc);

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
    void setNames(const char*, const char*);

    void clearClassList();
    void addClass(short classIdx);
    void setClassList(std::vector<short>& list);
};

#endif

