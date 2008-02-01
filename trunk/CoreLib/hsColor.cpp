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

void hsColorRGBA::prcWrite(pfPrcHelper* prc) {
    prc->startTag("hsColorRGBA");
    prc->writeParam("red", r);
    prc->writeParam("green", g);
    prc->writeParam("blue", b);
    prc->writeParam("alpha", a);
    prc->endTag(true);
}


/* hsColor32 */
void hsColor32::read(hsStream* S) {
    color = S->readInt();
}

void hsColor32::write(hsStream* S) {
    S->writeInt(color);
}

void hsColor32::prcWrite(pfPrcHelper* prc) {
    prc->startTag("hsColor32");
    prc->writeParam("value", color);
    prc->endTag(true);
}
