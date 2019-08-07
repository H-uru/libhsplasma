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

#ifndef _PLEXCLUDEREGIONMODIFIER_H
#define _PLEXCLUDEREGIONMODIFIER_H

#include "plModifier.h"

class PLASMA_DLL plExcludeRegionModifier : public plSingleModifier
{
    CREATABLE(plExcludeRegionModifier, kExcludeRegionModifier, plSingleModifier)

public:
    enum { kBlockCameras };

protected:
    std::vector<plKey> fSafePoints;
    bool fSeek;
    float fSeekTime;

public:
    plExcludeRegionModifier() : fSeek(), fSeekTime()
    {
        fFlags.setName(kBlockCameras, "kBlockCameras");
    }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    std::vector<plKey>& getSafePoints() { return fSafePoints; }
    const std::vector<plKey>& getSafePoints() const { return fSafePoints; }
    void addSafePoint(plKey key) { fSafePoints.emplace_back(std::move(key)); }
    void clearSafePoints() { fSafePoints.clear(); }
    void delSafePoint(size_t idx) { fSafePoints.erase(fSafePoints.begin() + idx); }

    bool getSeek() const { return fSeek; }
    float getSeekTime() const { return fSeekTime; }

    void setSeek(bool value) { fSeek = value; }
    void setSeekTime(float value) { fSeekTime = value; }
};

#endif
