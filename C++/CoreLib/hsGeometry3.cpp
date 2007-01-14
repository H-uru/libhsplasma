#include "hsGeometry3.h"

/* hsScalarTriple */
hsScalarTriple::hsScalarTriple() : X(0.0f), Y(0.0f), Z(0.0f) { }

hsScalarTriple::hsScalarTriple(float x, float y, float z) {
    X = x;
    Y = y;
    Z = z;
}

hsScalarTriple::~hsScalarTriple() { }

float hsScalarTriple::getX() { return X; }
float hsScalarTriple::getY() { return Y; }
float hsScalarTriple::getZ() { return Z; }
void hsScalarTriple::setX(float x) { X = x; }
void hsScalarTriple::setY(float y) { Y = y; }
void hsScalarTriple::setZ(float z) { Z = z; }

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

/* Vertex3 */

Vertex3::Vertex3() : X(0.0f), Y(0.0f), Z(0.0f) { }

Vertex3::Vertex3(float x, float y, float z) {
    X = x;
    Y = y;
    Z = z;
}

Vertex3::Vertex3(Vertex3& other) {
    X = other.X;
    Y = other.Y;
    Z = other.Z;
}

Vertex3::Vertex3(hsScalarTriple& st) {
    X = st.getX();
    Y = st.getY();
    Z = st.getZ();
}

Vertex3::~Vertex3() { }

void Vertex3::Zero() {
    X = 0.0f;
    Y = 0.0f;
    Z = 0.0f;
}

float Vertex3::getX() { return X; }
float Vertex3::getY() { return Y; }
float Vertex3::getZ() { return Z; }
void Vertex3::setX(float x) { X = x; }
void Vertex3::setY(float y) { Y = y; }
void Vertex3::setZ(float z) { Z = z; }

Vertex3& Vertex3::operator+(const Vertex3& other) {
    Vertex3 * result = new Vertex3();
    result->X = X + other.X;
    result->Y = Y + other.Y;
    result->Z = Z + other.Z;
    return (*result);
}

Vertex3& Vertex3::operator*(const Vertex3& other) {
    Vertex3 * result = new Vertex3();
    result->X = X * other.X;
    result->Y = Y * other.Y;
    result->Z = Z * other.Z;
    return (*result);
}

Vertex3& Vertex3::operator*(const float mult) {
    Vertex3 * result = new Vertex3();
    result->X = X * mult;
    result->Y = Y * mult;
    result->Z = Z * mult;
    return (*result);
}

Vertex3& Vertex3::operator=(const Vertex3& other) {
    X = other.X;
    Y = other.Y;
    Z = other.Z;
    return (*this);
}

Vertex3& Vertex3::operator=(hsScalarTriple& st) {
    X = st.getX();
    Y = st.getY();
    Z = st.getZ();
    return (*this);
}

bool Vertex3::operator==(const Vertex3& other) {
    return (X == other.X) && (Y == other.Y) && (Z == other.Z);
}

void Vertex3::read(hsStream *S) {
    X = S->readFloat();
    Y = S->readFloat();
    Z = S->readFloat();
}

void Vertex3::write(hsStream *S) {
    S->writeFloat(X);
    S->writeFloat(Y);
    S->writeFloat(Z);
}

