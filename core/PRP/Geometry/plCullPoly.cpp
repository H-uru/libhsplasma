#include "plCullPoly.h"

plCullPoly::plCullPoly() : fFlags(kNone), fDist(0.0f), fRadius(0.0f) { }
plCullPoly::~plCullPoly() { }

void plCullPoly::read(hsStream* S) {
    fFlags = S->readInt();
    fNorm.read(S);
    fDist = S->readFloat();
    fCenter.read(S);
    fRadius = S->readFloat();

    fVerts.setSize(S->readInt());
    for (size_t i=0; i<fVerts.getSize(); i++)
        fVerts[i].read(S);
}

void plCullPoly::write(hsStream* S) {
    S->writeInt(fFlags);
    fNorm.write(S);
    S->writeFloat(fDist);
    fCenter.write(S);
    S->writeFloat(fRadius);

    S->writeInt(fVerts.getSize());
    for (size_t i=0; i<fVerts.getSize(); i++)
        fVerts[i].write(S);
}

void plCullPoly::prcWrite(pfPrcHelper* prc) {
    prc->startTag("plCullPoly");
    prc->writeParamHex("Flags", fFlags);
    prc->endTag();
    
    prc->startTag("Normal");
    prc->writeParam("Dist", fDist);
    prc->endTag();
    fNorm.prcWrite(prc);
    prc->closeTag();

    prc->startTag("Center");
    prc->writeParam("Radius", fRadius);
    prc->endTag();
    fCenter.prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Verts");
    for (size_t i=0; i<fVerts.getSize(); i++)
        fVerts[i].prcWrite(prc);
    prc->closeTag();
    
    prc->closeTag(); // plCullPoly
}

void plCullPoly::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "plCullPoly")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    fFlags = tag->getParam("Flags", "0").toUint();

    const pfPrcTag* child = tag->getFirstChild();
    while (child != NULL) {
        if (child->getName() == "Normal") {
            fDist = child->getParam("Dist", "0").toFloat();
            if (child->hasChildren())
                fNorm.prcParse(child->getFirstChild());
        } else if (child->getName() == "Center") {
            fRadius = child->getParam("Radius", "0").toFloat();
            if (child->hasChildren())
                fCenter.prcParse(child->getFirstChild());
        } else if (child->getName() == "Verts") {
            fVerts.setSize(child->countChildren());
            const pfPrcTag* vertChild = child->getFirstChild();
            for (size_t i=0; i<fVerts.getSize(); i++) {
                fVerts[i].prcParse(vertChild);
                vertChild = vertChild->getNextSibling();
            }
        } else {
            throw pfPrcTagException(__FILE__, __LINE__, child->getName());
        }
        child = child->getNextSibling();
    }
}

hsTArray<hsVector3> plCullPoly::GetVerts() const {
    return fVerts;
}
