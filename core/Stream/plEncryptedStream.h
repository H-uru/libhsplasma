#ifndef _PLENCRYPTEDSTREAM_H
#define _PLENCRYPTEDSTREAM_H

#include "hsStream.h"

DllClass plEncryptedStream : public hsFileStream {
public:
    enum EncryptionType { kEncNone, kEncXtea, kEncAES, kEncDroid, kEncAuto };

private:
    unsigned char LBuffer[16]; // Uru modes use only the first 8 bytes
    size_t dataSize, dataPos;
    unsigned int eKey[4];
    EncryptionType eType;

protected:
    void TeaDecipher(unsigned int* buf);
    void TeaEncipher(unsigned int* buf);
    void AesDecipher(unsigned char* buffer, int count);
    void AesEncipher(unsigned char* buffer, int count);
    void DroidDecipher(unsigned int* buf, unsigned int num);
    void DroidEncipher(unsigned int* buf, unsigned int num);
    void CryptFlush();

public:
    plEncryptedStream(PlasmaVer pv = pvUnknown);
    virtual ~plEncryptedStream();

    virtual bool open(const char* file, FileMode mode, EncryptionType type);
    virtual void close();
    void setKey(unsigned int* keys);
    EncryptionType getEncType() const;

    virtual hsUint32 size() const;
    virtual hsUint32 pos() const;
    virtual bool eof() const;

    virtual void seek(hsUint32 pos);  // Less efficient than skip...
    virtual void skip(hsInt32 count);
    virtual void rewind();

    virtual size_t read(size_t size, void* buf);
    virtual size_t write(size_t size, const void* buf);

    static bool IsFileEncrypted(const char* file);
};

#endif
