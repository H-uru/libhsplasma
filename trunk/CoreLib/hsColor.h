#ifndef _HSCOLORRGBA_H
#define _HSCOLORRGBA_H

#include "hsStream.h"
#include "FeatureLib/pfPRC/pfPrcHelper.h"
#include "FeatureLib/pfPRC/pfPrcParser.h"

DllStruct hsColorRGBA {
public:
    static const hsColorRGBA kBlack;
    static const hsColorRGBA kWhite;
    static const hsColorRGBA kRed;
    static const hsColorRGBA kGreen;
    static const hsColorRGBA kBlue;
    static const hsColorRGBA kGray;
    static const hsColorRGBA kNone;

public:
    float r, g, b, a;

    hsColorRGBA(float red = 0.0f, float green = 0.0f, float blue = 0.0f,
                float alpha = 1.0f);
    void set(float red, float green, float blue, float alpha = 1.0f);

    void read(hsStream* S);
    void write(hsStream* S);
    void readRGB(hsStream* S);
    void writeRGB(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);
};

DllStruct hsColor32 {
public:
    union {
        unsigned char b, g, r, a;
        unsigned int color;
    };

    void read32(hsStream* S);
    void write32(hsStream* S);
    void readRGB8(hsStream* S);
    void writeRGB8(hsStream* S);
    void readRGBA8(hsStream* S);
    void writeRGBA8(hsStream*S );
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);
};

#endif
