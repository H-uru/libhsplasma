#ifndef _HSSCALARTRIPLE_H
#define _HSSCALARTRIPLE_H

#include "CoreLib/hsStream.h"

class hsScalarTriple {
private:
    float a, b, c;

public:
    hsScalarTriple();
    hsScalarTriple(float f1, float f2, float f3);
    ~hsScalarTriple();

    void read(hsStream *S);
    void write(hsStream *S);
};

#endif

