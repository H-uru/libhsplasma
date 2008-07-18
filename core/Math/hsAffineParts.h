#ifndef _HSAFFINEPARTS_H
#define _HSAFFINEPARTS_H

#include "hsGeometry3.h"
#include "hsQuat.h"

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
    void prcParse(const pfPrcTag* tag);
};

#endif
