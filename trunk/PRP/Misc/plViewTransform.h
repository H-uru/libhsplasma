#ifndef _PLVIEWTRANSFORM_H
#define _PLVIEWTRANSFORM_H

#include "Math/hsMatrix44.h"
#include "Math/hsGeometry3.h"

DllClass plViewTransform {
public:
    enum {
        kNone = 0,
        kOrthogonal = 0x1,
        kSymmetric = 0x2,
        kCameraToNDCSet = 0x4,
        kWorldToNDCSet = 0x8,
        kSetMask = kCameraToNDCSet | kWorldToNDCSet,
        kViewPortRelative = 0x10
    };

protected:
    unsigned int fFlags;
    hsMatrix44 fCameraToWorld, fWorldToCamera;
    hsVector3 fMin, fMax;
    unsigned short fWidth, fHeight;
    hsVector3 fViewPortX, fViewPortY;
    hsVector3 fMapMin, fMapMax;
    hsMatrix44 fCameraToNDC, fWorldToNDC;
};

#endif
