#include "plPhysical.h"
#include "plHKPhysical.h"
#include "plPXPhysical.h"
#include "plODEPhysical.h"

const char* plSimDefs::BoundsNames[] = {
    "(Invalid)", "kBoxBounds", "kSphereBounds", "kHullBounds",
    "kProxyBounds", "kExplicitBounds", "kCylinderBounds"
};

const char* plSimDefs::GroupNames[] = {
    "kGroupStatic", "kGroupAvatarBlocker", "kGroupDynamicBlocker",
    "kGroupAvatar", "kGroupDynamic", "kGroupDetector", "kGroupLOSOnly"
};

IMPLEMENT_CREATABLE(plPhysical, kPhysical, plSynchedObject)
