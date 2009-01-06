#ifndef _HSGEOMETRY3_H
#define _HSGEOMETRY3_H

#include "Stream/hsStream.h"
#include "Stream/pfPrcHelper.h"
#include "Stream/pfPrcParser.h"

DllStruct hsVector3 {
    float X, Y, Z;

    hsVector3();
    hsVector3(float x, float y, float z);
    hsVector3(const hsVector3& src);
    hsVector3& operator=(const hsVector3& other);

    void Zero();
    float magnitude() const;
    bool operator==(const hsVector3& other) const;
    bool operator!=(const hsVector3& other) const;

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

    hsVector3 operator+(const hsVector3& other) const;
    hsVector3 operator-(const hsVector3& other) const;
    hsVector3 operator*(const float mult) const;
    float dotP(const hsVector3& other) const;
    hsVector3 crossP(const hsVector3& other) const;
};

DllStruct hsPlane3 {
    hsVector3 N;
    float W;

    hsPlane3();
    hsPlane3(const hsVector3& n, float w);
    hsPlane3(const hsPlane3& src);
    hsPlane3& operator=(const hsPlane3& other);

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);
};

DllStruct hsFloatPoint2 {
    float X, Y;

    hsFloatPoint2();
};

#endif
