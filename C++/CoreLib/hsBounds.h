#ifndef _HSBOUNDS_H
#define _HSBOUNDS_H

#include "hsStream.h"
#include "hsGeometry3.h"

class hsBounds {
protected:
    int fType;

public:
    hsBounds();
    virtual ~hsBounds();

    virtual void read(hsStream *S);
    virtual void write(hsStream *S);
};

class hsBounds3 : public hsBounds {
protected:
    int fBounds3Flags;
    hsPoint3 fMins, fMaxs, fCenter;

public:
    hsBounds3();
    virtual ~hsBounds3();

    virtual void read(hsStream *S);
    virtual void write(hsStream *S);
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
    virtual ~hsBounds3Ext();

    virtual void read(hsStream *S);
    virtual void write(hsStream *S);
};

#endif

