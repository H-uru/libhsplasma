#include "plJPEG.h"
#include <jpeglib.h>

// Uses IJG's libjpeg...  Unless someone knows of something better ;)
// I think IJL (what Cyan used) is commercial, but if it isn't and it's easy
// to set up for the three major platforms (Lin, Win & Mac), I'm all for using
// it too.

plJPEG* plJPEG::inst = NULL;

plJPEG::plJPEG(PlasmaVer pv) {
    if (inst != NULL)
        throw "Never construct me more than once!";
    inst = this;
}

plJPEG::~plJPEG() {
    inst = NULL;
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
