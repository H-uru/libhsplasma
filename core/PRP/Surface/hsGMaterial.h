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

#ifndef _HSGMATERIAL_H
#define _HSGMATERIAL_H

#include "PRP/Object/plSynchedObject.h"

class PLASMA_DLL hsGMaterial : public plSynchedObject
{
    CREATABLE(hsGMaterial, kGMaterial, plSynchedObject)

public:
    enum hsGCompFlags
    {
        kCompShaded = 0x1,
        kCompEnvironMap = 0x2,
        kCompProjectOnto = 0x4,
        kCompSoftShadow = 0x8,
        kCompSpecular = 0x10,
        kCompTwoSided = 0x20,
        kCompDrawAsSplats = 0x40,
        kCompAdjusted = 0x80,
        kCompNoSoftShadow = 0x100,
        kCompDynamic = 0x200,
        kCompDecal = 0x400,
        kCompIsEmissive = 0x800,    // OBSOLETE
        kCompIsLightMapped = 0x1000,
        kCompNeedsBlendChannel = 0x2000
    };

private:
    std::vector<plKey> fLayers, fPiggyBacks;
    unsigned int fCompFlags, fLoadFlags;

public:
    hsGMaterial() : fCompFlags(), fLoadFlags() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    const std::vector<plKey>& getLayers() const { return fLayers; }
    std::vector<plKey>& getLayers() { return fLayers; }
    void addLayer(plKey layer) { fLayers.emplace_back(std::move(layer)); }
    void delLayer(size_t idx) { fLayers.erase(fLayers.begin() + idx); }
    void clearLayers() { fLayers.clear(); }

    const std::vector<plKey>& getPiggyBacks() const { return fPiggyBacks; }
    std::vector<plKey>& getPiggyBacks() { return fPiggyBacks; }
    void addPiggyBack(plKey layer) { fPiggyBacks.emplace_back(std::move(layer)); }
    void delPiggyBack(size_t idx) { fPiggyBacks.erase(fPiggyBacks.begin() + idx); }
    void clearPiggyBacks() { fPiggyBacks.clear(); }

    unsigned int getCompFlags() const { return fCompFlags; }
    unsigned int getLoadFlags() const { return fLoadFlags; }
    void setCompFlags(unsigned int flags) { fCompFlags = flags; }
    void setLoadFlags(unsigned int flags) { fLoadFlags = flags; }
};

#endif
