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

class PLASMA_DLL plEncryptedStream : public hsStream
{
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
    ~plEncryptedStream() { close(); }

    bool open(const ST::string& file, FileMode mode, EncryptionType type);
    bool open(hsStream* S, FileMode mode, EncryptionType type);
    void close() HS_OVERRIDE;
    void setKey(const unsigned int* keys);
    EncryptionType getEncType() const { return fEType; }

    uint32_t size() const HS_OVERRIDE { return fDataSize; }
    uint32_t pos() const HS_OVERRIDE { return fDataPos; }
    bool eof() const HS_OVERRIDE { return fDataPos >= fDataSize; }

    void seek(uint32_t pos) HS_OVERRIDE;
    void skip(int32_t count) HS_OVERRIDE;
    void fastForward() HS_OVERRIDE { seek(size()); }
    void rewind() HS_OVERRIDE;
    void flush() HS_OVERRIDE { fBase->flush(); }

    size_t read(size_t size, void* buf) HS_OVERRIDE;
    size_t write(size_t size, const void* buf) HS_OVERRIDE;

    static bool IsFileEncrypted(const ST::string& file);
};

#endif
