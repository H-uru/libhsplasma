#ifndef _PLSCENENODE_H
#define _PLSCENENODE_H

#include "PRP/KeyedObject/hsKeyedObject.h"
#include "PRP/Object/plSceneObject.h"
#include "Util/hsTArray.hpp"

DllClass plSceneNode : public hsKeyedObject {
protected:
    hsTArray<plKey> fSceneObjects;
    hsTArray<plKey> fOtherObjects;

public:
    plSceneNode();
    virtual ~plSceneNode();

    DECLARE_CREATABLE(plSceneNode)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    size_t getNumSceneObjects() const;
    plKey getSceneObject(size_t idx) const;
    void addSceneObject(plKey obj);
    void delSceneObject(size_t idx);
    void clearSceneObjects();

    size_t getNumPoolObjects() const;
    plKey getPoolObject(size_t idx) const;
    void addPoolObject(plKey obj);
    void delPoolObject(size_t idx);
    void clearPoolObjects();

    hsTArray<plKey>& getSceneObjects();
    hsTArray<plKey>& getPoolObjects();
};

#endif
