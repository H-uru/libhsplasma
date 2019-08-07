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

#include "plEncryptedStream.h"
#include <string.h>
#include "3rdPartyLibs/rijndael.h"

static const unsigned int uruKey[4] = { 0x6c0a5452, 0x03827d0f,
                                        0x3a170b92, 0x16db7fc2 };
static const unsigned char eoaKey[16] = { 240, 77, 37, 51, 172, 93, 39, 90,
                                          158, 24, 120, 62, 101, 44, 72, 8  };

static const char* uruMagic = "whatdoyousee";
static const char* uruMagic2 = "BriceIsSmart";
static const char* liveMagic = "notthedroids";
static const int eoaMagic = 0x0D874288;

const unsigned int* plEncryptedStream::DefaultKey() { return uruKey; }

plEncryptedStream::plEncryptedStream(int pv)
    : hsStream(pv), fBase(), fIOwnBase(false)
{
    fEKey[0] = uruKey[0];
    fEKey[1] = uruKey[1];
    fEKey[2] = uruKey[2];
    fEKey[3] = uruKey[3];
}

void plEncryptedStream::TeaDecipher(unsigned int* buf)
{
    unsigned int second = buf[1], first = buf[0], key = 0xC6EF3720;

    for (int i=0; i<32; i++) {
        second -= (((first >> 5) ^ (first << 4)) + first)
                ^ (fEKey[(key >> 11) & 3] + key);
        key += 0x61C88647;
        first -= (((second >> 5) ^ (second << 4)) + second)
               ^ (fEKey[key & 3] + key);
    }
    buf[0] = LESWAP32(first);
    buf[1] = LESWAP32(second);
}

void plEncryptedStream::TeaEncipher(unsigned int* buf)
{
    unsigned int first = LESWAP32(buf[0]), second = LESWAP32(buf[1]), key = 0;

    for (int i=0; i<32; i++) {
        first += (((second >> 5) ^ (second << 4)) + second)
               ^ (fEKey[key & 3] + key);
        key -= 0x61C88647;
        second += (((first >> 5) ^ (first << 4)) + first)
                ^ (fEKey[(key >> 11) & 3] + key);
    }
    buf[1] = second;
    buf[0] = first;
}

void plEncryptedStream::AesDecipher(unsigned char* buffer, int count)
{
    Rijndael aes;
    aes.init(Rijndael::ECB, Rijndael::Decrypt, eoaKey, Rijndael::Key16Bytes);
    unsigned char* tmpBuf = new unsigned char[count];
    memcpy(tmpBuf, buffer, count);
    aes.blockDecrypt((UINT8*)tmpBuf, count*8, (UINT8*)buffer);
    delete[] tmpBuf;
}

void plEncryptedStream::AesEncipher(unsigned char* buffer, int count)
{
    Rijndael aes;
    aes.init(Rijndael::ECB, Rijndael::Encrypt, eoaKey, Rijndael::Key16Bytes);
    unsigned char* tmpBuf = new unsigned char[count];
    memcpy(tmpBuf, buffer, count);
    aes.blockEncrypt((UINT8*)tmpBuf, count*8, (UINT8*)buffer);
    delete[] tmpBuf;
}

void plEncryptedStream::DroidDecipher(unsigned int* buf, unsigned int num)
{
    unsigned int key = ((52 / num) + 6) * 0x9E3779B9;
    while (key != 0) {
        unsigned int xorkey = (key >> 2) & 3;
        unsigned int numloop = num - 1;
        while (numloop != 0) {
            buf[numloop] -=
              (((buf[numloop - 1] << 4) ^ (buf[numloop - 1] >> 3)) +
              ((buf[numloop - 1] >> 5) ^ (buf[numloop - 1] << 2))) ^
              ((fEKey[(numloop & 3) ^ xorkey] ^ buf[numloop - 1]) +
              (key ^ buf[numloop - 1]));
            numloop--;
        }
        buf[0] -=
          (((buf[num - 1] << 4) ^ (buf[num - 1] >> 3)) +
          ((buf[num - 1] >> 5) ^ (buf[num - 1] << 2))) ^
          ((fEKey[(numloop & 3) ^ xorkey] ^ buf[num - 1]) +
          (key ^ buf[num - 1]));
        key += 0x61C88647;
    }
}

