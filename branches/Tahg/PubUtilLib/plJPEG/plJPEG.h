#ifndef _PLJPEG_H
#define _PLJPEG_H

#include "../plGImage/plMipmap.h"

class plJPEG {
public:
    static plJPEG* inst;

public:
    plJPEG::plJPEG(PlasmaVer pv = pvUnknown);

    plMipmap* IRead(hsStream* S);
    void IWrite(plMipmap* source, hsStream* S);
};

#endif
