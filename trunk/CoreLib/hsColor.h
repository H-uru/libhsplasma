#ifndef _HSCOLORRGBA_H
#define _HSCOLORRGBA_H

#include "hsStream.h"
#include "FeatureLib/pfPRC/pfPrcHelper.h"

DllStruct hsColorRGBA {
public:
    float r, g, b, a;

    hsColorRGBA(float red = 0.0f, float green = 0.0f, float blue = 0.0f,
                float alpha = 1.0f);
    void set(float red, float green, float blue, float alpha);

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
};

DllStruct hsColor32 {
public:
    union {
        unsigned char b, g, r, a;
        unsigned int color;
    };

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
};

#endif
