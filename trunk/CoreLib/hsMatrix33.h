#ifndef _HSMATRIX33_H
#define _HSMATRIX33_H

#include "../FeatureLib/pfPRC/pfPrcHelper.h"

DllStruct hsMatrix33 {
private:
    float data[3][3];

public:
    float& operator()(int x, int y);

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
};

#endif
