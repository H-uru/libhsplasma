#ifndef _PLPAGEINFO_H
#define _PLPAGEINFO_H

#include <vector>
#include "PRP/KeyedObject/plLocation.h"
#include "Stream/pfPrcHelper.h"

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
    plLocation fLocation;
    plString fAge, fPage;
    unsigned int fIdxChecksum, fChecksum;
    int fReleaseVersion;
    unsigned int fDataStart, fIdxStart, fFlags;

    unsigned int fNumObjects;
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
    unsigned int getReleaseVersion() const;
    unsigned int getDataStart() const;
    unsigned int getIndexStart() const;
    unsigned int getFlags() const;
    const plLocation& getLocation() const;
    unsigned int getNumObjects() const;

    void setAge(const plString&);
    void setPage(const plString&);
    void setChecksum(unsigned int);
    void setReleaseVersion(unsigned int);
    void setDataStart(unsigned int);
    void setIndexStart(unsigned int);
    void setFlags(unsigned int);
    void setLocation(const plLocation&);
    void setNumObjects(unsigned int);

    void clearClassList();
    void addClass(short classIdx);
    void setClassList(std::vector<short>& list);

protected:
    void IInit();
};

#endif
