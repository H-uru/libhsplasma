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

class PLASMA_DLL plExcludeRegionModifier : public virtual plSingleModifier {
    CREATABLE(plExcludeRegionModifier, kExcludeRegionModifier, plSingleModifier)

public:
    enum { kBlockCameras };

protected:
    std::vector<plKey> fSafePoints;
    bool fSeek;
    float fSeekTime;

public:
    plExcludeRegionModifier() : fSeek(false), fSeekTime(0.0f) {
        fFlags.setName(kBlockCameras, "kBlockCameras");
    }

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    std::vector<plKey>& getSafePoints() { return fSafePoints; }
    const std::vector<plKey>& getSafePoints() const { return fSafePoints; }
    void addSafePoint(plKey key) { fSafePoints.push_back(key); }
    void clearSafePoints() { fSafePoints.clear(); }
    void delSafePoint(size_t idx) { fSafePoints.erase(fSafePoints.begin() + idx); }

    bool getSeek() const { return fSeek; }
    float getSeekTime() const { return fSeekTime; }

    void setSeek(bool value) { fSeek = value; }
    void setSeekTime(float value) { fSeekTime = value; }
};

#endif
