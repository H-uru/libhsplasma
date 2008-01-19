#include <cstring>
#include <cstdlib>
#include "hsElfStream.h"

hsElfStream::hsElfStream() { }

hsElfStream::~hsElfStream() { }

void hsElfStream::decipher(unsigned char* v, int size, unsigned char hint) {
    unsigned char key = (v[0] ^ hint) >> 5;
    for (int i=size-1; i>=0; i--) {
        unsigned char c = ((v[i] ^ hint) << 3) | key;
        v[i] = (c >> 6) | (c << 2);
        key = (v[i] ^ hint) >> 5;
    }
}

void hsElfStream::encipher(unsigned char* v, unsigned char hint) {
    size_t size = strlen((const char*)v);
    unsigned char key = (v[size-1] & 0xFC) << 3;
    for (size_t i=0; i<size; i++) {
        unsigned char c = (v[i] << 6) | (v[i] >> 2);
        v[i] = ((c >> 3) | key) ^ hint;
        key = c << 5;
    }
}

plString hsElfStream::readLine() {
    unsigned int p = pos();
    unsigned short segHead = readShort();
    unsigned short segSize = segHead ^ (p & 0xFFFF);

    char* ln = new char[segSize+1];
    read(segSize, ln);
    ln[segSize] = 0;
    decipher((unsigned char*)ln, segSize, (p & 0xFF));
    return plString(ln);
}

void hsElfStream::writeLine(const plString& ln) {
    // This may or may not work...
    unsigned int p = pos();
    unsigned short segSize = ln.len();

    char* lnWrite = ln.copybuf();
    encipher((unsigned char*)lnWrite, (p & 0xFF));
    writeShort(segSize ^ (p & 0xFFFF));
    write(segSize, lnWrite);
    delete[] lnWrite;
}
