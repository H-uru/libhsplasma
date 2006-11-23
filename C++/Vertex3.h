#ifndef _VERTEX3_H
#define _VERTEX3_H

#include "CoreLib/hsStream.h"

class Vertex3 {
private:
    float X, Y, Z;

public:
    Vertex3();
    Vertex3(float x, float y, float z);
    ~Vertex3();

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

