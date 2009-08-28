#ifndef _PLZLIB_H
#define _PLZLIB_H

#include "PlasmaDefs.h"
#include "Stream/hsRAMStream.h"

extern "C" {
#include "3rdPartyLibs/zlib/include/zlib.h"
}

DllClass plZlib {
public:
    static bool Uncompress(unsigned char** bufIn, unsigned int* bufLenIn, unsigned int bufLenOut, int offset);
    static bool Uncompress(unsigned char* bufOut, unsigned int* bufLenOut, const unsigned char* bufIn, unsigned int bufLenIn);
    static bool ICopyBuffers(unsigned char** bufIn, unsigned int* bufLenIn, char* bufOut, unsigned int bufLenOut, int offset, bool ok);
};

#endif
