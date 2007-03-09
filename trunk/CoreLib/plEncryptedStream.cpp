#include "plEncryptedStream.h"
#include <string.h>
#include "../rijndael.h"

static const int uruKey[4] = { 0x6c0a5452, 0x03827d0f, 0x3a170b92, 0x16db7fc2 };
static const unsigned char eoaKey[16] = { 240, 77, 37, 51, 172, 93, 39, 90,
                                          158, 24, 120, 62, 101, 44, 72, 8 };

static const char* uruMagic = "whatdoyousee";
static const char* uruMagic2 = "BriceIsSmart";
static const char* liveMagic = "notthedroids";
static const int eoaMagic = 0x0D874288;

plEncryptedStream::plEncryptedStream(PlasmaVer pv) {
    eKey[0] = uruKey[0];
    eKey[1] = uruKey[1];
    eKey[2] = uruKey[2];
    eKey[3] = uruKey[3];
}
plEncryptedStream::~plEncryptedStream() { }

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

void plEncryptedStream::AesDecipher(char* buffer, int count) {
    Rijndael aes;
    aes.init(Rijndael::ECB, Rijndael::Decrypt, eoaKey, Rijndael::Key16Bytes);
    char* tmpBuf = new char[count];
    memcpy(tmpBuf, buffer, count);
    aes.blockDecrypt((UINT8*)tmpBuf, count*8, (UINT8*)buffer);
    delete[] tmpBuf;
}

void plEncryptedStream::AesEncipher(char* buffer, int count) {
    Rijndael aes;
    aes.init(Rijndael::ECB, Rijndael::Encrypt, eoaKey, Rijndael::Key16Bytes);
    char* tmpBuf = new char[count];
    memcpy(tmpBuf, buffer, count);
    aes.blockEncrypt((UINT8*)tmpBuf, count*8, (UINT8*)buffer);
    delete[] tmpBuf;
}

void plEncryptedStream::DroidDecipher(unsigned int* buf, unsigned int num) {
    unsigned int key = (52 / num + 6) * 0x9E3779B9;
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
        key -= 0x9E3779B9;
    }
}

void plEncryptedStream::DroidEncipher(unsigned int* buf, unsigned int num) {
    unsigned int key = 0;
    unsigned int count = 52 / num + 6;
    while (count != 0) {
        key += 0x9E3779B9;
        unsigned int xorkey = (key >> 2) & 3;
        unsigned int numloop = 0;
        while (numloop < num - 1) {
            buf[numloop] +=
              (((buf[numloop + 1] << 4) ^ (buf[numloop + 1] >> 3)) +
              ((buf[numloop + 1] >> 5) ^ (buf[numloop + 1] << 2))) ^
              ((eKey[(numloop & 3) ^ xorkey] ^ buf[numloop + 1]) +
              (key ^ buf[numloop + 1]));
            numloop++;
        }
        buf[num - 1] +=
          (((buf[num - 1] << 4) ^ (buf[num - 1] >> 3)) +
          ((buf[num - 1] >> 5) ^ (buf[num - 1] << 2))) ^
          ((eKey[(numloop & 3) ^ xorkey] ^ buf[num - 1]) +
          (key ^ buf[num - 1]));
        count--;
    }
}

