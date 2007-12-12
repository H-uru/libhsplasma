#ifndef _PLENCRYPTEDSTREAM_H
#define _PLENCRYPTEDSTREAM_H

#include "hsStream.h"

DllClass plEncryptedStream : public hsStream {
private:
    char LBuffer[16]; // Uru modes use only the first 8 bytes
    size_t dataSize, dataPos;
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

    virtual hsUint32 size() const;
    virtual hsUint32 pos() const;
    virtual bool eof() const;

    virtual void seek(hsUint32 pos);  // Less efficient than skip...
    virtual void skip(hsUint32 count);
    virtual void rewind();

    virtual void read(size_t size, void* buf);
    virtual void write(size_t size, const void* buf);

    static bool isFileEncrypted(const char* file);
};

#endif
