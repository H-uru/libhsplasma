#include "hsQuat.h"
#include <cmath>

hsQuat::hsQuat()
      : X(0.0f), Y(0.0f), Z(0.0f), W(0.0f) { }
hsQuat::hsQuat(const hsQuat& init)
      : X(init.X), Y(init.Y), Z(init.Z), W(init.W) { }
hsQuat::hsQuat(float _x, float _y, float _z, float _w)
      : X(_x), Y(_y), Z(_z), W(_w) { }

hsQuat::hsQuat(float rad, const hsVector3& axis) {
    W = cos(rad * 0.5f);
    X = sin(rad * 0.5f) * axis.X;
    Y = sin(rad * 0.5f) * axis.Y;
    Z = sin(rad * 0.5f) * axis.Z;
}

void hsQuat::read(hsStream* S) {
    X = S->readFloat();
    Y = S->readFloat();
    Z = S->readFloat();
    W = S->readFloat();
}

void hsQuat::write(hsStream* S) {
    S->writeFloat(X);
    S->writeFloat(Y);
    S->writeFloat(Z);
    S->writeFloat(W);
}

void hsQuat::prcWrite(pfPrcHelper* prc) {
    prc->startTag("hsQuat");
    prc->writeParam("X", X);
    prc->writeParam("Y", Y);
    prc->writeParam("Z", Z);
    prc->writeParam("W", W);
    prc->endTag(true);
}
