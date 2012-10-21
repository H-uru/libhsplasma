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

#ifndef _PLOCCLUDER_H
#define _PLOCCLUDER_H

#include "PRP/Object/plObjInterface.h"
#include "PRP/Region/hsBounds.h"
#include "Math/hsMatrix44.h"
#include "plCullPoly.h"

class PLASMA_DLL plOccluder : public virtual plObjInterface {
    CREATABLE(plOccluder, kOccluder, plObjInterface)

protected:
    hsTArray<plCullPoly> fPolys;
    hsTArray<plKey> fVisRegions;
    float fPriority;
    hsBounds3Ext fWorldBounds;
    plKey fSceneNode;

public:
    plOccluder() : fPriority(0.0f) { }

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    float getPriority() const { return fPriority; }
    hsBounds3Ext getWorldBounds() const { return fWorldBounds; }
    plKey getSceneNode() const { return fSceneNode; }

    void setPriority(float priority) { fPriority = priority; }
    void setWorldBounds(const hsBounds3Ext& bounds) { fWorldBounds = bounds; }
    void setSceneNode(plKey node) { fSceneNode = node; }

    const hsTArray<plCullPoly>& getPolys() const { return fPolys; }
    hsTArray<plCullPoly>& getPolys() { return fPolys; }
    void addPoly(const plCullPoly& poly) { fPolys.append(poly); }
    void delPoly(size_t idx) { fPolys.remove(idx); }
    void clearPolys() { fPolys.clear(); }

    const hsTArray<plKey>& getVisRegions() const { return fVisRegions; }
    hsTArray<plKey>& getVisRegions() { return fVisRegions; }
    void addVisRegion(plKey region) { fVisRegions.append(region); }
    void delVisRegion(size_t idx) { fVisRegions.remove(idx); }
    void clearVisRegions() { fVisRegions.clear(); }
};


class PLASMA_DLL plMobileOccluder : public virtual plOccluder {
    CREATABLE(plMobileOccluder, kMobileOccluder, plOccluder)

protected:
    hsMatrix44 fLocalToWorld, fWorldToLocal;
    hsBounds3Ext fLocalBounds;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    hsMatrix44 getLocalToWorld() const { return fLocalToWorld; }
    hsMatrix44 getWorldToLocal() const { return fWorldToLocal; }
    hsBounds3Ext getLocalBounds() const { return fLocalBounds; }

    void setLocalToWorld(const hsMatrix44& l2w) { fLocalToWorld = l2w; }
    void setWorldToLocal(const hsMatrix44& w2l) { fWorldToLocal = w2l; }
    void setLocalBounds(const hsBounds3Ext& bounds) { fLocalBounds = bounds; }
};

#endif
