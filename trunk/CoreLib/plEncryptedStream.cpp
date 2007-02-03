#include "plEncryptedStream.h"

static const int uruKey[4] = { 0x6c0a5452, 0x03827d0f, 0x3a170b92, 0x16db7fc2 };
static const unsigned char eoaKey[16] = { 240, 77, 37, 51, 172, 93, 39, 90,
                                          158, 24, 120, 62, 101, 44, 72, 8 };

static const char* uruMagic = "whatdoyousee";
static const char* uruMagic2 = "BriceIsSmart";
static const int eoaMagic = 0x0D874288;

plEncryptedStream::plEncryptedStream(PlasmaVer pv) : bufPage(0) { }
plEncryptedStream::~plEncryptedStream() { }

void plEncryptedStream::TeaDecipher(unsigned int *v1, unsigned int *v2) {
    unsigned int o1 = *v1, o2 = *v2, base = 0xc6ef3720;
    unsigned int t1, t2;
    
    for (int index = 0x20; index>0; index--) {
        // First word
        t1 = t2 = o1;
        t1 >>= 5;
        t2 <<= 4;
        t1 = (t1 ^ t2) + o1;
        
        t2 = (base >> 0x0B) & 0x03;
        t2 = uruKey[t2] + base;
        base += 0x61c88647;
        
        t1 ^= t2;
        o2 -= t1;
        
        // Second word
        t1 = t2 = o2;
        t1 >>= 5;
        t2 <<= 4;
        t1 = (t1 ^ t2) + o2;
        
        t2 = base & 0x03;
        t2 = uruKey[t2] + base;
        
        t1 ^= t2;
        o1 -= t1;
     }
     *v1 = o1;
     *v2 = o2;
}

void plEncryptedStream::TeaEncipher(unsigned int *v1, unsigned int *v2) {
    unsigned int o1 = *v1, o2 = *v2, base = 0;
    unsigned int t1, t2;

    for (int index = 0x20; index > 0; index--) {
        // Second word
        t1 = t2 = o2;
        t1 >>= 5;
        t2 <<= 4;
        t1 = (t1 ^ t2) + o2;

        t2 = base & 0x03;
        t2 = uruKey[t2] + base;
        base -= 0x61c88647;

        t1 ^= t2;
        o1 += t1;

        // First word
        t1 = t2 = o1;
        t1 >>= 5;
        t2 <<= 4;
        t1 = (t1 ^ t2) + o1;

        t2 = (base >> 0x0B) & 0x03;
        t2 = uruKey[t2] + base;

        t1 ^= t2;
        o2 += t1;
    }

    *v1 = o1;
    *v2 = o2;
}

void plEncryptedStream::AesDecipher(char* buffer, int count) {

}

void plEncryptedStream::AesEncipher(char* buffer, int count) {

}

void plEncryptedStream::IAdvanceBuffer() {
    if (ver == pvUnknown)
        throw "Plasma version is unknown!";
    //else if (ver == pvEoa)
    //    ...
}

void plEncryptedStream::IRegressBuffer() {

}
