#include "hsGeometry3.h"

/* hsScalarTriple */
hsScalarTriple::hsScalarTriple() : fX(0.0f), fY(0.0f), fZ(0.0f) { }

hsScalarTriple::hsScalarTriple(float x, float y, float z)
              : fX(x), fY(y), fZ(z) { }

hsScalarTriple::~hsScalarTriple() { }

const char* hsScalarTriple::ClassName() const { return "hsScalarTriple"; }

void hsScalarTriple::read(hsStream* S) {
    fX = S->readFloat();
    fY = S->readFloat();
    fZ = S->readFloat();
}

void hsScalarTriple::write(hsStream* S) {
    S->writeFloat(fX);
    S->writeFloat(fY);
    S->writeFloat(fZ);
}

void hsScalarTriple::prcWrite(pfPrcHelper* prc) {
    prc->startTag(ClassName());
    prc->writeParam("X", fX);
    prc->writeParam("Y", fY);
    prc->writeParam("Z", fZ);
    prc->endTag(true);
}


/* hsPoint3 */
hsPoint3::hsPoint3() { }
hsPoint3::hsPoint3(float x, float y, float z) { }

hsPoint3::hsPoint3(const hsScalarTriple& src) {
    fX = src.fX;
    fY = src.fY;
    fZ = src.fZ;
}

hsPoint3::~hsPoint3() { }

const char* hsPoint3::ClassName() const { return "hsPoint3"; }

void hsPoint3::Zero() {
    fX = 0.0f;
    fY = 0.0f;
    fZ = 0.0f;
}

hsPoint3 hsPoint3::operator+(const hsPoint3& other) const {
    return hsPoint3(fX + other.fX, fY + other.fY, fZ + other.fZ);
}

hsPoint3 hsPoint3::operator-(const hsPoint3& other) const {
    return hsPoint3(fX - other.fX, fY - other.fY, fZ - other.fZ);
}

hsPoint3 hsPoint3::operator*(const float mult) const {
    return hsPoint3(fX * mult, fY * mult, fZ * mult);
}

hsPoint3& hsPoint3::operator=(const hsPoint3& other) {
    fX = other.fX;
    fY = other.fY;
    fZ = other.fZ;
    return (*this);
}

bool hsPoint3::operator==(const hsPoint3& other) const {
    return (fX == other.fX) && (fY == other.fY) && (fZ == other.fZ);
}


/* hsVector3 */
hsVector3::hsVector3() { }
hsVector3::hsVector3(float x, float y, float z) { }

hsVector3::hsVector3(const hsScalarTriple& src) {
    fX = src.fX;
    fY = src.fY;
    fZ = src.fZ;
}

hsVector3::~hsVector3() { }

const char* hsVector3::ClassName() const { return "hsVector3"; }

hsVector3& hsVector3::operator=(const hsVector3& other) {
    fX = other.fX;
    fY = other.fY;
    fZ = other.fZ;
    return (*this);
}

bool hsVector3::operator==(const hsVector3& other) const {
    return (fX == other.fX) && (fY == other.fY) && (fZ == other.fZ);
}

hsVector3 hsVector3::operator+(const hsVector3& other) const {
    return hsVector3(fX + other.fX, fY + other.fY, fZ + other.fZ);
}

hsVector3 hsVector3::operator-(const hsVector3& other) const {
    return hsVector3(fX - other.fX, fY - other.fY, fZ - other.fZ);
}

hsVector3 hsVector3::operator*(const float mult) const {
    return hsVector3(fX * mult, fY * mult, fZ * mult);
}

float hsVector3::dotP(const hsVector3& other) const {
    return (fX * other.fX) + (fY * other.fY) + (fZ * other.fZ);
}

hsVector3 hsVector3::crossP(const hsVector3& other) const {
    return hsVector3((fY * other.fZ) - (fZ * other.fY),
                     (fZ * other.fX) - (fX * other.fZ),
                     (fX * other.fY) - (fY * other.fX));
}


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
    prc->writeParam("X", fN.fX);
    prc->writeParam("Y", fN.fY);
    prc->writeParam("Z", fN.fZ);
    prc->writeParam("D", fD);
    prc->endTag(true);
}
