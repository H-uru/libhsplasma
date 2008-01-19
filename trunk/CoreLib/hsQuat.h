#ifndef _HSQUAT_H
#define _HSQUAT_H

#include "hsGeometry3.h"
#include "FeatureLib/pfPRC/pfPrcHelper.h"

DllClass hsQuat {
protected:
    float fX, fY, fZ, fW;

public:
    hsQuat();
    hsQuat(const hsQuat& init);
    hsQuat(float X, float Y, float Z, float W);
    hsQuat(float rad, const hsVector3& axis);

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
};

#endif
