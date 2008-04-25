#ifndef _PLCLUSTERGROUP_H
#define _PLCLUSTERGROUP_H

#include "NucleusLib/pnKeyedObject/hsKeyedObject.h"
#include "CoreLib/plRenderLevel.h"
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
};

DllClass plClusterGroup : public hsKeyedObject {
protected:
    plSpanTemplate* fTemplate;
    plKey fMaterial;
    //hsBitVector fVisSet, fVisNot;
    hsTArray<plCluster*> fClusters;
    hsTArray<plKey> fRegions, fLights;
    plLODDist fLOD;
    plKey fSceneNode, fDrawable;
    plRenderLevel fRenderLevel;

public:
    plClusterGroup();
    virtual ~plClusterGroup();

    DECLARE_CREATABLE(plClusterGroup)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);

    plSpanTemplate* getTemplate() const;
};

#endif
