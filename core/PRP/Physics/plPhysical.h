#ifndef _PLPHYSICAL_H
#define _PLPHYSICAL_H

#include "PRP/Object/plSynchedObject.h"

DllClass plSimDefs {
public:
    enum Bounds {
        kBoxBounds = 1, kSphereBounds, kHullBounds, kProxyBounds,
        kExplicitBounds, kCylinderBounds, kNumBounds, kBoundsMax = 0xFF
    };

    enum Group {
        kGroupStatic, kGroupAvatarBlocker, kGroupDynamicBlocker, kGroupAvatar,
        kGroupDynamic, kGroupDetector, kGroupLOSOnly, kGroupMax
    };

    enum LOSDB {
        kLOSDBNone = 0,
        kLOSDBUIBlockers = 0x1,
        kLOSDBUIItems = 0x2,
        kLOSDBCameraBlockers = 0x4,
        kLOSDBCustom = 0x8,
        kLOSDBLocalAvatar = 0x10,
        kLOSDBShootableItems = 0x20,
        kLOSDBAvatarWalkable = 0x40,
        kLOSDBSwimRegion = 0x80,
        kLOSDBMax = 0x100,
        kLOSDBForce16 = 0xFFFF
    };

    enum LOSReqType {
        kLOS_IgnoreCameraRequest = 0x1,
        kLOS_IgnoreUIRequest = 0x2,
        kLOS_CameraAvoidObject = 0x4,
        kLOS_Max = 0xFFFF
    };

    static const char* BoundsNames[];
    static const char* GroupNames[];
};

DllClass plPhysical : public plSynchedObject {
public:
    DECLARE_CREATABLE(plPhysical)

    virtual class plHKPhysical* ConvertToHavok() const =0;
    virtual class plPXPhysical* ConvertToPhysX() const =0;
    virtual class plODEPhysical* ConvertToODE() const =0;

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void readData(hsStream* S, plResManager* mgr) =0;
    virtual void writeData(hsStream* S, plResManager* mgr) =0;
};

#endif
