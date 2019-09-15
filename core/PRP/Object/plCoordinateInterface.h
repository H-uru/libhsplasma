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

#ifndef _PLCOORDINATEINTERFACE_H
#define _PLCOORDINATEINTERFACE_H

#include "plObjInterface.h"
#include "Math/hsMatrix44.h"

class PLASMA_DLL plCoordinateInterface : public plObjInterface
{
    CREATABLE(plCoordinateInterface, kCoordinateInterface, plObjInterface)

public:
    enum plCoordinateProperties
    {
        kDisable, kCanEverDelayTransform, kDelayedTransformEval, kNumProps
    };

private:
    hsMatrix44 fLocalToParent;
    hsMatrix44 fParentToLocal;
    hsMatrix44 fLocalToWorld;
    hsMatrix44 fWorldToLocal;
    std::vector<plKey> fChildren;
    plKey fParent;

public:
    plCoordinateInterface();

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    const hsMatrix44& getLocalToParent() const { return fLocalToParent; }
    const hsMatrix44& getParentToLocal() const { return fParentToLocal; }
    const hsMatrix44& getLocalToWorld() const { return fLocalToWorld; }
    const hsMatrix44& getWorldToLocal() const { return fWorldToLocal; }

    void setLocalToParent(const hsMatrix44& xform) { fLocalToParent = xform; }
    void setParentToLocal(const hsMatrix44& xform) { fParentToLocal = xform; }
    void setLocalToWorld(const hsMatrix44& xform) { fLocalToWorld = xform; }
    void setWorldToLocal(const hsMatrix44& xform) { fWorldToLocal = xform; }

    const std::vector<plKey>& getChildren() const { return fChildren; }
    std::vector<plKey>& getChildren() { return fChildren; }
    void addChild(plKey child) { fChildren.emplace_back(std::move(child)); }
    void delChild(size_t idx) { fChildren.erase(fChildren.begin() + idx); }
    void clearChildren() { fChildren.clear(); }

    /** Set parent coordinate interface */
    void setParent(plKey parent) { fParent = std::move(parent); }

    /** Get parent coordinate interface */
    plKey getParent() const { return fParent; }
};

#endif
