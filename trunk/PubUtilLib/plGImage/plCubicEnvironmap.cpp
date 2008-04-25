#include "plCubicEnvironmap.h"

plCubicEnvironmap::plCubicEnvironmap() { }
plCubicEnvironmap::~plCubicEnvironmap() { }

IMPLEMENT_CREATABLE(plCubicEnvironmap, kCubicEnvironmap, plBitmap)

void plCubicEnvironmap::readData(hsStream* S) {
    plBitmap::readData(S);
    for (int i=0; i<kNumFaces; i++)
        fFaces[i].readData(S);
}

void plCubicEnvironmap::writeData(hsStream* S) {
    plBitmap::writeData(S);
    for (int i=0; i<kNumFaces; i++)
        fFaces[i].writeData(S);
}

void plCubicEnvironmap::IPrcWrite(pfPrcHelper* prc) {
    plBitmap::IPrcWrite(prc);

    prc->writeSimpleTag("Faces");
    for (int i=0; i<kNumFaces; i++)
        fFaces[i].prcWrite(prc);
    prc->closeTag();
}
