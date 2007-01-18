#ifndef _HSGEOMETRY3_H
#define _HSGEOMETRY3_H

#include "hsStream.h"

struct hsScalarTriple {
public:
    float X, Y, Z;

public:
    hsScalarTriple();
    hsScalarTriple(float x, float y, float z);
    ~hsScalarTriple();

    void read(hsStream *S);
    void write(hsStream *S);
};

struct hsPoint3 : public hsScalarTriple {
public:
    hsPoint3();
    hsPoint3(float x, float y, float z);
    ~hsPoint3();

    void Zero();

    hsPoint3& operator+(const hsPoint3& other);
    hsPoint3& operator*(const hsPoint3& other);
    hsPoint3& operator*(const float mult);
    hsPoint3& operator=(const hsPoint3& other);
    bool operator==(const hsPoint3& other);
};

struct hsFloatPoint2 {
public:
    float X, Y;
};

#endif

