#include "hsGMatState.h"

hsGMatState::hsGMatState(unsigned int blend, unsigned int clamp,
                         unsigned int shade, unsigned int Z,
                         unsigned int misc) {
    fBlendFlags = blend;
    fClampFlags = clamp;
    fShadeFlags = shade;
    fZFlags = Z;
    fMiscFlags = misc;
}

void hsGMatState::read(hsStream* S) {
    fBlendFlags = S->readInt();
    fClampFlags = S->readInt();
    fShadeFlags = S->readInt();
    fZFlags = S->readInt();
    fMiscFlags = S->readInt();
}

void hsGMatState::write(hsStream* S) {
    S->writeInt(fBlendFlags);
    S->writeInt(fClampFlags);
    S->writeInt(fShadeFlags);
    S->writeInt(fZFlags);
    S->writeInt(fMiscFlags);
}

void hsGMatState::prcWrite(pfPrcHelper* prc) {
    prc->startTag("hsGMatState");
    prc->writeParamHex("BlendFlags", fBlendFlags);
    prc->writeParamHex("ClampFlags", fClampFlags);
    prc->writeParamHex("ShadeFlags", fShadeFlags);
    prc->writeParamHex("ZFlags", fZFlags);
    prc->writeParamHex("MiscFlags", fMiscFlags);
    prc->endTag(true);
}

void hsGMatState::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "hsGMatState")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fBlendFlags = tag->getParam("BlendFlags", "0").toUint();
    fClampFlags = tag->getParam("ClampFlags", "0").toUint();
    fShadeFlags = tag->getParam("ShadeFlags", "0").toUint();
    fZFlags = tag->getParam("ZFlags", "0").toUint();
    fMiscFlags = tag->getParam("MiscFlags", "0").toUint();
}
