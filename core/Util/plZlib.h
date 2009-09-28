#ifndef _PLZLIB_H
#define _PLZLIB_H

#include "PlasmaDefs.h"

DllClass plZlib {
public:
    static bool Uncompress(unsigned char* bufOut, unsigned int& bufLenOut, const unsigned char* bufIn, unsigned int bufLenIn);
    static bool Compress(unsigned char*& bufOut, unsigned int& bufLenOut, const unsigned char* bufIn, unsigned int bufLenIn);
};

#endif
