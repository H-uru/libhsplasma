#include "plCubicEnvironmap.h"

plCubicEnvironmap::plCubicEnvironmap() { }
plCubicEnvironmap::~plCubicEnvironmap() { }

short plCubicEnvironmap::ClassIndex() { return kCubicEnvironmap; }
short plCubicEnvironmap::ClassIndex(PlasmaVer ver) {
    return pdUnifiedTypeMap::MappedToPlasma(kCubicEnvironmap, ver);
}

void plCubicEnvironmap::read(hsStream* S) {
    hsKeyedObject::read(S);
    readData(S);
}

void plCubicEnvironmap::write(hsStream* S) {
    hsKeyedObject::write(S);
    writeData(S);
}

void plCubicEnvironmap::readData(hsStream* S) {
    plBitmap::readData(S);
    for (int i=0; i<6; i++)
        faces[i].readData(S);
}

void plCubicEnvironmap::writeData(hsStream* S) {
    plBitmap::writeData(S);
    for (int i=0; i<6; i++)
        faces[i].writeData(S);
}
