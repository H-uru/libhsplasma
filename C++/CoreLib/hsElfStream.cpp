#include "hsElfStream.h"

hsElfStream::hsElfStream() { }

hsElfStream::~hsElfStream() { }

void hsElfStream::decipher(char* v, int size, char key) {
    char a, b, c, d;

    b = key;
    d = (v[0] ^ b) >> 5;
    for (int i=size-1; i>=0; i--) {
        a = v[i] ^ b;
        c = a;
        a = (a << 3) | d;
        d = a;
        d >>= 6;
        a <<= 2;
        d |= a;
        c >>= 5;
        v[i] = d;
        d = c;
    }
}

const char* hsElfStream::readLine() {
    long long p = pos();
    unsigned short segHead = readShort();
    unsigned short segSize = segHead ^ (p & 0xFFFF);
    char key = p & 0xFF;

    char* ln = readStr(segSize);
    decipher(ln, segSize, key);
    return ln;
}

