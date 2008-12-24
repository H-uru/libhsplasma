#ifndef _PLOCCLUDER_H
#define _PLOCCLUDER_H

#include "PRP/Object/plObjInterface.h"
#include "PRP/Region/hsBounds.h"
#include "Math/hsMatrix44.h"
#include "plCullPoly.h"

DllClass plOccluder : public plObjInterface {
protected:
    hsTArray<plCullPoly> fPolys;
    hsTArray<plKey> fVisRegions;
    float fPriority;
    hsBounds3Ext fWorldBounds;
    plKey fSceneNode;

public:
    plOccluder();
    virtual ~plOccluder();

    DECLARE_CREATABLE(plOccluder)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    float getPriority() const;
    hsBounds3Ext getWorldBounds() const;
    plKey getSceneNode() const;

    void setPriority(float priority);
    void setWorldBounds(const hsBounds3Ext& bounds);
    void setSceneNode(plKey node);

    size_t getNumPolys() const;
    plCullPoly getPoly(size_t idx) const;
    void addPoly(const plCullPoly& poly);
    void delPoly(size_t idx);
    void clearPolys();
};

DllClass plMobileOccluder : public plOccluder {
protected:
    hsMatrix44 fLocalToWorld, fWorldToLocal;
    hsBounds3Ext fLocalBounds;

public:
    plMobileOccluder();
    virtual ~plMobileOccluder();

    DECLARE_CREATABLE(plMobileOccluder)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    hsMatrix44 getLocalToWorld() const;
    hsMatrix44 getWorldToLocal() const;
    hsBounds3Ext getLocalBounds() const;

    void setLocalToWorld(const hsMatrix44& l2w);
    void setWorldToLocal(const hsMatrix44& w2l);
    void setLocalBounds(const hsBounds3Ext& bounds);
};

#endif
