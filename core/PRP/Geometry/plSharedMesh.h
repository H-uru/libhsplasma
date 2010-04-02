#ifndef PLSHAREDMESH_H
#define PLSHAREDMESH_H

#include "PRP/KeyedObject/hsKeyedObject.h"
#include "PRP/Object/plSceneObject.h"
#include "Util/hsTArray.hpp"
#include "plGeometrySpan.h"

DllClass plSharedMesh : public hsKeyedObject {
    CREATABLE(plSharedMesh, kSharedMesh, hsKeyedObject)

public:
    enum {
        kDontSaveMorphState = 0x1,
        kLayer0GlobalToMod = 0x2
    };

public:
    hsTArray<plGeometrySpan*> fSpans;
    plKey fMorphSet;
    unsigned char fFlags;

public:
    plSharedMesh();
    virtual ~plSharedMesh();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plKey getMorphSet() const { return fMorphSet; }
    unsigned char getFlags() const { return fFlags; }

    void setMorphSet(plKey set) { fMorphSet = set; }
    void setFlags(unsigned char flags) { fFlags = flags; }

    const hsTArray<plGeometrySpan*>& getSpans() const { return fSpans; }
    hsTArray<plGeometrySpan*>& getSpans() { return fSpans; }
    void addSpan(plGeometrySpan* span) { fSpans.append(span); }
    void delSpan(size_t idx);
    void clearSpans();
};

#endif
