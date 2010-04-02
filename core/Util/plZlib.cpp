#include "plZlib.h"
#include "Stream/hsRAMStream.h"
#include <zlib.h>

bool plZlib::Uncompress(unsigned char* bufOut, unsigned int& bufLenOut, const unsigned char* bufIn, unsigned int bufLenIn) {
    return (::uncompress(bufOut, (uLongf*)&bufLenOut, bufIn, bufLenIn) == Z_OK);
}

bool plZlib::Compress(unsigned char*& bufOut, unsigned int& bufLenOut, const unsigned char* bufIn, unsigned int bufLenIn) {
    bufLenOut = ::compressBound(bufLenIn);
    bufOut = new unsigned char[bufLenOut];
    return (::compress(bufOut, (uLongf*)&bufLenOut, bufIn, bufLenIn) == Z_OK);
}
