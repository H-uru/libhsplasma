#ifndef _PLCOORDINATEINTERFACE_H
#define _PLCOORDINATEINTERFACE_H

#include "plObjInterface.h"
#include "Util/hsTArray.hpp"
#include "Math/hsMatrix44.h"

DllClass plCoordinateInterface : public plObjInterface {
    CREATABLE(plCoordinateInterface, kCoordinateInterface, plObjInterface)

public:
    enum plCoordinateProperties {
        kDisable, kCanEverDelayTransform, kDelayedTransformEval, kNumProps
    };

public:
    hsMatrix44 fLocalToParent;
    hsMatrix44 fParentToLocal;
    hsMatrix44 fLocalToWorld;
    hsMatrix44 fWorldToLocal;
    hsTArray<plKey> fChildren;

public:
    plCoordinateInterface();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const hsMatrix44& getLocalToParent() const { return fLocalToParent; }
    const hsMatrix44& getParentToLocal() const { return fParentToLocal; }
    const hsMatrix44& getLocalToWorld() const { return fLocalToWorld; }
    const hsMatrix44& getWorldToLocal() const { return fWorldToLocal; }

    void setLocalToParent(const hsMatrix44& xform) { fLocalToParent = xform; }
    void setParentToLocal(const hsMatrix44& xform) { fParentToLocal = xform; }
    void setLocalToWorld(const hsMatrix44& xform) { fLocalToWorld = xform; }
    void setWorldToLocal(const hsMatrix44& xform) { fWorldToLocal = xform; }

    const hsTArray<plKey>& getChildren() const { return fChildren; }
    hsTArray<plKey>& getChildren() { return fChildren; }
    void addChild(plKey child) { fChildren.append(child); }
    void delChild(size_t idx) { fChildren.remove(idx); }
    void clearChildren() { fChildren.clear(); }
};

#endif
