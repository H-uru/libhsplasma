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
static const unsigned char eoaKey[16] = {
                                          240, 77, 37, 51, 172, 93, 39, 90,
                                          158, 24, 120, 62, 101, 44, 72, 8
                                        };

static const char* uruMagic = "whatdoyousee";
static const char* uruMagic2 = "BriceIsSmart";
static const char* liveMagic = "notthedroids";
static const int eoaMagic = 0x0D874288;

const unsigned int* plEncryptedStream::DefaultKey() { return uruKey; }

plEncryptedStream::plEncryptedStream() {
    eKey[0] = uruKey[0];
    eKey[1] = uruKey[1];
    eKey[2] = uruKey[2];
    eKey[3] = uruKey[3];
}

plEncryptedStream::plEncryptedStream(hsStream* S) {
    eKey[0] = uruKey[0];
    eKey[1] = uruKey[1];
    eKey[2] = uruKey[2];
    eKey[3] = uruKey[3];

    openRead(S);
    base = S;

    setVer(base->getVer());
}

plEncryptedStream::~plEncryptedStream() {
    close();
    delete base;
}

void plEncryptedStream::TeaDecipher(unsigned int* buf) {
    unsigned int second = buf[1], first = buf[0], key = 0xC6EF3720;

    for (int i=0; i<32; i++) {
        second -= (((first >> 5) ^ (first << 4)) + first)
                ^ (eKey[(key >> 11) & 3] + key);
        key += 0x61C88647;
        first -= (((second >> 5) ^ (second << 4)) + second)
               ^ (eKey[key & 3] + key);
    }
    buf[0] = first;
    buf[1] = second;
}

void plEncryptedStream::TeaEncipher(unsigned int* buf) {
    unsigned int first = buf[0], second = buf[1], key = 0;

    for (int i=0; i<32; i++) {
        first += (((second >> 5) ^ (second << 4)) + second)
               ^ (eKey[key & 3] + key);
        key -= 0x61C88647;
        second += (((first >> 5) ^ (first << 4)) + first)
                ^ (eKey[(key >> 11) & 3] + key);
    }
    buf[1] = second;
    buf[0] = first;
}

void plEncryptedStream::AesDecipher(unsigned char* buffer, int count) {
    Rijndael aes;
    aes.init(Rijndael::ECB, Rijndael::Decrypt, eoaKey, Rijndael::Key16Bytes);
    unsigned char* tmpBuf = new unsigned char[count];
    memcpy(tmpBuf, buffer, count);
    aes.blockDecrypt((UINT8*)tmpBuf, count*8, (UINT8*)buffer);
    delete[] tmpBuf;
}

void plEncryptedStream::AesEncipher(unsigned char* buffer, int count) {
    Rijndael aes;
    aes.init(Rijndael::ECB, Rijndael::Encrypt, eoaKey, Rijndael::Key16Bytes);
    unsigned char* tmpBuf = new unsigned char[count];
    memcpy(tmpBuf, buffer, count);
    aes.blockEncrypt((UINT8*)tmpBuf, count*8, (UINT8*)buffer);
    delete[] tmpBuf;
}

void plEncryptedStream::DroidDecipher(unsigned int* buf, unsigned int num) {
    unsigned int key = ((52 / num) + 6) * 0x9E3779B9;
    while (key != 0) {
        unsigned int xorkey = (key >> 2) & 3;
        unsigned int numloop = num - 1;
        while (numloop != 0) {
            buf[numloop] -=
              (((buf[numloop - 1] << 4) ^ (buf[numloop - 1] >> 3)) +
              ((buf[numloop - 1] >> 5) ^ (buf[numloop - 1] << 2))) ^
              ((eKey[(numloop & 3) ^ xorkey] ^ buf[numloop - 1]) +
              (key ^ buf[numloop - 1]));
            numloop--;
        }
        buf[0] -=
          (((buf[num - 1] << 4) ^ (buf[num - 1] >> 3)) +
          ((buf[num - 1] >> 5) ^ (buf[num - 1] << 2))) ^
          ((eKey[(numloop & 3) ^ xorkey] ^ buf[num - 1]) +
          (key ^ buf[num - 1]));
        key += 0x61C88647;
    }
}

