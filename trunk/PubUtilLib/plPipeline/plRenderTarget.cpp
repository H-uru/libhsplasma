#include "plRenderTarget.h"

/* plRenderTarget */
plRenderTarget::plRenderTarget()
              : fWidth(0), fHeight(0), fApplyTexQuality(false),
                fProportionalViewport(false), fZDepth(0), fStencilDepth(0),
                fParent(NULL) { }
plRenderTarget::~plRenderTarget() { }

IMPLEMENT_CREATABLE(plRenderTarget, kRenderTarget, plBitmap)

void plRenderTarget::readData(hsStream* S) {
    plBitmap::readData(S);

    fWidth = S->readShort();
    fHeight = S->readShort();
    fProportionalViewport = S->readBool();
    if (fProportionalViewport) {
        fViewport.fProportional.fLeft = S->readFloat();
        fViewport.fProportional.fTop = S->readFloat();
        fViewport.fProportional.fRight = S->readFloat();
        fViewport.fProportional.fBottom = S->readFloat();
    } else {
        fViewport.fAbsolute.fLeft = S->readShort();
        fViewport.fAbsolute.fTop = S->readShort();
        fViewport.fAbsolute.fRight = S->readShort();
        fViewport.fAbsolute.fBottom = S->readShort();
    }
    fZDepth = S->readByte();
    fStencilDepth = S->readByte();
}

void plRenderTarget::writeData(hsStream* S) {
    plBitmap::writeData(S);

    S->writeShort(fWidth);
    S->writeShort(fHeight);
    S->writeBool(fProportionalViewport);
    if (fProportionalViewport) {
        S->writeFloat(fViewport.fProportional.fLeft);
        S->writeFloat(fViewport.fProportional.fTop);
        S->writeFloat(fViewport.fProportional.fRight);
        S->writeFloat(fViewport.fProportional.fBottom);
    } else {
        S->writeShort(fViewport.fAbsolute.fLeft);
        S->writeShort(fViewport.fAbsolute.fTop);
        S->writeShort(fViewport.fAbsolute.fRight);
        S->writeShort(fViewport.fAbsolute.fBottom);
    }
    S->writeByte(fZDepth);
    S->writeByte(fStencilDepth);
}

void plRenderTarget::IPrcWrite(pfPrcHelper* prc) {
    plBitmap::IPrcWrite(prc);

    prc->startTag("RenderTargetParams");
    prc->writeParam("Width", fWidth);
    prc->writeParam("Height", fHeight);
    prc->writeParam("ZDepth", fZDepth);
    prc->writeParam("StencilDepth", fStencilDepth);
    prc->endTag(true);

    prc->startTag("Viewport");
    prc->writeParam("Proportional", fProportionalViewport);
    if (fProportionalViewport) {
        prc->writeParam("Left", fViewport.fProportional.fLeft);
        prc->writeParam("Top", fViewport.fProportional.fTop);
        prc->writeParam("Right", fViewport.fProportional.fRight);
        prc->writeParam("Bottom", fViewport.fProportional.fBottom);
    } else {
        prc->writeParam("Left", fViewport.fAbsolute.fLeft);
        prc->writeParam("Top", fViewport.fAbsolute.fTop);
        prc->writeParam("Right", fViewport.fAbsolute.fRight);
        prc->writeParam("Bottom", fViewport.fAbsolute.fBottom);
    }
    prc->endTag(true);
}

plCubicRenderTarget* plRenderTarget::getParent() const { return fParent; }
void plRenderTarget::setParent(plCubicRenderTarget* parent) { fParent = parent; }


/* plCubicRenderTarget */
plCubicRenderTarget::plCubicRenderTarget() {
    for (size_t i=0; i<6; i++)
        fFaces[i] = NULL;
}

plCubicRenderTarget::~plCubicRenderTarget() {
    for (size_t i=0; i<6; i++)
        if (fFaces[i] != NULL)
            delete fFaces[i];
}

IMPLEMENT_CREATABLE(plCubicRenderTarget, kCubicRenderTarget, plRenderTarget)

void plCubicRenderTarget::readData(hsStream* S) {
    plRenderTarget::readData(S);

    for (size_t i=0; i<6; i++) {
        fFaces[i] = new plRenderTarget();
        fFaces[i]->setParent(this);
        fFaces[i]->readData(S);
    }
}

void plCubicRenderTarget::writeData(hsStream* S) {
    plRenderTarget::writeData(S);

    for (size_t i=0; i<6; i++)
        fFaces[i]->writeData(S);
}

void plCubicRenderTarget::IPrcWrite(pfPrcHelper* prc) {
    plRenderTarget::IPrcWrite(prc);

    prc->writeSimpleTag("Faces");
    for (size_t i=0; i<6; i++)
        fFaces[i]->prcWrite(prc);
    prc->closeTag();
}
