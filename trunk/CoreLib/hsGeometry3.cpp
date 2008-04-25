#include "hsGeometry3.h"
#include <math.h>

/* hsVector3 */
hsVector3::hsVector3() : X(0.0f), Y(0.0f), Z(0.0f) { }

hsVector3::hsVector3(float _x, float _y, float _z)
         : X(_x), Y(_y), Z(_z) { }

hsVector3::hsVector3(const hsVector3& src)
         : X(src.X), Y(src.Y), Z(src.Z) { }

void hsVector3::Zero() {
    X = 0.0f;
    Y = 0.0f;
    Z = 0.0f;
}

float hsVector3::magnitude() const {
    return sqrt(X*X + Y*Y + Z*Z);
}

void hsVector3::read(hsStream* S) {
    X = S->readFloat();
    Y = S->readFloat();
    Z = S->readFloat();
}

void hsVector3::write(hsStream* S) {
    S->writeFloat(X);
    S->writeFloat(Y);
    S->writeFloat(Z);
}

void hsVector3::prcWrite(pfPrcHelper* prc) {
    prc->startTag("hsVector3");
    prc->writeParam("X", X);
    prc->writeParam("Y", Y);
    prc->writeParam("Z", Z);
    prc->endTag(true);
}

hsVector3 hsVector3::operator+(const hsVector3& other) const {
    return hsVector3(X + other.X, Y + other.Y, Z + other.Z);
}

hsVector3 hsVector3::operator-(const hsVector3& other) const {
    return hsVector3(X - other.X, Y - other.Y, Z - other.Z);
}

hsVector3 hsVector3::operator*(const float mult) const {
    return hsVector3(X * mult, Y * mult, Z * mult);
}

hsVector3& hsVector3::operator=(const hsVector3& other) {
    X = other.X;
    Y = other.Y;
    Z = other.Z;
    return (*this);
}

bool hsVector3::operator==(const hsVector3& other) const {
    return (X == other.X) && (Y == other.Y) && (Z == other.Z);
}

float hsVector3::dotP(const hsVector3& other) const {
    return (X * other.X) + (Y * other.Y) + (Z * other.Z);
}

hsVector3 hsVector3::crossP(const hsVector3& other) const {
    return hsVector3((Y * other.Z) - (Z * other.Y),
                     (Z * other.X) - (X * other.Z),
                     (X * other.Y) - (Y * other.X));
}


/* hsPlane3 */
hsPlane3::hsPlane3() : W(0.0f) { }

void hsPlane3::read(hsStream* S) {
    N.read(S);
    W = S->readFloat();
}

void hsPlane3::write(hsStream* S) {
    N.write(S);
    S->writeFloat(W);
}

void hsPlane3::prcWrite(pfPrcHelper* prc) {
    prc->startTag("hsPlane3");
    prc->writeParam("X", N.X);
    prc->writeParam("Y", N.Y);
    prc->writeParam("Z", N.Z);
    prc->writeParam("W", W);
    prc->endTag(true);
}
