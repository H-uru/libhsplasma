#ifndef _PLSPAN_H
#define _PLSPAN_H

#include "../../CoreLib/hsMatrix44.h"
#include "../../CoreLib/hsStream.h"
#include "../../CoreLib/hsBounds.h"

class plSpan {
private:
    int DrawableType, MatIndex;
    hsMatrix44 LocalToWorld, WorldToLocal;
    int Flags;
    hsBounds3Ext bounds1, bounds2;
    int c98, i94;
    short s9A, s9C, s9E;
    float Dist1, Dist2;
    float f1B0;

public:
    plSpan();
    ~plSpan();

    void read(hsStream *S);
    void write(hsStream *S);
};

#endif

