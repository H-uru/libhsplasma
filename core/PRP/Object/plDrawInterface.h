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

class PLASMA_DLL plDrawInterface : public virtual plObjInterface {
    CREATABLE(plDrawInterface, kDrawInterface, plObjInterface)

protected:
    std::vector<plKey> fDrawables;
    std::vector<plKey> fRegions;
    std::vector<int> fDrawableKeys;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    size_t getNumDrawables() const { return fDrawables.size(); }
    plKey getDrawable(size_t idx) const { return fDrawables[idx]; }
    int getDrawableKey(size_t idx) const { return fDrawableKeys[idx]; }
    void clearDrawables();
    void addDrawable(plKey draw, int key);
    void delDrawable(size_t idx);

    const std::vector<plKey>& getRegions() const { return fRegions; }
    std::vector<plKey>& getRegions() { return fRegions; }
    void addRegion(plKey obj) { fRegions.push_back(obj); }
    void delRegion(size_t idx) { fRegions.erase(fRegions.begin() + idx); }
    void clearRegions() { fRegions.clear(); }
};


class PLASMA_DLL plInstanceDrawInterface : public virtual plDrawInterface {
    CREATABLE(plInstanceDrawInterface, kInstanceDrawInterface, plDrawInterface)

protected:
    unsigned int fTargetID;
    plKey fDrawable;

public:
    plInstanceDrawInterface() : fTargetID(0) { }

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
