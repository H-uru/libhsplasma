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
    plCullPoly(const plCullPoly& init);
    ~plCullPoly();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);
    
    unsigned int getFlags() const;
    const hsTArray<hsVector3>& getVerts() const;
    hsVector3 getNorm() const;
    hsVector3 getCenter() const;
    float getDist() const;
    float getRadius() const;

    void setFlags(unsigned int flags);
    void setVerts(const hsTArray<hsVector3>& verts);
    void setNorm(const hsVector3& norm);
    void setCenter(const hsVector3& center);
    void setDist(float dist);
    void setRadius(float radius);
};

#endif
