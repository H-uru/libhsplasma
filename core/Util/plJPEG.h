#ifndef _PLJPEG_H
#define _PLJPEG_H

#include "PRP/Surface/plMipmap.h"

extern "C" {
#include "3rdPartyLibs/jpeg-6b/jpeglib.h"
}

DllClass hsJPEGException : public hsException {
public:
    hsJPEGException(const char* file, unsigned long line,
                    const char* message = NULL) throw();
};


DllClass plJPEG {
public:
    static plJPEG* s_inst;
    unsigned char fWriteQuality;
    jpeg_compress_struct cinfo;
    jpeg_decompress_struct dinfo;
    jpeg_error_mgr jerr;

public:
    plJPEG();
    ~plJPEG();

    void DecompressJPEG(hsStream* S, void* buf, size_t size);
    void CompressJPEG(hsStream* S, void* buf, size_t size);
};

#endif