void plEncryptedStream::DroidEncipher(unsigned int* buf, unsigned int num) {
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
              ((eKey[(numloop & 3) ^ xorkey] ^ buf[numloop + 1]) +
              (key ^ buf[numloop + 1]));
            numloop++;
        }
        buf[num - 1] +=
          (((buf[0] << 4) ^ (buf[0] >> 3)) +
          ((buf[0] >> 5) ^ (buf[0] << 2))) ^
          ((eKey[(numloop & 3) ^ xorkey] ^ buf[0]) +
          (key ^ buf[0]));
        count--;
    }
}

void plEncryptedStream::CryptFlush() {
    if (base == NULL)
        throw hsBadParamException(__FILE__, __LINE__);

    if (eType == kEncAES) {
        AesEncipher(LBuffer, 16);
        base->write(16, LBuffer);
    } else if (eType == kEncDroid) {
        DroidEncipher((unsigned int*)&LBuffer[0], 2);
        base->write(8, LBuffer);
    } else {
        TeaEncipher((unsigned int*)&LBuffer[0]);
        base->write(8, LBuffer);
    }
    memset(LBuffer, 0, 16);
}

bool plEncryptedStream::IsFileEncrypted(const char* file) {
    FILE* tF = fopen(file, "rb");
    if (tF == NULL) return false;
    fseek(tF, 0, SEEK_END);
    unsigned int sz = ftell(tF);
    fseek(tF, 0, SEEK_SET);
    if (sz < 8) return false;
    int magicN = 0;
    fread(&magicN, sizeof(magicN), 1, tF);
    if (magicN == eoaMagic) {
        fclose(tF);
        return true;
    } else {
        fseek(tF, 0, SEEK_SET);
        char magicS[12];
        fread(magicS, 1, 12, tF);
        fclose(tF);
        if (strncmp(magicS, uruMagic, 12) == 0 ||
            strncmp(magicS, uruMagic2, 12) == 0 ||
            strncmp(magicS, liveMagic, 12) == 0)
            return true;
        return false;
    }
}

const char* EncrErr = "File is not encrypted";

bool plEncryptedStream::open(const char* file, FileMode mode, EncryptionType type) {
    base = new hsFileStream();
    ((hsFileStream*)base)->open(file, mode);
    bool ret;

    if (mode == fmRead || mode == fmReadWrite) {
        ret = openRead(base);
    } else if (mode == fmWrite || mode == fmCreate) {
        ret = openWrite(base, type);
    } else {
        throw hsBadParamException(__FILE__, __LINE__);
    }

    this->mode = mode;
    return ret;
}

bool plEncryptedStream::openRead(hsStream* S) {
    setVer(S->getVer());
    base = S;
    mode = fmRead;

    unsigned int sz = base->size();
    if (sz < 8)
        throw hsFileReadException(__FILE__, __LINE__, EncrErr);
    int magicN = 0;
    base->read(sizeof(magicN), &magicN);
    if (magicN == eoaMagic) {
        eType = kEncAES;
        base->read(sizeof(dataSize), &dataSize);
    } else {
        base->rewind();
        char magicS[12];
        base->read(12, magicS);
        if (strncmp(magicS, uruMagic, 12) == 0 ||
            strncmp(magicS, uruMagic2, 12) == 0) {
            eType = kEncXtea;
            base->read(sizeof(dataSize), &dataSize);
        } else if (strncmp(magicS, liveMagic, 12) == 0) {
            eType = kEncDroid;
            base->read(sizeof(dataSize), &dataSize);
        } else {
            throw hsFileReadException(__FILE__, __LINE__, EncrErr);
        }
    }
    dataPos = 0;
    return true;
}

