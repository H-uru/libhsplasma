#include "plEncryptedStream.h"
#include <string.h>
#include "3rdPartyLibs/rijndael.h"

static const int uruKey[4] = { 0x6c0a5452, 0x03827d0f, 0x3a170b92, 0x16db7fc2 };
static const unsigned char eoaKey[16] = { 240, 77, 37, 51, 172, 93, 39, 90,
                                          158, 24, 120, 62, 101, 44, 72, 8 };

static const char* uruMagic = "whatdoyousee";
static const char* uruMagic2 = "BriceIsSmart";
static const char* liveMagic = "notthedroids";
static const int eoaMagic = 0x0D874288;

plEncryptedStream::plEncryptedStream(PlasmaVer pv) : hsFileStream(pv) {
    eKey[0] = uruKey[0];
    eKey[1] = uruKey[1];
    eKey[2] = uruKey[2];
    eKey[3] = uruKey[3];
}

plEncryptedStream::~plEncryptedStream() {
    if (F != NULL)
        close();
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
    if (eType == kEncAES) {
        AesEncipher(LBuffer, 16);
        fwrite(LBuffer, 16, 1, F);
    } else if (eType == kEncDroid) {
        DroidEncipher((unsigned int*)&LBuffer[0], 2);
        fwrite(LBuffer, 8, 1, F);
    } else {
        TeaEncipher((unsigned int*)&LBuffer[0]);
        fwrite(LBuffer, 8, 1, F);
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
    if (!hsFileStream::open(file, mode)) return false;
    eType = type;

    if (eType == kEncNone)
        throw hsBadParamException(__FILE__, __LINE__);

    if (mode == fmRead || mode == fmReadWrite) {
        fseek(F, 0, SEEK_END);
        unsigned int sz = ftell(F);
        fseek(F, 0, SEEK_SET);
        if (sz < 8) throw hsFileReadException(__FILE__, __LINE__, EncrErr);
        int magicN = 0;
        fread(&magicN, sizeof(magicN), 1, F);
        if (magicN == eoaMagic) {
            eType = kEncAES;
            fread(&dataSize, sizeof(dataSize), 1, F);
        } else {
            fseek(F, 0, SEEK_SET);
            char magicS[12];
            fread(magicS, 1, 12, F);
            if (strncmp(magicS, uruMagic, 12) == 0 ||
                strncmp(magicS, uruMagic2, 12) == 0) {
                eType = kEncXtea;
                fread(&dataSize, sizeof(dataSize), 1, F);
            } else if (strncmp(magicS, liveMagic, 12) == 0) {
                eType = kEncDroid;
                fread(&dataSize, sizeof(dataSize), 1, F);
            } else {
                throw hsFileReadException(__FILE__, __LINE__, EncrErr);
            }
        }
    } else {
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
            fwrite(LBuffer, 8, 1, F);
        else
            fwrite(LBuffer, 16, 1, F);
        dataSize = 0;
    }

    dataPos = 0;
    return true;
}

void plEncryptedStream::close() {
    if (fm == fmWrite || fm == fmCreate) {
        size_t szInc = (eType == kEncAES ? 16 : 8);
        if ((dataPos % szInc) != 0)
            CryptFlush();

        // Write header info
        fseek(F, 0, SEEK_SET);
        if (eType == kEncAES)
            fwrite(&eoaMagic, sizeof(eoaMagic), 1, F);
        else if (eType == kEncDroid)
            fwrite(liveMagic, 12, 1, F);
        else
            fwrite(uruMagic, 12, 1, F);
        fwrite(&dataSize, sizeof(dataSize), 1, F);
    }

    hsFileStream::close();
}

void plEncryptedStream::setKey(unsigned int* keys) {
    eKey[0] = keys[0];
    eKey[1] = keys[1];
    eKey[2] = keys[2];
    eKey[3] = keys[3];
}

plEncryptedStream::EncryptionType plEncryptedStream::getEncType() const {
    return eType;
}

hsUint32 plEncryptedStream::size() const { return dataSize; }
hsUint32 plEncryptedStream::pos() const { return dataPos; }
bool plEncryptedStream::eof() const { return dataPos >= dataSize; }

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
    fseek(F, (eType == kEncAES ? 8 : 16), SEEK_SET);
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
                fread(LBuffer, 16, 1, F);
                AesDecipher(LBuffer, 16);
            } else if (eType == kEncDroid) {
                fread(LBuffer, 8, 1, F);
                DroidDecipher((unsigned int*)&LBuffer[0], 2);
            } else {
                fread(LBuffer, 8, 1, F);
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
