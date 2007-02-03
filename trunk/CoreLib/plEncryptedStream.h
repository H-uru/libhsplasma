#ifndef _PLENCRYPTEDSTREAM_H
#define _PLENCRYPTEDSTREAM_H

#include "hsStream.h"

class plEncryptedStream : hsStream {
private:
    char LTeaBuffer[8];
    char LAesBuffer[16];
    unsigned int bufPage;

protected:
    void TeaDecipher(unsigned int *v1, unsigned int *v2);
    void TeaEncipher(unsigned int *v1, unsigned int *v2);
    void AesDecipher(char* buffer, int count);
    void AesEncipher(char* buffer, int count);

    void IAdvanceBuffer();
    void IRegressBuffer();

public:
    plEncryptedStream(PlasmaVer pv = pvUnknown);
    virtual ~plEncryptedStream();
};

#endif
