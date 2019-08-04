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

#ifndef _PLPAGEINFO_H
#define _PLPAGEINFO_H

#include <vector>
#include "PRP/KeyedObject/plLocation.h"
#include "Stream/pfPrcHelper.h"

class PLASMA_DLL plPageInfo
{
public:
    enum Flags
    {
        kPartialPatchFile = 0x1,
        kOldDataChecksum = 0x2,
        kOldIdxChecksum = 0x4,
        kBasicChecksum = 0x8,
        kPatchHeaderOnly = 0x10,
        kChecksumMask = kBasicChecksum | kOldIdxChecksum | kOldDataChecksum,
        kPatchFlags = kPatchHeaderOnly | kPartialPatchFile
    };

private:
    plLocation fLocation;
    ST::string fAge, fPage;
    unsigned int fIdxChecksum, fChecksum;
    int fReleaseVersion;
    unsigned int fDataStart, fIdxStart, fFlags;

    unsigned int fNumObjects;
    std::vector<short> fClassList;

public:
    plPageInfo() { IInit(); }
    plPageInfo(const ST::string& age, const ST::string& page);

    bool isValid() const { return fLocation.isValid(); }

    void read(hsStream* S);
    void write(hsStream* S);
    void writeSums(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

public:
    ST::string getFilename(PlasmaVer ver) const;
    ST::string getAge() const { return fAge; }
    ST::string getChapter() const { return "District"; }
    ST::string getPage() const { return fPage; }
    unsigned int getChecksum() const { return fChecksum; }
    unsigned int getReleaseVersion() const { return fReleaseVersion; }
    unsigned int getDataStart() const { return fDataStart; }
    unsigned int getIndexStart() const { return fIdxStart; }
    unsigned int getFlags() const { return fFlags; }
    const plLocation& getLocation() const { return fLocation; }
    unsigned int getNumObjects() const { return fNumObjects; }

    void setAge(const ST::string& age) { fAge = age; }
    void setPage(const ST::string& page) { fPage = page; }
    void setChecksum(unsigned int sum) { fChecksum = sum; }
    void setReleaseVersion(unsigned int relVer) { fReleaseVersion = relVer; }
    void setDataStart(unsigned int loc) { fDataStart = loc; }
    void setIndexStart(unsigned int loc) { fIdxStart = loc; }
    void setFlags(unsigned int flags) { fFlags = flags; }
    void setLocation(const plLocation& loc) { fLocation = loc; }
    void setNumObjects(unsigned int nObjects) { fNumObjects = nObjects; }

    void clearClassList() { fClassList.clear(); }
    void addClass(short classIdx) { fClassList.push_back(classIdx); }
    void setClassList(std::vector<short>& list) { fClassList = list; }

protected:
    void IInit();
};

#endif
