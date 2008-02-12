#ifndef _PLCULLPOLY_H
#define _PLCULLPOLY_H

#include "FeatureLib/pfPRC/pfPrcHelper.h"
#include "CoreLib/hsBitVector.h"
#include "CoreLib/hsGeometry3.h"

DllClass plCullPoly {
public:
    enum {
        kNone,
        kHole = 0x1,
        kTwoSided = 0x2
    };

protected:
    unsigned int fFlags;
    hsBitVector fClipped;
    hsTArray<hsPoint3> fVerts;
    hsVector3 fNorm;
    float fDist;
    hsPoint3 fCenter;
    float fRadius;

public:
    plCullPoly();
    ~plCullPoly();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
};

#endif
