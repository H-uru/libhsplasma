#include "Vertex3.h"

Vertex3::Vertex3() : X(0.0f), Y(0.0f), Z(0.0f) { }

Vertex3::Vertex3(float x, float y, float z) {
    X = x;
    Y = y;
    Z = z;
}

Vertex3::~Vertex3() { }

float Vertex3::getX() { return X; }
float Vertex3::getY() { return Y; }
float Vertex3::getZ() { return Z; }
void Vertex3::setX(float x) { X = x; }
void Vertex3::setY(float y) { Y = y; }
void Vertex3::setZ(float z) { Z = z; }

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

