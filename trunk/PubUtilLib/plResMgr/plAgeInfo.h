#ifndef _PLAGEINFO_H
#define _PLAGEINFO_H

#include "CoreLib/plEncryptedStream.h"
#include "CoreLib/hsTArray.hpp"
#include "plPageInfo.h"

/* Loosely based on plAgeDescription */

DllClass plAgeInfo {
public:
    enum CommonPages { kTextures, kGlobal, kNumCommonPages };

    DllStruct PageEntry {
        plString fName;
        int fSeqSuffix;
        unsigned int fLoadFlags;

        PageEntry(const plString& name, int seqSuffix, unsigned int loadFlags);
        PageEntry();
    };
    
protected:
    plString fName;
    unsigned int fStartDateTime;
    float fDayLength;
    short fMaxCapacity, fLingerTime;
    int fSeqPrefix;
    unsigned int fReleaseVersion;
    hsTArray<PageEntry> fPages;

    static const plString kCommonPages[kNumCommonPages];

public:
    plAgeInfo();
    ~plAgeInfo();

    void readFromFile(const plString& filename);
    void writeToPath(const plString& path, PlasmaVer ver);

    const plString& getAgeName() const;
    unsigned int getStartDateTime() const;
    float getDayLength() const;
    short getMaxCapacity() const;
    short getLingerTime() const;
    int getSeqPrefix() const;
    unsigned int getReleaseVersion() const;

    void setAgeName(const plString&);
    void setStartDateTime(unsigned int);
    void setDayLength(float);
    void setMaxCapacity(short);
    void setLingerTime(short);
    void setSeqPrefix(int);
    void setReleaseVersion(unsigned int);

    size_t getNumPages() const;
    PageEntry getPage(size_t idx) const;
    void setPage(size_t idx, const PageEntry& page);
    void addPage(const PageEntry& page);

    plString getPageFileName(size_t idx, PlasmaVer pv) const;
    plLocation getPageLocation(size_t idx) const;
};

#endif
