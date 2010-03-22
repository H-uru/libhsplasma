#include "plCubicEnvironmap.h"

const char* plCubicEnvironmap::kFaceNames[kNumFaces] = {
    "Left", "Right", "Front", "Back", "Top", "Bottom"
};

plCubicEnvironmap::plCubicEnvironmap() { }
plCubicEnvironmap::~plCubicEnvironmap() { }

IMPLEMENT_CREATABLE(plCubicEnvironmap, kCubicEnvironmap, plBitmap)

void plCubicEnvironmap::read(hsStream* S, plResManager* mgr) {
    plBitmap::read(S, mgr);

    for (int i=0; i<kNumFaces; i++) {
        if (S->getVer() < pvEoa || S->getVer() == pvUniversal) {
            fFaces[i].readData(S);
            fFaces[i].init(getKey()->getName() + "-" + kFaceNames[i]);
        } else {
            fFaces[i].read(S, mgr);
        }
    }
}

void plCubicEnvironmap::write(hsStream* S, plResManager* mgr) {
    plBitmap::write(S, mgr);

    for (int i=0; i<kNumFaces; i++) {
        if (S->getVer() < pvEoa || S->getVer() == pvUniversal)
            fFaces[i].writeData(S);
        else
            fFaces[i].write(S, mgr);
    }
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
