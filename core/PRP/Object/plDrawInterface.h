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

#ifndef _PLDRAWINTERFACE_H
#define _PLDRAWINTERFACE_H

#include "plObjInterface.h"

class PLASMA_DLL plDrawInterface : public plObjInterface
{
    CREATABLE(plDrawInterface, kDrawInterface, plObjInterface)

protected:
    std::vector<plKey> fDrawables;
    std::vector<plKey> fRegions;
    std::vector<int> fDrawableKeys;

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    size_t getNumDrawables() const { return fDrawables.size(); }
    plKey getDrawable(size_t idx) const { return fDrawables[idx]; }
    int getDrawableKey(size_t idx) const { return fDrawableKeys[idx]; }
    void clearDrawables();
    void addDrawable(plKey draw, int key);
    void delDrawable(size_t idx);

    const std::vector<plKey>& getRegions() const { return fRegions; }
    std::vector<plKey>& getRegions() { return fRegions; }
    void addRegion(plKey obj) { fRegions.emplace_back(std::move(obj)); }
    void delRegion(size_t idx) { fRegions.erase(fRegions.begin() + idx); }
    void clearRegions() { fRegions.clear(); }
};


class PLASMA_DLL plInstanceDrawInterface : public plDrawInterface
{
    CREATABLE(plInstanceDrawInterface, kInstanceDrawInterface, plDrawInterface)

protected:
    unsigned int fTargetID;
    plKey fDrawable;

public:
    plInstanceDrawInterface() : fTargetID() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;
};

#endif
