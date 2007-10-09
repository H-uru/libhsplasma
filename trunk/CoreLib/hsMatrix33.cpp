#include "hsMatrix33.h"

float& hsMatrix33::operator()(int y, int x) {
    return data[y][x];
}

void hsMatrix33::read(hsStream* S) {
    for (int y=0; y<3; y++)
        for (int x=0; x<3; x++)
            data[y][x] = S->readFloat();
}

void hsMatrix33::write(hsStream* S) {
    for (int y=0; y<3; y++)
        for (int x=0; x<3; x++)
            S->writeFloat(data[y][x]);
}

void hsMatrix33::prcWrite(pfPrcHelper* prc) {
    prc->writeTagNoBreak("hsMatrix33");
    char buf[1024];
    snprintf(buf, 1024, "[%f,%f,%f ; %f,%f,%f ; %f,%f,%f]",
        data[0][0], data[0][1], data[0][2],
        data[1][0], data[1][1], data[1][2],
        data[2][0], data[2][1], data[2][2]);
    prc->getStream()->writeStr(buf);
    prc->closeTagNoBreak();
}
