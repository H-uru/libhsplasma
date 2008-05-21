#ifndef _PLPAGEINFO_H
#define _PLPAGEINFO_H

#include <vector>
#include "CoreLib/hsStream.h"
#include "NucleusLib/pnKeyedObject/plUoid.h"
#include "FeatureLib/pfPRC/pfPrcHelper.h"

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

    enum LoadFlags {
        kPreventAutoLoad = 0x1,
        kLoadIfSDLPresent = 0x2,
        kIsLocalOnly = 0x4,
        kIsVolatile = 0x8
    };

protected:
    plLocation fLocation;
    plString fAge, fPage;
    unsigned int fIdxChecksum, fChecksum;
    int fReleaseVersion;
    unsigned int fDataStart, fIdxStart, fFlags;

    unsigned int fNumObjects;
    unsigned char fLoadFlags;
    std::vector<short> fClassList;

    static const plString kDistrict;

public:
    plPageInfo();
    plPageInfo(const plString& age, const plString& page);
    ~plPageInfo();

    bool isValid() const;

    void read(hsStream* S);
    void write(hsStream* S);
    void writeSums(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

    plString getFilename(PlasmaVer ver) const;
    const plString& getAge() const;
    const plString& getChapter() const;
    const plString& getPage() const;
    unsigned int getChecksum() const;
    unsigned int getDataStart() const;
    unsigned int getIndexStart() const;
    unsigned int getFlags() const;
    plLocation& getLocation();
    unsigned char getLoadFlags() const;
    unsigned int getNumObjects() const;

    void setChecksum(unsigned int);
    void setReleaseVersion(unsigned int);
    void setDataStart(unsigned int);
    void setIndexStart(unsigned int);
    void setFlags(unsigned int);
    void setLocation(const plLocation&);
    void setNames(const plString& age, const plString& page);
    void setLoadFlags(unsigned char);
    void setNumObjects(unsigned int);

    void clearClassList();
    void addClass(short classIdx);
    void setClassList(std::vector<short>& list);

protected:
    void IInit();
};

#endif

