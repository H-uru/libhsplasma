/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _PLENCRYPTEDSTREAM_H
#define _PLENCRYPTEDSTREAM_H

#include "hsStream.h"

class PLASMA_DLL plEncryptedStream : public hsStream {
public:
    enum EncryptionType { kEncNone, kEncXtea, kEncAES, kEncDroid, kEncAuto };

    static const unsigned int* DefaultKey();

private:
    unsigned char fLBuffer[16]; // Uru modes use only the first 8 bytes
    unsigned int fDataSize, fDataPos;
    unsigned int fEKey[4];
    EncryptionType fEType;
    FileMode fMode;
    hsStream* fBase;
    bool fIOwnBase;

protected:
    void TeaDecipher(unsigned int* buf);
    void TeaEncipher(unsigned int* buf);
    void AesDecipher(unsigned char* buffer, int count);
    void AesEncipher(unsigned char* buffer, int count);
    void DroidDecipher(unsigned int* buf, unsigned int num);
    void DroidEncipher(unsigned int* buf, unsigned int num);
    void CryptFlush();

public:
    plEncryptedStream(int pv = PlasmaVer::pvUnknown);
    virtual ~plEncryptedStream();

    bool open(const char* file, FileMode mode, EncryptionType type);
    bool open(hsStream* S, FileMode mode, EncryptionType type);
    void close();
    void setKey(unsigned int* keys);
    EncryptionType getEncType() const { return fEType; }

    virtual uint32_t size() const { return fDataSize; }
    virtual uint32_t pos() const { return fDataPos; }
    virtual bool eof() const { return fDataPos >= fDataSize; }

    virtual void seek(uint32_t pos);
    virtual void skip(int32_t count);
    virtual void fastForward() { seek(size()); }
    virtual void rewind();
    virtual void flush() { fBase->flush(); }

    virtual size_t read(size_t size, void* buf);
    virtual size_t write(size_t size, const void* buf);

    static bool IsFileEncrypted(const char* file);
};

#endif
