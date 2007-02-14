#ifndef _PLSCENENODE_H
#define _PLSCENENODE_H

#include "../../NucleusLib/pnKeyedObject/hsKeyedObject.h"
#include "../../NucleusLib/pnSceneObject/plSceneObject.h"
#include "../../CoreLib/hsTArray.hpp"
#ifdef Tahg
  #include "../../CoreLib/hsmalloc.h"
  #include "../../NucleusLib/inc/plDrawable.h"
  #include "../../NucleusLib/inc/plgDispatch.h"
  #include "../../NucleusLib/pnMessage/plNodeRefMsg.h"
  #include "../plDrawable/plSpaceTree.h"
  #include "../plDrawable/plSpaceTreeMaker.h"
  #include "../plMessage/plNodeCleanupMsg.h"
  #include "plOccluder.h"
  #include "plPageTreeMgr.h"
#endif

class plSceneNode : public hsKeyedObject {
protected:
    bool filterGenerics;
    short depth;

public:
    hsTArray<plKey*> SceneObjects;
    hsTArray<plKey*> OtherObjects;
    //class hsTArray<plDrawable *> drawPool;
    //class hsTArray<plPhysical *> simulationPool;
    //class hsTArray<plAudible *> audioPool;
    //class hsTArray<plOccluder *> occluders;
    //class hsTArray<plLightInfo *> lightPool;
    //class plSpaceTree * spaceTree;

public:
    plSceneNode(PlasmaVer pv = pvUnknown);
    virtual ~plSceneNode();

    virtual short ClassIndex();

    virtual void read(hsStream *S);
    virtual void write(hsStream *S);

#ifdef Tahg
public:
    static class plSceneNode * Create();
    static const class plSceneNode * ConvertNoRef(const class plCreatable *);
    static class plSceneNode * ConvertNoRef(class plCreatable *);
    static class plSceneNode * Convert(class plCreatable *);
    static bool HasDerivedClass(unsigned short);
    static bool HasBaseClass(unsigned short);
    class plCreatable * GetInterface(unsigned short);
    const class plCreatable * GetConstInterface(unsigned short);
//  void Harvest(class plVolumeIsect *, class hsTArray<plDrawVisList> &);
//  void CollectForRender(class plPipeline *, class hsTArray<plDrawVisList> &, class plVisMgr *);
    void SubmitOccluders(class plPageTreeMgr *);
    short GetDepth();
    short IncDepth();
    short DecDepth();
    void Init();
    class plSpaceTree * GetSpaceTree();
    class plDrawable * GetMatchingDrawable(const class plDrawableCriteria &);
    void OptimizeDrawables();
    void SetFilterGenericsOnly(int);
    const class hsTArray<plDrawable *> & plSceneNode::GetDrawPool();

protected:
    void IDirtySpaceTree();
    class plSpaceTree * ITrashSpaceTree();
    class plSpaceTree * IBuildSpaceTree();
    void IRemoveDrawable(class plDrawable *);
    void IRemoveAudible(class plAudible *);
    void IRemovePhysical(class plPhysical *);
    void IRemoveObject(class plSceneObject *);
    void IRemoveLight(class plLightInfo *);
    void IRemoveOccluder(class plOccluder *);
    void IRemoveGeneric(class hsKeyedObject *);
    void ISetObject(class plSceneObject *);
    void ISetPhysical(class plPhysical *);
    void ISetAudible(class plAudible *);
    void ISetDrawable(class plDrawable *);
    void ISetLight(class plLightInfo *);
    void ISetOccluder(class plOccluder *);
    void ISetGeneric(class hsKeyedObject *);
    int IOnRemove(class plNodeRefMsg *);
    int IOnAdd(class plNodeRefMsg *);
    void ICleanUp();
#endif
};

#endif

