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
    size_t getNumPoolObjects() const;
    plKey getSceneObject(size_t idx) const;
    plKey getPoolObject(size_t idx) const;
    hsTArray<plKey>& getSceneObjects();
    hsTArray<plKey>& getPoolObjects();
};

#endif