void plEncryptedStream::DroidEncipher(unsigned int* buf, unsigned int num)
{
    unsigned int key = 0;
    unsigned int count = (52 / num) + 6;
    while (count != 0) {
        key -= 0x61C88647;
        unsigned int xorkey = (key >> 2) & 3;
        unsigned int numloop = 0;
        while (numloop != num - 1) {
            buf[numloop] +=
              (((buf[numloop + 1] << 4) ^ (buf[numloop + 1] >> 3)) +
              ((buf[numloop + 1] >> 5) ^ (buf[numloop + 1] << 2))) ^
              ((fEKey[(numloop & 3) ^ xorkey] ^ buf[numloop + 1]) +
              (key ^ buf[numloop + 1]));
            numloop++;
        }
        buf[num - 1] +=
          (((buf[0] << 4) ^ (buf[0] >> 3)) +
          ((buf[0] >> 5) ^ (buf[0] << 2))) ^
          ((fEKey[(numloop & 3) ^ xorkey] ^ buf[0]) +
          (key ^ buf[0]));
        count--;
    }
}

void plEncryptedStream::CryptFlush()
{
    if (fBase == nullptr)
        throw hsBadParamException(__FILE__, __LINE__);

    if (fEType == kEncAES) {
        AesEncipher(fLBuffer, 16);
        fBase->writeInts(4, (unsigned int*)&fLBuffer[0]);
    } else if (fEType == kEncDroid) {
        DroidEncipher((unsigned int*)fLBuffer, 2);
        fBase->writeInts(2, (unsigned int*)&fLBuffer[0]);
    } else {
        TeaEncipher((unsigned int*)fLBuffer);
        fBase->writeInts(2, (unsigned int*)&fLBuffer[0]);
    }
    memset(fLBuffer, 0, 16);
}

bool plEncryptedStream::IsFileEncrypted(const ST::string& file)
{
    hsFileStream sF;
    if (!sF.open(file, fmRead))
        return false;
    if (sF.size() < 8) {
        sF.close();
        return false;
    }
    int magicN = sF.readInt();
    if (magicN == eoaMagic) {
        sF.close();
        return true;
    } else {
        sF.rewind();
        char magicS[12];
        sF.read(12, magicS);
        sF.close();
        return (memcmp(magicS, uruMagic, strlen(uruMagic)) == 0)   ||
               (memcmp(magicS, uruMagic2, strlen(uruMagic2)) == 0) ||
               (memcmp(magicS, liveMagic, strlen(liveMagic)) == 0);
    }
}

const char EncrErr[] = "File is not encrypted";

bool plEncryptedStream::open(const ST::string& file, FileMode mode, EncryptionType type)
{
    hsFileStream* S = new hsFileStream(getVer());
    if (S->open(file, mode)) {
        bool result = open(S, mode, type);
        fIOwnBase = true;
        return result;
    } else {
        return false;
    }
}

bool plEncryptedStream::open(hsStream* S, FileMode mode, EncryptionType type)
{
    close();
    setVer(S->getVer());
    fBase = S;
    fMode = mode;
    fIOwnBase = false;

    if (type == kEncNone)
        throw hsBadParamException(__FILE__, __LINE__);

    if (mode == fmRead) {
        unsigned int sz = fBase->size();
        if (sz < 8)
            throw hsFileReadException(__FILE__, __LINE__, EncrErr);
        int magicN = 0;
        magicN = fBase->readInt();
        if (magicN == eoaMagic) {
            fEType = kEncAES;
            fDataSize = fBase->readInt();
        } else {
            fBase->rewind();
            char magicS[12];
            fBase->read(12, magicS);
            if (strncmp(magicS, uruMagic, 12) == 0 ||
                strncmp(magicS, uruMagic2, 12) == 0) {
                fEType = kEncXtea;
                fDataSize = fBase->readInt();
            } else if (strncmp(magicS, liveMagic, 12) == 0) {
                fEType = kEncDroid;
                fDataSize = fBase->readInt();
            } else {
                throw hsFileReadException(__FILE__, __LINE__, EncrErr);
            }
        }
    } else {
        fEType = type;
        if (fEType == kEncAuto) {
            if (!getVer().isValid())
                throw hsBadVersionException(__FILE__, __LINE__);
            else if (getVer() < MAKE_VERSION(2, 0, 69, 0))
                fEType = kEncXtea;
            else if (getVer().isNewPlasma())
                fEType = kEncAES;
            else
                fEType = kEncDroid;
        }
        // Skip header info for now
        memset(fLBuffer, 0, 16);
        fBase->write((fEType == kEncAES) ? 8 : 16, fLBuffer);
        fDataSize = 0;
    }
    fDataPos = 0;
    return true;
}

