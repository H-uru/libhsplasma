#include <stdio.h>
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

const hsMatrix44& hsMatrix44::operator+(const hsMatrix44 &other) {
    hsMatrix44 rmat;
    for (int y=0; y<4; y++)
        for (int x=0; x<4; x++)
            rmat.data[y][x] = data[y][x] + other.data[y][x];
    return rmat;
}

const hsMatrix44& hsMatrix44::operator*(const hsMatrix44 &other) {
    hsMatrix44 rmat;
    for (int y=0; y<4; y++)
        for (int x=0; x<4; x++)
            rmat.data[y][x] = (data[y][0] * other.data[0][x]) +
                              (data[y][1] * other.data[1][x]) +
                              (data[y][2] * other.data[2][x]) +
                              (data[y][3] * other.data[3][x]);
    return rmat;
}

const hsMatrix44& hsMatrix44::operator*(const float mult) {
    hsMatrix44 rmat;
    for (int y=0; y<4; y++)
        for (int x=0; x<4; x++)
            rmat.data[y][x] = data[y][x] * mult;
    return rmat;
}

const char* hsMatrix44::toString() {
    char* s = new char[4096];
    sprintf(s, "[ %4.1f %4.1f %4.1f %4.1f\n  %4.1f %4.1f %4.1f %4.1f\n  %4.1f %4.1f %4.1f %4.1f\n  %4.1f %4.1f %4.1f %4.1f ]",
        data[0][0], data[0][1], data[0][2], data[0][3],
        data[1][0], data[1][1], data[1][2], data[1][3],
        data[2][0], data[2][1], data[2][2], data[2][3],
        data[3][0], data[3][1], data[3][2], data[3][3]);
    return s;
}
