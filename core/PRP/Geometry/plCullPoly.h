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

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

public:
    unsigned int getFlags() const { return fFlags; }
    const hsTArray<hsVector3>& getVerts() const { return fVerts; }
    hsVector3 getNorm() const { return fNorm; }
    hsVector3 getCenter() const { return fCenter; }
    float getDist() const { return fDist; }
    float getRadius() const { return fRadius; }

    void setFlags(unsigned int flags) { fFlags = flags; }
    void setVerts(const hsTArray<hsVector3>& verts) { fVerts = verts; }
    void setNorm(const hsVector3& norm) { fNorm = norm; }
    void setCenter(const hsVector3& center) { fCenter = center; }
    void setDist(float dist) { fDist = dist; }
    void setRadius(float radius) { fRadius = radius; }
};

#endif
