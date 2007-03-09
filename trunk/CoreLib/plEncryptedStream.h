#ifndef _PLENCRYPTEDSTREAM_H
#define _PLENCRYPTEDSTREAM_H

#include "hsStream.h"

DllClass plEncryptedStream : public hsStream {
private:
    char LBuffer[16]; // Uru modes use only the first 8 bytes
    unsigned int dataSize;
    unsigned int dataPos;
    unsigned int eKey[4];

protected:
    void TeaDecipher(unsigned int* buf);
    void TeaEncipher(unsigned int* buf);
    void AesDecipher(char* buffer, int count);
    void AesEncipher(char* buffer, int count);
    void DroidDecipher(unsigned int* buf, unsigned int num);
    void DroidEncipher(unsigned int* buf, unsigned int num);

public:
    plEncryptedStream(PlasmaVer pv = pvUnknown);
    virtual ~plEncryptedStream();

    virtual bool open(const char* file, FileMode mode);
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

    static bool isFileEncrypted(const char* file);
};

#endif
