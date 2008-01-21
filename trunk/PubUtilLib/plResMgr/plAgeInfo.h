#ifndef _PLAGEINFO_H
#define _PLAGEINFO_H

#include "CoreLib/plEncryptedStream.h"
#include "CoreLib/hsTArray.hpp"
#include "plPageInfo.h"

/* Loosely based on plAgeDescription */

DllClass plAgeInfo {
public:
    enum CommonPages { kTextures, kGlobal, kNumCommonPages };
    
protected:
    plString fName;
    unsigned int fStartDateTime;
    float fDayLength;
    short fMaxCapacity, fLingerTime;
    int fSeqPrefix;
    unsigned int fReleaseVersion;

    hsTArray<plPageInfo*> fPages;

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
    plPageInfo* getPage(size_t idx) const;
    void setPage(size_t idx, plPageInfo* page);
    void addPage(plPageInfo* page);
};

#endif
