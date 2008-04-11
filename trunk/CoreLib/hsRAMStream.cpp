#include "hsRAMStream.h"

hsRAMStream::hsRAMStream(PlasmaVer pv)
           : hsStream(pv), fData(NULL), fSize(0), fMax(0), fPos(0),
             fIOwnStream(false) { }

hsRAMStream::~hsRAMStream() {
    if (fIOwnStream && fData != NULL)
        delete[] fData;
}

void hsRAMStream::copyFrom(const void* data, hsUint32 size) {
    fSize = size;
    fMax = ((size / BLOCKSIZE) * BLOCKSIZE) + (size % BLOCKSIZE ? BLOCKSIZE : 0);
    fPos = 0;
    if (fIOwnStream && fData != NULL)
        delete[] fData;
    if (size == 0) {
        fData = NULL;
    } else {
        fData = new hsUbyte[size];
        memcpy(fData, data, size);
        fIOwnStream = true;
    }
}

void hsRAMStream::copyTo(void*& data, hsUint32& size) {
    if (data == NULL) {
        data = new hsUbyte[fSize];
        size = fSize;
    }
    hsUint32 cpysize = (size < fSize) ? size : fSize;
    memcpy(data, fData, cpysize);
}

void hsRAMStream::setFrom(const void* data, hsUint32 size) {
    fData = (hsUbyte*)data;
    fSize = size;
    fMax = ((size / BLOCKSIZE) * BLOCKSIZE) + (size % BLOCKSIZE ? BLOCKSIZE : 0);
    fIOwnStream = false;
}

hsUint32 hsRAMStream::size() const { return fSize; }
hsUint32 hsRAMStream::pos() const { return fPos; }
bool hsRAMStream::eof() const { return (fPos >= fSize); }

void hsRAMStream::seek(hsUint32 pos) { fPos = pos; }
void hsRAMStream::skip(hsInt32 count) { fPos += count; }
void hsRAMStream::fastForward() { fPos = fSize; }
void hsRAMStream::rewind() { fPos = 0; }

void hsRAMStream::read(size_t size, void* buf) {
    if (size + fPos > fSize)
        throw hsFileReadException(__FILE__, __LINE__, "Read past end of buffer");
    memcpy(buf, fData + fPos, size);
    fPos += size;
}

void hsRAMStream::write(size_t size, const void* buf) {
    if (size + fPos > fMax)
        resize(fMax + BLOCKSIZE);
    memcpy(fData + fPos, buf, size);
    fPos += size;
    if (fPos > fSize)
        fSize = fPos;
}

void hsRAMStream::resize(hsUint32 newsize) {
    hsUbyte* newData = NULL;

    if (newsize != 0) {
        newData = new hsUbyte[newsize];
        hsUint32 cpysize = 0;
        if (fData != NULL) {
            cpysize = (newsize < fSize) ? newsize : fSize;
            memcpy(newData, fData, cpysize);
        }
        if (newsize > cpysize)
            memset(newData + cpysize, 0, (newsize - cpysize));
    }
    if (fIOwnStream && fData != NULL)
        delete[] fData;

    fMax = newsize;
    fData = newData;
}
