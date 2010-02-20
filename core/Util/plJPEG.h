#ifndef _PLJPEG_H
#define _PLJPEG_H

#include "PRP/Surface/plMipmap.h"

extern "C" {
#include <jpeglib.h>
}

DllClass hsJPEGException : public hsException {
public:
    hsJPEGException(const char* file, unsigned long line,
                    const char* message = NULL) throw();
};


DllClass plJPEG {
private:
    static bool fJPEGInited;
    static jpeg_compress_struct cinfo;
    static jpeg_decompress_struct dinfo;
    static jpeg_error_mgr jerr;

public:
    static void Init();
    static void DecompressJPEG(hsStream* S, void* buf, size_t size);
    static void CompressJPEG(hsStream* S, void* buf, size_t size);

private:
    static void DeInit();
};

#endif
