#include "plJPEG.h"
#include <jpeglib.h>

// Uses IJG's libjpeg

plJPEG* plJPEG::inst = NULL;

plJPEG::plJPEG(PlasmaVer pv) {
    if (inst != NULL)
        throw "Never construct me more than once!";
    inst = this;
}

plMipmap* plJPEG::IRead(hsStream* S) {
    struct jpeg_decompress_struct cinfo;
    JSAMPARRAY buffer;
    int row_stride;

    //jpeg_create_decompress(&cinfo);
    
    return NULL;
}

void plJPEG::IWrite(plMipmap* source, hsStream* S) {
    //
}
