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

#ifndef _HSSUMFILE_H
#define _HSSUMFILE_H

#include <string_theory/string>

#include "Util/plMD5.h"

class PLASMA_DLL hsSumFile
{
public:
    enum UpdateResult
    {
        kNotNeeded = 0,
        kUpdated = 1,
        kAdded = 2,
    };

    struct FileInfo
    {
        ST::string fPath;
        plMD5Hash fHash;
        uint32_t fTimestamp;
        uint32_t fUnknown;

        FileInfo() : fTimestamp(), fUnknown() { }
        FileInfo(const ST::string& path, const plMD5Hash& hash, uint32_t timestamp)
            : fPath(path), fHash(hash), fTimestamp(timestamp), fUnknown() { }

        bool isValid() const { return !fPath.empty(); }
    };

    hsSumFile() : fUnknown() { }

    void read(hsStream* S);
    void write(hsStream* S) const;

    uint32_t getUnknown() const { return fUnknown; }
    std::vector<FileInfo>& getFiles() { return fFiles; }
    const std::vector<FileInfo>& getFiles() const { return fFiles; }

    void setUnknown(uint32_t value) { fUnknown = value; }

    FileInfo findFile(const ST::string& sumPath) const;
    UpdateResult updateFile(const ST::string& sumPath, hsStream* source,
                            uint32_t modTime);
    void removeFile(const ST::string& sumPath);

private:
    uint32_t fUnknown;
    std::vector<FileInfo> fFiles;
};

#endif // _HSSUMFILE_H
