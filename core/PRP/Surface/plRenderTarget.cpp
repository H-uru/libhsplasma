/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "plRenderTarget.h"

/* plRenderTarget */
void plRenderTarget::read(hsStream* S, plResManager* mgr)
{
    plBitmap::read(S, mgr);
    IReadRenderTarget(S);
}

void plRenderTarget::write(hsStream* S, plResManager* mgr)
{
    plBitmap::write(S, mgr);
    IWriteRenderTarget(S);
}

void plRenderTarget::readData(hsStream* S)
{
    IReadBitmap(S);
    IReadRenderTarget(S);
}

void plRenderTarget::writeData(hsStream* S)
{
    IWriteBitmap(S);
    IWriteRenderTarget(S);
}

void plRenderTarget::IReadRenderTarget(hsStream* S)
{
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

void plRenderTarget::IWriteRenderTarget(hsStream* S)
{
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

void plRenderTarget::IPrcWrite(pfPrcHelper* prc)
{
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

void plRenderTarget::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "RenderTargetParams") {
        fWidth = tag->getParam("Width", "0").to_uint();
        fHeight = tag->getParam("Height", "0").to_uint();
        fZDepth = tag->getParam("ZDepth", "0").to_uint();
        fStencilDepth = tag->getParam("StencilDepth", "0").to_uint();
    } else if (tag->getName() == "Viewport") {
        fProportionalViewport = tag->getParam("Proportional", "false").to_bool();
        if (fProportionalViewport) {
            fViewport.fProportional.fLeft = tag->getParam("Left", "0").to_float();
            fViewport.fProportional.fTop = tag->getParam("Top", "0").to_float();
            fViewport.fProportional.fRight = tag->getParam("Right", "0").to_float();
            fViewport.fProportional.fBottom = tag->getParam("Bottom", "0").to_float();
        } else {
            fViewport.fAbsolute.fLeft = tag->getParam("Left", "0").to_uint();
            fViewport.fAbsolute.fTop = tag->getParam("Top", "0").to_uint();
            fViewport.fAbsolute.fRight = tag->getParam("Right", "0").to_uint();
            fViewport.fAbsolute.fBottom = tag->getParam("Bottom", "0").to_uint();
        }
    } else {
        plBitmap::IPrcParse(tag, mgr);
    }
}


/* plCubicRenderTarget */
void plCubicRenderTarget::read(hsStream* S, plResManager* mgr)
{
    plRenderTarget::read(S, mgr);

    for (size_t i=0; i<6; i++) {
        if (S->getVer().isUru() || S->getVer().isUniversal())
            fFaces[i].readData(S);
        else
            fFaces[i].read(S, mgr);
    }
}

void plCubicRenderTarget::write(hsStream* S, plResManager* mgr)
{
    plRenderTarget::write(S, mgr);

    for (size_t i=0; i<6; i++) {
        if (S->getVer().isUru() || S->getVer().isUniversal())
            fFaces[i].writeData(S);
        else
            fFaces[i].write(S, mgr);
    }
}

void plCubicRenderTarget::IPrcWrite(pfPrcHelper* prc)
{
    plRenderTarget::IPrcWrite(prc);

    prc->writeSimpleTag("Faces");
    for (size_t i=0; i<6; i++)
        fFaces[i].prcWrite(prc);
    prc->closeTag();
}

void plCubicRenderTarget::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
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
