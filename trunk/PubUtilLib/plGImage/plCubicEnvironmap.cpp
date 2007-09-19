#include "plCubicEnvironmap.h"

plCubicEnvironmap::plCubicEnvironmap() { }
plCubicEnvironmap::~plCubicEnvironmap() { }

IMPLEMENT_CREATABLE(plCubicEnvironmap, kCubicEnvironmap, plBitmap)

void plCubicEnvironmap::read(hsStream* S, plResManager* mgr) {
    hsKeyedObject::read(S, mgr);
    readData(S);
}

void plCubicEnvironmap::write(hsStream* S, plResManager* mgr) {
    hsKeyedObject::write(S, mgr);
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