bool plEncryptedStream::openWrite(hsStream* S, EncryptionType type) {
    setVer(S->getVer());
    base = S;
    eType = type;
    mode = fmCreate;

    if (eType == kEncNone)
        throw hsBadParamException(__FILE__, __LINE__);

    if (eType == kEncAuto) {
        if (getVer() == pvUnknown)
            throw hsBadVersionException(__FILE__, __LINE__);
        else if (getVer() < pvLive)
            eType = kEncXtea;
        else if (getVer() > pvLive)
            eType = kEncAES;
        else
            eType = kEncDroid;
    }
    // Skip header info for now
    memset(LBuffer, 0, 16);
    if (eType == kEncAES)
        base->write(8, LBuffer);
    else
        base->write(16, LBuffer);
    dataSize = 0;
    dataPos = 0;
    return true;
}

void plEncryptedStream::close() {

    if (mode == fmWrite || mode == fmCreate) {
        size_t szInc = (eType == kEncAES ? 16 : 8);
        if ((dataPos % szInc) != 0)
            CryptFlush();

        // Write header info
        base->rewind();
        if (eType == kEncAES)
            base->write(sizeof(eoaMagic), &eoaMagic);
        else if (eType == kEncDroid)
            base->write(12, liveMagic);
        else
            base->write(12, uruMagic);
        base->write(sizeof(dataSize), &dataSize);
    }
}


void plEncryptedStream::setKey(unsigned int* keys) {
    eKey[0] = keys[0];
    eKey[1] = keys[1];
    eKey[2] = keys[2];
    eKey[3] = keys[3];
}

void plEncryptedStream::seek(hsUint32 pos) {
    rewind();
    skip(pos);
}

void plEncryptedStream::skip(hsInt32 count) {
    if (count < 0) {
        if ((dataPos + count) < 0)
            throw hsFileReadException(__FILE__, __LINE__, "Seek out of range");
        seek(dataPos + count);
    } else {
        unsigned char* ignore = new unsigned char[count];
        read(count, ignore);
        delete[] ignore;
    }
}

void plEncryptedStream::rewind() {
    base->seek(eType == kEncAES ? 8 : 16);
    dataPos = 0;
}

size_t plEncryptedStream::read(size_t size, void* buf) {
    if (dataPos + size > dataSize)
        throw hsFileReadException(__FILE__, __LINE__, "Read past end of stream");

    size_t szInc = (eType == kEncAES ? 16 : 8);
    size_t bp = 0, lp = dataPos % szInc;
    while (bp < size) {
        if (lp == 0) {
            // Advance the buffer
            if (eType == kEncAES) {
                base->read(16, LBuffer);
                AesDecipher(LBuffer, 16);
            } else if (eType == kEncDroid) {
                base->read(8, LBuffer);
                DroidDecipher((unsigned int*)&LBuffer[0], 2);
            } else {
                base->read(8, LBuffer);
                TeaDecipher((unsigned int*)&LBuffer[0]);
            }
        }
        if (lp + (size - bp) >= szInc) {
            memcpy(((unsigned char*)buf)+bp, LBuffer+lp, szInc - lp);
            bp += szInc - lp;
            lp = 0;
        } else {
            memcpy(((unsigned char*)buf)+bp, LBuffer+lp, size - bp);
            bp = size; // end loop
        }
    }

    dataPos += size;
    return size;
}

size_t plEncryptedStream::write(size_t size, const void* buf) {
    size_t szInc = (eType == kEncAES ? 16 : 8);
    size_t bp = 0, lp = dataPos % szInc;
    while (bp < size) {
        if (lp + (size - bp) >= szInc) {
            memcpy(LBuffer+lp, ((unsigned char*)buf)+bp, szInc - lp);
            bp += szInc - lp;

            // Flush the buffer
            CryptFlush();
            lp = 0;
        } else {
            memcpy(LBuffer+lp, ((unsigned char*)buf)+bp, size - bp);
            bp = size; // end loop
        }
    }

    dataPos += size;
    if (dataPos > dataSize) dataSize = dataPos;
    return size;
}
