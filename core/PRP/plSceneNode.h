#ifndef _PLSCENENODE_H
#define _PLSCENENODE_H

#include "PRP/KeyedObject/hsKeyedObject.h"
#include "PRP/Object/plSceneObject.h"
#include "Util/hsTArray.hpp"

DllClass plSceneNode : public hsKeyedObject {
    CREATABLE(plSceneNode, kSceneNode, hsKeyedObject)

protected:
    hsTArray<plKey> fSceneObjects;
    hsTArray<plKey> fPoolObjects;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const hsTArray<plKey>& getSceneObjects() const { return fSceneObjects; }
    hsTArray<plKey>& getSceneObjects() { return fSceneObjects; }
    void addSceneObject(plKey obj) { fSceneObjects.append(obj); }
    void delSceneObject(size_t idx) { fSceneObjects.remove(idx); }
    void clearSceneObjects() { fSceneObjects.clear(); }

    const hsTArray<plKey>& getPoolObjects() const { return fPoolObjects; }
    hsTArray<plKey>& getPoolObjects() { return fPoolObjects; }
    void addPoolObject(plKey obj) { fPoolObjects.append(obj); }
    void delPoolObject(size_t idx) { fPoolObjects.remove(idx); }
    void clearPoolObjects() { fPoolObjects.clear(); }
};

#endif
