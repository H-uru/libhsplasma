#include "hsGMatState.h"

hsGMatState::hsGMatState(unsigned int blend, unsigned int clamp,
                         unsigned int shade, unsigned int Z,
                         unsigned int misc) {
    blendFlags = blend;
    clampFlags = clamp;
    shadeFlags = shade;
    ZFlags = Z;
    miscFlags = misc;
}

void hsGMatState::read(hsStream* S) {
    blendFlags = S->readInt();
    clampFlags = S->readInt();
    shadeFlags = S->readInt();
    ZFlags = S->readInt();
    miscFlags = S->readInt();
}

void hsGMatState::write(hsStream* S) {
    S->writeInt(blendFlags);
    S->writeInt(clampFlags);
    S->writeInt(shadeFlags);
    S->writeInt(ZFlags);
    S->writeInt(miscFlags);
}

void hsGMatState::prcWrite(hsStream* S, pfPrcHelper* prc) {
    prc->startTag("hsGMatState");
    prc->writeParam("BlendFlags", blendFlags);
    prc->writeParam("ClampFlags", clampFlags);
    prc->writeParam("ShadeFlags", shadeFlags);
    prc->writeParam("ZFlags", ZFlags);
    prc->writeParam("MiscFlags", miscFlags);
    prc->endTag(true);
}
