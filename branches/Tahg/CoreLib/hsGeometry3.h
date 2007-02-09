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
    hsPoint3(const hsScalarTriple& src);
    ~hsPoint3();

    void Zero();

    hsPoint3& operator=(const hsPoint3& other);
    bool operator==(const hsPoint3 & other);
    hsPoint3& operator+(const hsPoint3& other);
    hsPoint3& operator*(const hsPoint3& other);
    hsPoint3& operator*(const float mult);

    hsPoint3 * Set(const struct hsScalarTriple *);
    hsPoint3 * Set(float, float, float);
    bool operator!=(const hsPoint3& other);
    hsPoint3 & operator+=(const struct hsScalarTriple &);
    hsPoint3 & operator*=(const float);
};

struct hsVector3 : hsScalarTriple {
public:
    hsVector3(const hsScalarTriple& src);
    hsVector3(float x, float y, float z);
    hsVector3();
    ~hsVector3();

    hsVector3(const hsPoint3*, const hsPoint3*);
    hsVector3 * hsVector3::Set(const hsScalarTriple *, const hsScalarTriple *);
    hsVector3 * hsVector3::Set(const hsScalarTriple *);
    hsVector3 * hsVector3::Set(float, float, float);
    void hsVector3::Normalize();
    void Renormalize();
    unsigned long hsVector3::operator==(const hsVector3 &);
    hsVector3 & hsVector3::operator+=(const hsScalarTriple &);
    hsVector3 & operator-=(const hsScalarTriple &);
    hsVector3 & hsVector3::operator*=(const float);
    hsVector3 & hsVector3::operator/=(const float);
};

struct hsPlane3 {
public:
    hsVector3 fN;
    float fD;

public:
    hsPlane3();
    ~hsPlane3();

    void read(hsStream* S);
    void write(hsStream* S);
};

struct hsFloatPoint2 {
public:
    float X, Y;
};

#endif