void plEncryptedStream::close()
{
    if (fBase == nullptr)
        return;

    if (fMode == fmWrite || fMode == fmCreate) {
        size_t szInc = (fEType == kEncAES ? 16 : 8);
        if ((fDataPos % szInc) != 0)
            CryptFlush();

        // Write header info
        fBase->rewind();
        if (fEType == kEncAES)
            fBase->writeInt(eoaMagic);
        else if (fEType == kEncDroid)
            fBase->write(12, liveMagic);
        else
            fBase->write(12, uruMagic);
        fBase->writeInt(fDataSize);
    }

    if (fIOwnBase)
        delete fBase;
    fBase = nullptr;
}

void plEncryptedStream::setKey(const unsigned int* keys)
{
    fEKey[0] = keys[0];
    fEKey[1] = keys[1];
    fEKey[2] = keys[2];
    fEKey[3] = keys[3];
}

void plEncryptedStream::seek(uint32_t pos)
{
    rewind();
    skip(pos);
}

void plEncryptedStream::skip(int32_t count)
{
    if (count < 0) {
        if (((int32_t)fDataPos + count) < 0)
            throw hsFileReadException(__FILE__, __LINE__, "Seek out of range");
        seek(fDataPos + count);
    } else {
        unsigned char* ignore = new unsigned char[count];
        read(count, ignore);
        delete[] ignore;
    }
}

void plEncryptedStream::rewind()
{
    fBase->seek(fEType == kEncAES ? 8 : 16);
    fDataPos = 0;
}

size_t plEncryptedStream::read(size_t size, void* buf)
{
    if (fDataPos + size > fDataSize)
        throw hsFileReadException(__FILE__, __LINE__, "Read past end of stream");

    size_t szInc = (fEType == kEncAES ? 16 : 8);
    size_t bp = 0, lp = fDataPos % szInc;
    while (bp < size) {
        if (lp == 0) {
            // Advance the buffer
            if (fEType == kEncAES) {
                fBase->readInts(4, (unsigned int*)&fLBuffer[0]);
                AesDecipher(fLBuffer, 16);
            } else if (fEType == kEncDroid) {
                fBase->readInts(2, (unsigned int*)&fLBuffer[0]);
                DroidDecipher((unsigned int*)&fLBuffer[0], 2);
            } else {
                fBase->readInts(2, (unsigned int*)&fLBuffer[0]);
                TeaDecipher((unsigned int*)&fLBuffer[0]);
            }
        }
        if (lp + (size - bp) >= szInc) {
            memcpy(((unsigned char*)buf)+bp, fLBuffer+lp, szInc - lp);
            bp += szInc - lp;
            lp = 0;
        } else {
            memcpy(((unsigned char*)buf)+bp, fLBuffer+lp, size - bp);
            bp = size; // end loop
        }
    }

    fDataPos += size;
    return size;
}

size_t plEncryptedStream::write(size_t size, const void* buf)
{
    size_t szInc = (fEType == kEncAES ? 16 : 8);
    size_t bp = 0, lp = fDataPos % szInc;
    while (bp < size) {
        if (lp + (size - bp) >= szInc) {
            memcpy(fLBuffer+lp, ((unsigned char*)buf)+bp, szInc - lp);
            bp += szInc - lp;

            // Flush the buffer
            CryptFlush();
            lp = 0;
        } else {
            memcpy(fLBuffer+lp, ((unsigned char*)buf)+bp, size - bp);
            bp = size; // end loop
        }
    }

    fDataPos += size;
    if (fDataPos > fDataSize)
        fDataSize = fDataPos;
    return size;
}
