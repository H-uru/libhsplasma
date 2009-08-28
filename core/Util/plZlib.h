#ifndef _PLZLIB_H
#define _PLZLIB_H

#include "PlasmaDefs.h"

extern "C" {
#include "zlib.h"
}

DllClass plZlib {
public:
    static bool Uncompress(unsigned char* bufIn, unsigned int bufLenIn, unsigned char* bufOut, unsigned int* bufLenOut);
};

#endif
