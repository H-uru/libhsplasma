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

void plCubicEnvironmap::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Faces") {
        if (tag->countChildren() != kNumFaces)
            throw pfPrcParseException(__FILE__, __LINE__, "plCubicEnvironmap expects exactly 6 faces");
        const pfPrcTag* face = tag->getFirstChild();
        for (size_t i=0; i<kNumFaces; i++) {
            fFaces[i].prcParse(face, mgr);
            face = face->getNextSibling();
        }
    } else {
        plBitmap::IPrcParse(tag, mgr);
    }
}

plMipmap* plCubicEnvironmap::getFace(size_t idx) {
    return &fFaces[idx];
}
