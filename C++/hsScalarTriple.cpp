#include "hsScalarTriple.h"

hsScalarTriple::hsScalarTriple() : a(0.0f), b(0.0f), c(0.0f) { }

hsScalarTriple::hsScalarTriple(float f1, float f2, float f3) {
    a = f1;
    b = f2;
    c = f3;
}

hsScalarTriple::~hsScalarTriple() { }

void hsScalarTriple::read(hsStream *S) {
    a = S->readFloat();
    b = S->readFloat();
    c = S->readFloat();
}

void hsScalarTriple::write(hsStream *S) {
    S->writeFloat(a);
    S->writeFloat(b);
    S->writeFloat(c);
}

