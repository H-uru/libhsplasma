#ifndef _PLSCENENODE_H
#define _PLSCENENODE_H

#include "PRP/KeyedObject/hsKeyedObject.h"
#include "PRP/Object/plSceneObject.h"
#include "Util/hsTArray.hpp"

DllClass plSceneNode : public hsKeyedObject {
protected:
    bool filterGenerics;
    short depth;

public:
    hsTArray<plKey> fSceneObjects;
    hsTArray<plKey> fOtherObjects;

public:
    plSceneNode();
    virtual ~plSceneNode();

    DECLARE_CREATABLE(plSceneNode)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

};

#endif
