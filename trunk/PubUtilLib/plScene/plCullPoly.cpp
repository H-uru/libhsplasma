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
    prc->writeParam("Flags", fFlags);
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
