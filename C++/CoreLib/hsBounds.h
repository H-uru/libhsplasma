#ifndef _HSBOUNDS_H
#define _HSBOUNDS_H

#include "hsStream.h"
#include "../Vertex3.h"
#include "../hsScalarTriple.h"

class hsBounds {
protected:
    int Unknown;

public:
    hsBounds();
    ~hsBounds();

    void read(hsStream *S);
    void write(hsStream *S);
};

class hsBounds3 : public hsBounds {
protected:
    Vertex3 min, max;

public:
    hsBounds3();
    ~hsBounds3();

    void read(hsStream *S);
    void write(hsStream *S);
};

class hsBounds3Ext : public hsBounds3 {
protected:
    int Flags;
    hsScalarTriple ST34;
    hsScalarTriple ST40[3];
    float f64[6];

public:
    hsBounds3Ext();
    ~hsBounds3Ext();

    void read(hsStream *S);
    void write(hsStream *S);
};

#endif

