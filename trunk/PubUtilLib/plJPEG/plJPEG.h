#ifndef _PLJPEG_H
#define _PLJPEG_H

#include "../plGImage/plMipmap.h"

class plJPEG {
public:
    static plJPEG* inst;
    unsigned char writeQuality;

public:
    plJPEG(PlasmaVer pv = pvUnknown);
    ~plJPEG();

    plMipmap* IRead(hsStream* S);
    void IWrite(plMipmap* source, hsStream* S);
};

#endif
