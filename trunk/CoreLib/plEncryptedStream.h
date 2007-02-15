#ifndef _PLENCRYPTEDSTREAM_H
#define _PLENCRYPTEDSTREAM_H

#include "hsStream.h"

class plEncryptedStream : public hsStream {
private:
    char LBuffer[16]; // Uru modes use only the first 8 bytes
    unsigned int dataSize;
    unsigned int dataPos;
    unsigned int droidKey[4];

protected:
    void TeaDecipher(unsigned int *v1, unsigned int *v2);
    void TeaEncipher(unsigned int *v1, unsigned int *v2);
    void AesDecipher(char* buffer, int count);
    void AesEncipher(char* buffer, int count);
    void DroidDecipher(unsigned int* buf, unsigned int num);
    void DroidEncipher(unsigned int* buf, unsigned int num);

public:
    plEncryptedStream(PlasmaVer pv = pvUnknown);
    virtual ~plEncryptedStream();

    virtual void open(const char* file, FileMode mode);
    virtual void close();
    void setKey(unsigned int* keys);

    virtual unsigned int size();
    virtual unsigned int pos();
    virtual bool eof();

    virtual void seek(unsigned int pos);    // Less efficient than skip...
    virtual void skip(unsigned int count);
    virtual void rewind();

    virtual void read(unsigned int size, void* buf);
    virtual void write(unsigned int size, const void* buf);
};

#endif
