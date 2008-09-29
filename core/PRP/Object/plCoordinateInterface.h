#ifndef _PLCOORDINATEINTERFACE_H
#define _PLCOORDINATEINTERFACE_H

#include "plObjInterface.h"
#include "Util/hsTArray.hpp"
#include "Math/hsMatrix44.h"

DllClass plCoordinateInterface : public plObjInterface {
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
    virtual ~plCoordinateInterface();

    DECLARE_CREATABLE(plCoordinateInterface)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    hsMatrix44& getLocalToParent();
    hsMatrix44& getParentToLocal();
    hsMatrix44& getLocalToWorld();
    hsMatrix44& getWorldToLocal();

    size_t getNumChildren() const;
    plKey getChild(size_t idx) const;
    void clearChildren();
    void addChild(plKey child);
};

#endif
