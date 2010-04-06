#include "hsRAMStream.h"

hsRAMStream::hsRAMStream(PlasmaVer pv)
           : hsStream(pv), fData(NULL), fSize(0), fMax(0), fPos(0) { }

hsRAMStream::~hsRAMStream() {
    delete[] fData;
}

void hsRAMStream::copyFrom(const void* data, size_t size) {
    fSize = size;
    fMax = ((size / BLOCKSIZE) * BLOCKSIZE) + (size % BLOCKSIZE ? BLOCKSIZE : 0);
    fPos = 0;
    delete[] fData;
    if (size == 0) {
        fData = NULL;
    } else {
        fData = new hsUbyte[size];
        memcpy(fData, data, size);
    }
}

void hsRAMStream::copyTo(void* data, size_t size) {
    size_t cpysize = (size < fSize) ? size : fSize;
    memcpy(data, fData, cpysize);
}

size_t hsRAMStream::read(size_t size, void* buf) {
    if (size + fPos > fSize)
        throw hsFileReadException(__FILE__, __LINE__, "Read past end of buffer");
    memcpy(buf, fData + fPos, size);
    fPos += size;
    return size;
}

size_t hsRAMStream::write(size_t size, const void* buf) {
    if (size + fPos > fMax) {
        size_t newSize = (fMax == 0) ? BLOCKSIZE : fMax * 2;
        while (newSize < (size + fPos))
            newSize *= 2;
        resize(newSize);
    }
    memcpy(fData + fPos, buf, size);
    fPos += size;
    if (fPos > fSize)
        fSize = fPos;
    return size;
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
    delete[] fData;

    fMax = newsize;
    fData = newData;
    if (fSize > fMax)
        fSize = fMax;
}
