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

    enum plCoordinateTransformPhases {
        kTransformPhaseNormal, kTransformPhaseDelayed
    };

    enum {
        kTransformDirty = 0x1,
        kWarp = 0x2,
        kMaxState = 0xFFFFFFFF
    };

    enum plAttachFlags {
        kMaintainWorldPosition = 0x1,
        kMaintainSceneNode = 0x2,
        kAboutToAttach = 0x4
    };

    enum Reason {
        kReasonUnknown = 0x1,
        kReasonPhysics = 0x2,
        kMaxReasons = 0xFFFFFFFF
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
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
