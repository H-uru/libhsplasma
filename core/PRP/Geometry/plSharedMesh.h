#ifndef PLSHAREDMESH_H
#define PLSHAREDMESH_H

#include "PRP/KeyedObject/hsKeyedObject.h"
#include "PRP/Object/plSceneObject.h"
#include "Util/hsTArray.hpp"
#include "plGeometrySpan.h"

DllClass plSharedMesh : public hsKeyedObject {
public:
    enum {
        kDontSaveMorphState = 0x1,
        kLayer0GlobalToMod = 0x2
    };

public:
    hsTArray<plGeometrySpan*> fSpans;
    hsTArray<plSceneObject const*> fActiveInstances;
    plKey fMorphSet;
    unsigned char fFlags;

public:
    plSharedMesh();
    virtual ~plSharedMesh();

    DECLARE_CREATABLE(plSharedMesh)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    size_t getNumSpans() const;
    plGeometrySpan* getSpan(size_t idx) const;
};

#endif
