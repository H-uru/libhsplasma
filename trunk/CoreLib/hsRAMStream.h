#ifndef _HSRAMSTREAM_H
#define _HSRAMSTREAM_H

#include "hsStream.h"

#define BLOCKSIZE 4096  // Common block size on x86 machines

DllClass hsRAMStream : public hsStream {
protected:
    hsUbyte* fData;
    hsUint32 fSize, fMax, fPos;
    bool fIOwnData;

public:
    hsRAMStream(PlasmaVer pv = pvUnknown);
    virtual ~hsRAMStream();

    void copyFrom(const void* data, hsUint32 size);
    void copyTo(void*& data, hsUint32& size);
    void setFrom(const void* data, hsUint32 size);

    virtual hsUint32 size() const;
    virtual hsUint32 pos() const;
    virtual bool eof() const;
    
    virtual void seek(hsUint32 pos);
    virtual void skip(hsInt32 count);
    virtual void fastForward();
    virtual void rewind();

    virtual void read(size_t size, void* buf);
    virtual void write(size_t size, const void* buf);

    virtual void resize(hsUint32 newsize);
};

#endif
