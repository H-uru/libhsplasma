#ifndef _HSQUAT_H
#define _HSQUAT_H

#include "hsGeometry3.h"

DllStruct hsQuat {
    float X, Y, Z, W;

    hsQuat();
    hsQuat(const hsQuat& init);
    hsQuat(float x, float y, float z, float w);
    hsQuat(float rad, const hsVector3& axis);

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);
};

#endif
