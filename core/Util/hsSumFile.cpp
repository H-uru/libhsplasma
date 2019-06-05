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

#include "hsSumFile.h"
#include "Debug/plDebug.h"

#include <algorithm>

void hsSumFile::read(hsStream* S)
{
    fFiles.resize(S->readInt());
    fUnknown = S->readInt();
    for (size_t i = 0; i < fFiles.size(); ++i) {
        fFiles[i].fPath = S->readSafeStr();
        fFiles[i].fHash.read(S);
        fFiles[i].fTimestamp = S->readInt();
        fFiles[i].fUnknown = S->readInt();
    }
}

void hsSumFile::write(hsStream* S) const
{
    S->writeInt(fFiles.size());
    S->writeInt(fUnknown);
    for (const FileInfo& file : fFiles) {
        S->writeSafeStr(file.fPath);
        file.fHash.write(S);
        S->writeInt(file.fTimestamp);
        S->writeInt(file.fUnknown);
    }
}

hsSumFile::FileInfo hsSumFile::findFile(const ST::string &sumPath) const
{
    auto fit = std::find_if(fFiles.begin(), fFiles.end(),
                            [sumPath](const FileInfo& info) {
        return info.fPath == sumPath;
    });
    return (fit == fFiles.end()) ? FileInfo() : *fit;
}

hsSumFile::UpdateResult hsSumFile::updateFile(const ST::string& sumPath,
                                              hsStream* source, uint32_t modTime)
{
    plMD5Hash hash = plMD5::hashStream(source);

    auto fit = std::find_if(fFiles.begin(), fFiles.end(),
                            [sumPath](const FileInfo& info) {
        return info.fPath == sumPath;
    });
    if (fit == fFiles.end()) {
        fFiles.emplace_back(sumPath, hash, modTime);
        return kAdded;
    } else {
        UpdateResult result = (hash == fit->fHash) ? kNotNeeded : kUpdated;
        fit->fTimestamp = modTime;
        fit->fHash = hash;
        return result;
    }
}

void hsSumFile::removeFile(const ST::string& sumPath)
{
    auto fit = std::find_if(fFiles.begin(), fFiles.end(),
                            [sumPath](const FileInfo& info) {
        return info.fPath == sumPath;
    });
    if (fit == fFiles.end())
        plDebug::Warning("Attempted to remove non-existent file {}", sumPath);
    else
        fFiles.erase(fit);
}
