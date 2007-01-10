#ifndef _HSSCALARTRIPLE_H
#define _HSSCALARTRIPLE_H

#include "CoreLib/hsStream.h"

class hsScalarTriple {
private:
    float X, Y, Z;

public:
    hsScalarTriple();
    hsScalarTriple(float x, float y, float z);
    ~hsScalarTriple();

    float getX();
    float getY();
    float getZ();
    void setX(float x);
    void setY(float y);
    void setZ(float z);

    void read(hsStream *S);
    void write(hsStream *S);
};

#endif

