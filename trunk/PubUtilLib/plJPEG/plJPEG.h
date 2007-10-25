#ifndef _PLJPEG_H
#define _PLJPEG_H

#include "../plGImage/plMipmap.h"
#include <jpeglib.h>

class plJPEG {
public:
    static plJPEG* inst;
    unsigned char writeQuality;
    jpeg_compress_struct cinfo;
    jpeg_decompress_struct dinfo;
    jpeg_error_mgr jerr;

public:
    plJPEG();
    ~plJPEG();

    plMipmap* IRead(hsStream* S);
    void IWrite(plMipmap* source, hsStream* S);
};

#endif
