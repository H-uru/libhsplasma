#ifndef _HSQUAT_H
#define _HSQUAT_H

#include "hsGeometry3.h"

DllStruct hsQuat {
    float X, Y, Z, W;

    hsQuat();
    hsQuat(const hsQuat& init);
    hsQuat(float x, float y, float z, float w);
    hsQuat(float rad, const hsVector3& axis);

    static hsQuat Identity();

    hsQuat& operator=(const hsQuat& cpy);
    bool operator==(const hsQuat& other) const;
    hsQuat operator+(const hsQuat& rt) const;
    hsQuat operator-(const hsQuat& rt) const;
    hsQuat operator*(const hsQuat& rt) const;
    hsQuat operator*(float scale) const;

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

    hsQuat conjugate() const;
};

#endif