bool plEncryptedStream::isFileEncrypted(const char* file) {
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
bool plEncryptedStream::open(const char* file, FileMode mode) {
    if (!hsStream::open(file, mode)) return false;

    if (mode == fmRead || mode == fmReadWrite) {
        fseek(F, 0, SEEK_END);
        unsigned int sz = ftell(F);
        fseek(F, 0, SEEK_SET);
        if (sz < 8) throw EncrErr;
        int magicN = 0;
        fread(&magicN, sizeof(magicN), 1, F);
        if (magicN == eoaMagic) {
            ver = pvEoa;
            fread(&dataSize, sizeof(dataSize), 1, F);
        } else {
            fseek(F, 0, SEEK_SET);
            char magicS[12];
            fread(magicS, 1, 12, F);
            if (strncmp(magicS, uruMagic, 12) == 0 ||
                strncmp(magicS, uruMagic2, 12) == 0) {
                ver = pvPrime;
                fread(&dataSize, sizeof(dataSize), 1, F);
            } else if (strncmp(magicS, liveMagic, 12) == 0) {
                ver = pvLive;
                fread(&dataSize, sizeof(dataSize), 1, F);
            } else {
                throw EncrErr;
            }
        }
    } else {
        if (ver == pvUnknown)
            throw "Invalid Plasma Version";
        // Skip header info for now
        memset(LBuffer, 0, 16);
        if (ver == pvEoa)
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
        // Write header info
        fseek(F, 0, SEEK_SET);
        if (ver == pvEoa)
            fwrite(&eoaMagic, sizeof(eoaMagic), 1, F);
        else if (ver == pvLive)
            fwrite(liveMagic, 12, 1, F);
        else
            fwrite(uruMagic, 12, 1, F);
        fwrite(&dataSize, sizeof(dataSize), 1, F);
    }

    hsStream::close();
}

void plEncryptedStream::setKey(unsigned int* keys) {
    eKey[0] = keys[0];
    eKey[1] = keys[1];
    eKey[2] = keys[2];
    eKey[3] = keys[3];
}

unsigned int plEncryptedStream::size() { return dataSize; }
unsigned int plEncryptedStream::pos() { return dataPos; }
bool plEncryptedStream::eof() { return dataPos >= dataSize; }

void plEncryptedStream::seek(unsigned int pos) {
    rewind();
    skip(pos);
}

void plEncryptedStream::skip(unsigned int count) {
    char* ignore = new char[count];
    read(count, ignore);
    delete[] ignore;
}

void plEncryptedStream::rewind() {
    fseek(F, (ver == pvEoa ? 8 : 16), SEEK_SET);
    dataPos = 0;
}

void plEncryptedStream::read(unsigned int size, void* buf) {
    if (dataPos + size > dataSize)
        throw "Read beyond end of stream!";
    
    unsigned int szInc = (ver == pvEoa ? 16 : 8);
    unsigned int pp = dataPos, bp = 0, lp = dataPos % szInc;
    while (bp < size) {
        if (lp == 0) {
            // Advance the buffer
            if (ver == pvEoa) {
                fread(LBuffer, 16, 1, F);
                AesDecipher(LBuffer, 16);
            } else if (ver == pvLive) {
                fread(LBuffer, 8, 1, F);
                DroidDecipher((unsigned int*)&LBuffer[0], 2);
            } else {
                fread(LBuffer, 8, 1, F);
                TeaDecipher((unsigned int*)&LBuffer[0]);
            }
        }
        if (lp + (size - bp) >= szInc) {
            memcpy(((char*)buf)+bp, LBuffer+lp, szInc - lp);
            bp += szInc - lp;
            pp += szInc - lp;
            lp = 0;
        } else {
            memcpy(((char*)buf)+bp, LBuffer+lp, size - bp);
            bp = size; // end loop
        }
    }

    dataPos += size;
}

void plEncryptedStream::write(unsigned int size, const void* buf) {
    unsigned int szInc = (ver == pvEoa ? 16 : 8);
    unsigned int pp = dataPos, bp = 0, lp = dataPos % szInc;
    while (bp < size) {
        if (lp + (size - bp) >= szInc) {
            memcpy(LBuffer+lp, ((char*)buf)+bp, szInc - lp);
            bp += szInc - lp;
            pp += szInc - lp;
            lp = 0;
        } else {
            memcpy(LBuffer+lp, ((char*)buf)+bp, size - bp);
            bp = size; // end loop
        }
        if (lp == 0) {
            // Flush the buffer
            if (ver == pvEoa) {
                AesEncipher(LBuffer, 16);
                fwrite(LBuffer, 16, 1, F);
            } else if (ver == pvLive) {
                DroidEncipher((unsigned int*)&LBuffer[0], 2);
                fwrite(LBuffer, 8, 1, F);
            } else {
                TeaEncipher((unsigned int*)&LBuffer[0]);
                fwrite(LBuffer, 8, 1, F);
            }
            memset(LBuffer, 0, 16);
        }
    }

    dataPos += size;
    if (dataPos > dataSize) dataSize = dataPos;
}

