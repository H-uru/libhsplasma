#ifndef _VERTEX3_H
#define _VERTEX3_H

#include "CoreLib/hsStream.h"
#include "hsScalarTriple.h"

class Vertex3 {
private:
    float X, Y, Z;

public:
    Vertex3();
    Vertex3(float x, float y, float z);
    Vertex3(Vertex3& other);
    Vertex3(hsScalarTriple& st);
    ~Vertex3();

    float getX();
    float getY();
    float getZ();
    void setX(float x);
    void setY(float y);
    void setZ(float z);

    void Zero();

    Vertex3& operator+(const Vertex3& other);
    Vertex3& operator*(const Vertex3& other);
    Vertex3& operator*(const float mult);
    Vertex3& operator=(const Vertex3& other);
    Vertex3& operator=(hsScalarTriple& st);
    bool operator==(const Vertex3& other);

    void read(hsStream *S);
    void write(hsStream *S);
};

#endif

