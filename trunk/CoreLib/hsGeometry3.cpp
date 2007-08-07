#include "hsGeometry3.h"

/* hsScalarTriple */
hsScalarTriple::hsScalarTriple() : X(0.0f), Y(0.0f), Z(0.0f) { }

hsScalarTriple::hsScalarTriple(float x, float y, float z) {
    X = x;
    Y = y;
    Z = z;
}

hsScalarTriple::~hsScalarTriple() { }

const char* hsScalarTriple::ClassName() { return "hsScalarTriple"; }

void hsScalarTriple::read(hsStream* S) {
    X = S->readFloat();
    Y = S->readFloat();
    Z = S->readFloat();
}

void hsScalarTriple::write(hsStream* S) {
    S->writeFloat(X);
    S->writeFloat(Y);
    S->writeFloat(Z);
}

void hsScalarTriple::prcWrite(pfPrcHelper* prc) {
    prc->startTag(ClassName());
    prc->writeParam("X", X);
    prc->writeParam("Y", Y);
    prc->writeParam("Z", Z);
    prc->endTag(true);
}


/* hsPoint3 */
hsPoint3::hsPoint3() { }
hsPoint3::hsPoint3(float x, float y, float z) { }

hsPoint3::hsPoint3(const hsScalarTriple& src) {
    X = src.X;
    Y = src.Y;
    Z = src.Z;
}

hsPoint3::~hsPoint3() { }

const char* hsPoint3::ClassName() { return "hsPoint3"; }

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


/* hsVector3 */
hsVector3::hsVector3() { }
hsVector3::hsVector3(float x, float y, float z) { }

hsVector3::hsVector3(const hsScalarTriple& src) {
    X = src.X;
    Y = src.Y;
    Z = src.Z;
}

hsVector3::~hsVector3() { }

const char* hsVector3::ClassName() { return "hsVector3"; }


/* hsPlane3 */
hsPlane3::hsPlane3() : fN(), fD(0.0f) { }
hsPlane3::~hsPlane3() { }

void hsPlane3::read(hsStream* S) {
    fN.read(S);
    fD = S->readFloat();
}

void hsPlane3::write(hsStream* S) {
    fN.write(S);
    S->writeFloat(fD);
}

void hsPlane3::prcWrite(pfPrcHelper* prc) {
    prc->startTag("hsPlane3");
    prc->writeParam("X", fN.X);
    prc->writeParam("Y", fN.Y);
    prc->writeParam("Z", fN.Z);
    prc->writeParam("D", fD);
    prc->endTag(true);
}
