#include "plRenderTarget.h"

/* plRenderTarget */
plRenderTarget::plRenderTarget()
              : fWidth(0), fHeight(0), fProportionalViewport(false),
                fZDepth(0), fStencilDepth(0) { }
plRenderTarget::~plRenderTarget() { }

IMPLEMENT_CREATABLE(plRenderTarget, kRenderTarget, plBitmap)

void plRenderTarget::read(hsStream* S, plResManager* mgr) {
    plBitmap::read(S, mgr);
    IRead(S);
}

void plRenderTarget::write(hsStream* S, plResManager* mgr) {
    plBitmap::write(S, mgr);
    IWrite(S);
}

void plRenderTarget::readData(hsStream* S) {
    plBitmap::IRead(S);
    IRead(S);
}

void plRenderTarget::writeData(hsStream* S) {
    plBitmap::IWrite(S);
    IWrite(S);
}

void plRenderTarget::IRead(hsStream* S) {
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

void plRenderTarget::IWrite(hsStream* S) {
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

void plRenderTarget::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "RenderTargetParams") {
        fWidth = tag->getParam("Width", "0").toUint();
        fHeight = tag->getParam("Height", "0").toUint();
        fZDepth = tag->getParam("ZDepth", "0").toUint();
        fStencilDepth = tag->getParam("StencilDepth", "0").toUint();
    } else if (tag->getName() == "Viewport") {
        fProportionalViewport = tag->getParam("Proportional", "false").toBool();
        if (fProportionalViewport) {
            fViewport.fProportional.fLeft = tag->getParam("Left", "0").toFloat();
            fViewport.fProportional.fTop = tag->getParam("Top", "0").toFloat();
            fViewport.fProportional.fRight = tag->getParam("Right", "0").toFloat();
            fViewport.fProportional.fBottom = tag->getParam("Bottom", "0").toFloat();
        } else {
            fViewport.fAbsolute.fLeft = tag->getParam("Left", "0").toUint();
            fViewport.fAbsolute.fTop = tag->getParam("Top", "0").toUint();
            fViewport.fAbsolute.fRight = tag->getParam("Right", "0").toUint();
            fViewport.fAbsolute.fBottom = tag->getParam("Bottom", "0").toUint();
        }
    } else {
        plBitmap::IPrcParse(tag, mgr);
    }
}


/* plCubicRenderTarget */
plCubicRenderTarget::plCubicRenderTarget() { }
plCubicRenderTarget::~plCubicRenderTarget() { }

IMPLEMENT_CREATABLE(plCubicRenderTarget, kCubicRenderTarget, plRenderTarget)

void plCubicRenderTarget::read(hsStream* S, plResManager* mgr) {
    plRenderTarget::read(S, mgr);

    for (size_t i=0; i<6; i++) {
        if (S->getVer() < pvEoa)
            fFaces[i].readData(S);
        else
            fFaces[i].read(S, mgr);
    }
}

void plCubicRenderTarget::write(hsStream* S, plResManager* mgr) {
    plRenderTarget::write(S, mgr);

    for (size_t i=0; i<6; i++) {
        if (S->getVer() < pvEoa)
            fFaces[i].writeData(S);
        else
            fFaces[i].write(S, mgr);
    }
}

void plCubicRenderTarget::IPrcWrite(pfPrcHelper* prc) {
    plRenderTarget::IPrcWrite(prc);

    prc->writeSimpleTag("Faces");
    for (size_t i=0; i<6; i++)
        fFaces[i].prcWrite(prc);
    prc->closeTag();
}

void plCubicRenderTarget::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Faces") {
        if (tag->countChildren() != 6)
            throw pfPrcParseException(__FILE__, __LINE__, "CubicRenderTarget expects exactly 6 faces");

        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<6; i++) {
            fFaces[i].prcParse(child, mgr);
            child = child->getNextSibling();
        }
    } else {
        plRenderTarget::IPrcParse(tag, mgr);
    }
}
