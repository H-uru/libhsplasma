#include "hsQuat.h"
#include <cmath>

hsQuat::hsQuat()
      : fX(0.0f), fY(0.0f), fZ(0.0f), fW(0.0f) { }
hsQuat::hsQuat(const hsQuat& init)
      : fX(init.fX), fY(init.fY), fZ(init.fZ), fW(init.fW) { }
hsQuat::hsQuat(float X, float Y, float Z, float W)
      : fX(X), fY(Y), fZ(Z), fW(W) { }

hsQuat::hsQuat(float rad, const hsVector3& axis) {
    fW = cos(rad * 0.5);
    fX = sin(rad * 0.5) * axis.fX;
    fY = sin(rad * 0.5) * axis.fY;
    fZ = sin(rad * 0.5) * axis.fZ;
}

void hsQuat::read(hsStream* S) {
    fX = S->readFloat();
    fY = S->readFloat();
    fZ = S->readFloat();
    fW = S->readFloat();
}

void hsQuat::write(hsStream* S) {
    S->writeFloat(fX);
    S->writeFloat(fY);
    S->writeFloat(fZ);
    S->writeFloat(fW);
}

void hsQuat::prcWrite(pfPrcHelper* prc) {
    prc->startTag("hsQuat");
    prc->writeParam("X", fX);
    prc->writeParam("Y", fY);
    prc->writeParam("Z", fZ);
    prc->writeParam("W", fW);
    prc->endTag(true);
}
