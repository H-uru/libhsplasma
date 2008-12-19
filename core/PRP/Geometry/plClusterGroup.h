#ifndef _PLCLUSTERGROUP_H
#define _PLCLUSTERGROUP_H

#include "PRP/KeyedObject/hsKeyedObject.h"
#include "PRP/Misc/plRenderLevel.h"
#include "plCluster.h"
#include "plSpanTemplate.h"

DllClass plLODDist {
protected:
    float fMinDist, fMaxDist;

public:
    plLODDist();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

    float getMin() const;
    float getMax() const;
    void setMin(float dist);
    void setMax(float dist);
};

DllClass plClusterGroup : public hsKeyedObject {
protected:
    plSpanTemplate fTemplate;
    plKey fMaterial;
    hsTArray<plCluster*> fClusters;
    hsTArray<plKey> fRegions, fLights;
    plLODDist fLOD;
    plKey fSceneNode, fDrawable;
    unsigned int fRenderLevel;

public:
    plClusterGroup();
    virtual ~plClusterGroup();

    DECLARE_CREATABLE(plClusterGroup)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plLODDist& getLOD();
    plSpanTemplate& getTemplate();

    plKey getMaterial() const;
    plKey getSceneNode() const;
    plKey getDrawable() const;
    unsigned int getRenderLevel() const;

    void setMaterial(plKey mat);
    void setSceneNode(plKey node);
    void setDrawable(plKey draw);
    void setRenderLevel(unsigned int level);

    size_t getNumClusters() const;
    plCluster* getCluster(size_t idx) const;
    void addCluster(plCluster* cluster);
    void delCluster(size_t idx);
    void clearClusters();

    size_t getNumRegions() const;
    plKey getRegion(size_t idx) const;
    void addRegion(plKey region);
    void delRegion(size_t idx);
    void clearRegions();

    size_t getNumLights() const;
    plKey getLight(size_t idx) const;
    void addLight(plKey light);
    void delLight(size_t idx);
    void clearLights();
};

#endif
