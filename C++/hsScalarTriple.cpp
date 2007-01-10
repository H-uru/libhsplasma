#include "hsScalarTriple.h"

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

