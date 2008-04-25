#include "hsColor.h"

/* hsColorRGBA */
const hsColorRGBA hsColorRGBA::kBlack = hsColorRGBA(0.0f, 0.0f, 0.0f, 1.0f);
const hsColorRGBA hsColorRGBA::kWhite = hsColorRGBA(1.0f, 1.0f, 1.0f, 1.0f);
const hsColorRGBA hsColorRGBA::kRed   = hsColorRGBA(1.0f, 0.0f, 0.0f, 1.0f);
const hsColorRGBA hsColorRGBA::kGreen = hsColorRGBA(0.0f, 1.0f, 0.0f, 1.0f);
const hsColorRGBA hsColorRGBA::kBlue  = hsColorRGBA(0.0f, 0.0f, 1.0f, 1.0f);
const hsColorRGBA hsColorRGBA::kGray  = hsColorRGBA(0.5f, 0.5f, 0.5f, 1.0f);
const hsColorRGBA hsColorRGBA::kNone  = hsColorRGBA(0.0f, 0.0f, 0.0f, 0.0f);

hsColorRGBA::hsColorRGBA(float red, float green, float blue, float alpha)
           : r(red), g(green), b(blue), a(alpha) { }

void hsColorRGBA::set(float red, float green, float blue, float alpha) {
    r = red;
    g = green;
    b = blue;
    a = alpha;
}

void hsColorRGBA::read(hsStream* S) {
    r = S->readFloat();
    g = S->readFloat();
    b = S->readFloat();
    a = S->readFloat();
}

void hsColorRGBA::write(hsStream* S) {
    S->writeFloat(r);
    S->writeFloat(g);
    S->writeFloat(b);
    S->writeFloat(a);
}

void hsColorRGBA::readRGB(hsStream* S) {
    r = S->readFloat();
    g = S->readFloat();
    b = S->readFloat();
    a = 1.0f;
}

void hsColorRGBA::writeRGB(hsStream* S) {
    S->writeFloat(r);
    S->writeFloat(g);
    S->writeFloat(b);
}

void hsColorRGBA::prcWrite(pfPrcHelper* prc) {
    prc->startTag("hsColorRGBA");
    prc->writeParam("red", r);
    prc->writeParam("green", g);
    prc->writeParam("blue", b);
    prc->writeParam("alpha", a);
    prc->endTag(true);
}


/* hsColor32 */
void hsColor32::read32(hsStream* S) {
    color = S->readInt();
}

void hsColor32::write32(hsStream* S) {
    S->writeInt(color);
}

void hsColor32::readRGB8(hsStream* S) {
    r = S->readByte();
    g = S->readByte();
    b = S->readByte();
}

void hsColor32::writeRGB8(hsStream* S) {
    S->writeByte(r);
    S->writeByte(g);
    S->writeByte(b);
}

void hsColor32::readRGBA8(hsStream* S) {
    r = S->readByte();
    g = S->readByte();
    b = S->readByte();
    a = S->readByte();
}

void hsColor32::writeRGBA8(hsStream* S) {
    S->writeByte(r);
    S->writeByte(g);
    S->writeByte(b);
    S->writeByte(a);
}

void hsColor32::prcWrite(pfPrcHelper* prc) {
    prc->startTag("hsColor32");
    prc->writeParamHex("value", color);
    prc->endTag(true);
}
