#include "hsRAMStream.h"

hsRAMStream::hsRAMStream(PlasmaVer pv)
           : hsStream(pv), fData(NULL), fSize(0), fMax(0), fPos(0) { }

hsRAMStream::~hsRAMStream() {
    if (fData != NULL)
        delete[] fData;
}

void hsRAMStream::copyFrom(const void* data, hsUint32 size) {
    fSize = size;
    fMax = ((size / BLOCKSIZE) * BLOCKSIZE) + (size % BLOCKSIZE ? BLOCKSIZE : 0);
    fPos = 0;
    if (fData != NULL)
        delete[] fData;
    if (size == 0) {
        fData = NULL;
    } else {
        fData = new hsUbyte[size];
        memcpy(fData, data, size);
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
    if (size + fPos > fMax) {
        if (fMax == 0)
            resize(BLOCKSIZE);
        else
            resize(fMax * 2);
    }
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
    if (fData != NULL)
        delete[] fData;

    fMax = newsize;
    fData = newData;
    if (fSize > fMax)
        fSize = fMax;
}
