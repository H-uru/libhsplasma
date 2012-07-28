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
#include "Util/hsTArray.hpp"
#include "Math/hsMatrix44.h"

class PLASMA_DLL plCoordinateInterface : public virtual plObjInterface {
    CREATABLE(plCoordinateInterface, kCoordinateInterface, plObjInterface)


public:
    enum plCoordinateProperties {
        kDisable, kCanEverDelayTransform, kDelayedTransformEval, kNumProps
    };

private:
    hsMatrix44 fLocalToParent;
    hsMatrix44 fParentToLocal;
    hsMatrix44 fLocalToWorld;
    hsMatrix44 fWorldToLocal;
    hsTArray<plKey> fChildren;
    plKey fParent;

    void setParentCallback(hsKeyedObject* ko);

public:
    plCoordinateInterface();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const hsMatrix44& getLocalToParent() const { return fLocalToParent; }
    const hsMatrix44& getParentToLocal() const { return fParentToLocal; }
    const hsMatrix44& getLocalToWorld() const { return fLocalToWorld; }
    const hsMatrix44& getWorldToLocal() const { return fWorldToLocal; }

    void setLocalToParent(const hsMatrix44& xform) { fLocalToParent = xform; }
    void setParentToLocal(const hsMatrix44& xform) { fParentToLocal = xform; }
    void setLocalToWorld(const hsMatrix44& xform) { fLocalToWorld = xform; }
    void setWorldToLocal(const hsMatrix44& xform) { fWorldToLocal = xform; }

    const hsTArray<plKey>& getChildren() const { return fChildren; }
    hsTArray<plKey>& getChildren() { return fChildren; }
    void addChild(plKey child) { fChildren.append(child); }
    void delChild(size_t idx) { fChildren.remove(idx); }
    void clearChildren() { fChildren.clear(); }

    /** Set parent coordinate interface */
    void setParent(plKey parent) { fParent = parent; }

    /** Get parent coordinate interface */
    plKey getParent() const { return fParent; }
};

#endif
