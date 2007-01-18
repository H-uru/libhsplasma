#ifndef _HSBOUNDS_H
#define _HSBOUNDS_H

#include "hsStream.h"
#include "hsGeometry3.h"

class hsBounds {
protected:
    int fType;

public:
    hsBounds();
    ~hsBounds();

    void read(hsStream *S);
    void write(hsStream *S);
};

class hsBounds3 : public hsBounds {
protected:
    int fBounds3Flags;
    hsPoint3 fMins, fMaxs, fCenter;

public:
    hsBounds3();
    ~hsBounds3();

    void read(hsStream *S);
    void write(hsStream *S);
};

class hsBounds3Ext : public hsBounds3 {
protected:
    int fExtFlags;
    hsPoint3 fCorner;
    hsPoint3 fAxes[3];
    hsFloatPoint2 fDists[3];
    float fRadius;

public:
    hsBounds3Ext();
    ~hsBounds3Ext();

    void read(hsStream *S);
    void write(hsStream *S);
};

#endif

