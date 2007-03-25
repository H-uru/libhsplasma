#ifndef _HSCOLORRGBA_H
#define _HSCOLORRGBA_H

#include "hsStream.h"
#include "../FeatureLib/pfPRC/pfPrcHelper.h"

struct hsColorRGBA {
public:
    float r, g, b, a;

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(hsStream* S, pfPrcHelper* prc);
};

struct hsColor32 {
public:
    union {
        unsigned char b, g, r, a;
        unsigned int color;
    };

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(hsStream* S, pfPrcHelper* prc);
};

#endif
