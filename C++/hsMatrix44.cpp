#include <stdio.h>
#include <math.h>
#include "hsMatrix44.h"

hsMatrix44::hsMatrix44() {
    Identity();
}
hsMatrix44::hsMatrix44(hsMatrix44 * init) {
    for (int y=0; y<4; y++)
        for (int x=0; x<4; x++)
            data[y][x] = init->data[y][x];
}

hsMatrix44::~hsMatrix44() { }

void hsMatrix44::Identity() {
    for (int y=0; y<4; y++)
        for (int x=0; x<4; x++)
            if (x == y) data[y][x] = 1;
            else data[y][x] = 0;
}

float& hsMatrix44::operator()(int y, int x) {
    return data[y][x];
}

hsMatrix44& hsMatrix44::operator+(const hsMatrix44 &other) {
    hsMatrix44 * rmat = new hsMatrix44();
    for (int y=0; y<4; y++)
        for (int x=0; x<4; x++)
            rmat->data[y][x] = data[y][x] + other.data[y][x];
    return (*rmat);
}

hsMatrix44& hsMatrix44::operator*(const hsMatrix44 &other) {
    hsMatrix44 * rmat = new hsMatrix44();
    for (int y=0; y<4; y++)
        for (int x=0; x<4; x++)
            rmat->data[y][x] = (data[y][0] * other.data[0][x]) +
                               (data[y][1] * other.data[1][x]) +
                               (data[y][2] * other.data[2][x]) +
                               (data[y][3] * other.data[3][x]);
    return (*rmat);
}

hsMatrix44& hsMatrix44::operator*(const float mult) {
    hsMatrix44 * rmat = new hsMatrix44();
    for (int y=0; y<4; y++)
        for (int x=0; x<4; x++)
            rmat->data[y][x] = data[y][x] * mult;
    return (*rmat);
}

hsMatrix44& hsMatrix44::translate(float x, float y, float z) {
    hsMatrix44 transMat;
    transMat(0, 3) = x;
    transMat(1, 3) = y;
    transMat(2, 3) = z;
    return (*this) * transMat;
}

hsMatrix44& hsMatrix44::scale(float x, float y, float z) {
    hsMatrix44 scaleMat;
    scaleMat(0, 0) = x;
    scaleMat(1, 1) = y;
    scaleMat(2, 2) = z;
    return (*this) * scaleMat;
}

hsMatrix44& hsMatrix44::rotate(float x, float y, float z) {
    // Note: This is only for rotation around the global axes.
    //   You should get Local-To-World coordinates first before using this
    //   function if you want a local axis rotation.
    hsMatrix44 rotMat;
    hsMatrix44 *result = NULL;
    rotMat(1, 1) = cos(x);
    rotMat(1, 2) = sin(x);
    rotMat(2, 1) = -sin(x);
    rotMat(2, 2) = cos(x);
    *result = (*this) * rotMat;
    rotMat.Identity();
    rotMat(0, 0) = cos(y);
    rotMat(0, 2) = -sin(y);
    rotMat(2, 0) = sin(y);
    rotMat(2, 2) = cos(y);
    *result = (*result )* rotMat;
    rotMat.Identity();
    rotMat(0, 0) = cos(z);
    rotMat(0, 1) = sin(z);
    rotMat(1, 0) = -sin(z);
    rotMat(1, 1) = cos(z);
    *result = (*result) * rotMat;
    return (*result);
}

void hsMatrix44::read(hsStream *S) {
    for (int y=0; y<4; y++)
        for (int x=0; x<4; x++)
            data[y][x] = S->readFloat();
}

void hsMatrix44::write(hsStream *S) {
    for (int y=0; y<4; y++)
        for (int x=0; x<4; x++)
            S->writeFloat(data[y][x]);
}

const char* hsMatrix44::toString() {
    char* s = new char[4096];
    sprintf(s, "[ %5.1f %5.1f %5.1f %5.1f\n  %5.1f %5.1f %5.1f %5.1f\n  %5.1f %5.1f %5.1f %5.1f\n  %5.1f %5.1f %5.1f %5.1f ]",
        data[0][0], data[0][1], data[0][2], data[0][3],
        data[1][0], data[1][1], data[1][2], data[1][3],
        data[2][0], data[2][1], data[2][2], data[2][3],
        data[3][0], data[3][1], data[3][2], data[3][3]);
    return s;
}
