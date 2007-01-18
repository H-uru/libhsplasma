#include "hsGeometry3.h"

/* hsScalarTriple */
hsScalarTriple::hsScalarTriple() : X(0.0f), Y(0.0f), Z(0.0f) { }

hsScalarTriple::hsScalarTriple(float x, float y, float z) {
    X = x;
    Y = y;
    Z = z;
}

hsScalarTriple::~hsScalarTriple() { }

void hsScalarTriple::read(hsStream *S) {
    X = S->readFloat();
    Y = S->readFloat();
    Z = S->readFloat();
}

void hsScalarTriple::write(hsStream *S) {
    S->writeFloat(X);
    S->writeFloat(Y);
    S->writeFloat(Z);
}

/* hsPoint3 */

hsPoint3::hsPoint3() { }
hsPoint3::hsPoint3(float x, float y, float z) { }
hsPoint3::~hsPoint3() { }

void hsPoint3::Zero() {
    X = 0.0f;
    Y = 0.0f;
    Z = 0.0f;
}

hsPoint3& hsPoint3::operator+(const hsPoint3& other) {
    hsPoint3 * result = new hsPoint3();
    result->X = X + other.X;
    result->Y = Y + other.Y;
    result->Z = Z + other.Z;
    return (*result);
}

hsPoint3& hsPoint3::operator*(const hsPoint3& other) {
    hsPoint3 * result = new hsPoint3();
    result->X = X * other.X;
    result->Y = Y * other.Y;
    result->Z = Z * other.Z;
    return (*result);
}

hsPoint3& hsPoint3::operator*(const float mult) {
    hsPoint3 * result = new hsPoint3();
    result->X = X * mult;
    result->Y = Y * mult;
    result->Z = Z * mult;
    return (*result);
}

hsPoint3& hsPoint3::operator=(const hsPoint3& other) {
    X = other.X;
    Y = other.Y;
    Z = other.Z;
    return (*this);
}

bool hsPoint3::operator==(const hsPoint3& other) {
    return (X == other.X) && (Y == other.Y) && (Z == other.Z);
}

