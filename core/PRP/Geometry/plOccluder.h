#ifndef _PLOCCLUDER_H
#define _PLOCCLUDER_H

#include "PRP/Object/plObjInterface.h"
#include "PRP/Region/hsBounds.h"
#include "Math/hsMatrix44.h"
#include "plCullPoly.h"

DllClass plOccluder : public plObjInterface {
    CREATABLE(plOccluder, kOccluder, plObjInterface)

protected:
    hsTArray<plCullPoly> fPolys;
    hsTArray<plKey> fVisRegions;
    float fPriority;
    hsBounds3Ext fWorldBounds;
    plKey fSceneNode;

public:
    plOccluder();

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


DllClass plMobileOccluder : public plOccluder {
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
