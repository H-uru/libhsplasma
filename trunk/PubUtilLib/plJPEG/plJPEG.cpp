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
    
    plMipmap* newMipmap = NULL;
    unsigned char* jpegSrcBuffer = NULL;
    unsigned int size = S->readInt();
    jpegSrcBuffer = (unsigned char*)malloc(size);
    S->read(size, jpegSrcBuffer);
    
    newMipmap = new plMipmap(S->getVer());
    newMipmap->setJPEGData(jpegSrcBuffer, size);

    // To be implemented later...
    
    free(jpegSrcBuffer);
    return newMipmap;
}

void plJPEG::IWrite(plMipmap* source, hsStream* S) {
    S->writeInt(source->getJPEGSize());
    S->write(source->getJPEGSize(), source->getJPEGData());
}

