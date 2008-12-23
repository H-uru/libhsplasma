#ifndef _PLCULLPOLY_H
#define _PLCULLPOLY_H

#include "Util/hsBitVector.h"
#include "Math/hsGeometry3.h"

DllClass plCullPoly {
public:
    enum {
        kNone,
        kHole = 0x1,
        kTwoSided = 0x2
    };

protected:
    unsigned int fFlags;
    hsTArray<hsVector3> fVerts;
    hsVector3 fNorm, fCenter;
    float fDist, fRadius;

public:
    plCullPoly();
    ~plCullPoly();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);
    
    hsTArray<hsVector3> GetVerts() const;
};

#endif
