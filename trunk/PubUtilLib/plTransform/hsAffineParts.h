#ifndef _HSAFFINEPARTS_H
#define _HSAFFINEPARTS_H

#include "../../CoreLib/hsGeometry3.h"
#include "../../CoreLib/hsQuat.h"
#include "../../FeatureLib/pfPRC/pfPrcHelper.h"

DllClass hsAffineParts {
protected:
    int fI; // Not used in Live
    hsVector3 fT;
    hsQuat fQ, fU;
    hsVector3 fK;
    float fF;

public:
    hsAffineParts();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
};

#endif
