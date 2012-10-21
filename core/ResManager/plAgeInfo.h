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

#ifndef _PLAGEINFO_H
#define _PLAGEINFO_H

#include "Stream/plEncryptedStream.h"
#include "Util/hsTArray.hpp"
#include "PRP/plPageInfo.h"

/* Loosely based on plAgeDescription */

class PLASMA_DLL plAgeInfo {
public:
    enum CommonPages { kTextures, kGlobal, kNumCommonPages };
    static const plString kCommonPages[kNumCommonPages];

    enum LoadFlags {
        kPreventAutoLoad = 0x1,
        kLoadIfSDLPresent = 0x2,
        kDontLoadMask = (kPreventAutoLoad | kLoadIfSDLPresent),
        kIsLocalOnly = 0x4,
        kIsVolatile = 0x8
    };

    struct PLASMA_DLL PageEntry {
        plString fName;
        int fSeqSuffix;
        unsigned int fLoadFlags;

        PageEntry(const plString& name, int seqSuffix, unsigned int loadFlags)
            : fName(name), fSeqSuffix(seqSuffix), fLoadFlags(loadFlags) { }
        PageEntry() : fSeqSuffix(0), fLoadFlags(0) { }
    };

protected:
    plString fName;
    unsigned int fStartDateTime;
    float fDayLength;
    short fMaxCapacity, fLingerTime;
    int fSeqPrefix;
    unsigned int fReleaseVersion;
    hsTArray<PageEntry> fPages;

public:
    plAgeInfo() : fStartDateTime(0), fDayLength(24.0f), fMaxCapacity(-1),
                  fLingerTime(180), fSeqPrefix(0), fReleaseVersion(0) { }

    void readFromFile(const plString& filename);
    void writeToFile(const plString& filename, PlasmaVer ver);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

public:
    plString getAgeName() const { return fName; }
    unsigned int getStartDateTime() const { return fStartDateTime; }
    float getDayLength() const { return fDayLength; }
    short getMaxCapacity() const { return fMaxCapacity; }
    short getLingerTime() const { return fLingerTime; }
    int getSeqPrefix() const { return fSeqPrefix; }
    unsigned int getReleaseVersion() const { return fReleaseVersion; }

    void setAgeName(const plString& name) { fName = name; }
    void setStartDateTime(unsigned int time) { fStartDateTime = time; }
    void setDayLength(float length) { fDayLength = length; }
    void setMaxCapacity(short maxCap) { fMaxCapacity = maxCap; }
    void setLingerTime(short time) { fLingerTime = time; }
    void setSeqPrefix(int prefix) { fSeqPrefix = prefix; }
    void setReleaseVersion(unsigned int ver) { fReleaseVersion = ver; }

    size_t getNumPages() const { return fPages.getSize(); }
    PageEntry getPage(size_t idx) const { return fPages[idx]; }
    void setPage(size_t idx, const PageEntry& page) { fPages[idx] = page; }
    void addPage(const PageEntry& page) { fPages.append(page); }
    void clearPages() { fPages.clear(); }

    size_t getNumCommonPages(PlasmaVer pv) const;
    PageEntry getCommonPage(size_t idx, PlasmaVer pv) const;

    plString getPageFilename(size_t idx, PlasmaVer pv) const;
    plString getCommonPageFilename(size_t idx, PlasmaVer pv) const;
    plLocation getPageLoc(size_t idx, PlasmaVer pv) const;
    plLocation getCommonPageLoc(size_t idx, PlasmaVer pv) const;
    std::vector<plLocation> getPageLocs(PlasmaVer pv, bool all = false) const;
};

#endif
