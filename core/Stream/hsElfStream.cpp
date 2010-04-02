#include <cstring>
#include <cstdlib>
#include "hsElfStream.h"

hsElfStream::hsElfStream() : hsFileStream(pvUnknown) { }

void hsElfStream::decipher(unsigned char* v, int size, unsigned char hint) {
    unsigned char key = (v[0] ^ hint) >> 5;
    for (int i=size-1; i>=0; i--) {
        unsigned char a = (v[i] ^ hint);
        key = (a << 3) | key;
        v[i] = (key >> 6) | (key << 2);
        key = a >> 5;
    }
}

void hsElfStream::encipher(unsigned char* v, int size, unsigned char hint) {
    unsigned char key = (v[size-1] & 0xFC) << 3;
    for (int i=0; i<size; i++) {
        unsigned char a = (v[i] << 6) | (v[i] >> 2);
        v[i] = ((a >> 3) | key) ^ hint;
        key = a << 5;
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
    plString line(ln);
    delete[] ln;
    return line;
}

void hsElfStream::writeLine(const plString& ln) {
    // This may or may not work...
    unsigned int p = pos();
    unsigned short segSize = ln.len();

    char* lnWrite = new char[ln.len() + 1];
    memcpy(lnWrite, ln.cstr(), ln.len() + 1);
    encipher((unsigned char*)lnWrite, segSize, (p & 0xFF));
    writeShort(segSize ^ (p & 0xFFFF));
    write(segSize, lnWrite);
    delete[] lnWrite;
}
