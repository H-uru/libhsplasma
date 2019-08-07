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

#include "plIcicle.h"

/* plIcicle */
plIcicle::plIcicle(const plIcicle& init)
    : plVertexSpan(init), fIBufferIdx(init.fIBufferIdx),
      fIStartIdx(init.fIStartIdx), fILength(init.fILength)
{
    if (fProps & kPropFacesSortable) {
        fSortData = new plGBufferTriangle[fILength / 3];
        for (size_t i=0; i<(fILength / 3); i++)
            fSortData[i] = init.fSortData[i];
    } else {
        fSortData = nullptr;
    }
}

plIcicle::~plIcicle()
{
    delete[] fSortData;
}

void plIcicle::read(hsStream* S)
{
    plVertexSpan::read(S);
    if (!S->getVer().isHexIsle()) {
        fIBufferIdx = S->readInt();
        fIStartIdx = S->readInt();
    }
    fILength = S->readInt();
    if (fProps & kPropFacesSortable) {
        delete[] fSortData;
        fSortData = new plGBufferTriangle[fILength / 3];
        for (size_t i=0; i<(fILength / 3); i++)
            fSortData[i].read(S);
    } else {
        fSortData = nullptr;
    }
}

void plIcicle::write(hsStream* S)
{
    plVertexSpan::write(S);
    if (!S->getVer().isHexIsle()) {
        S->writeInt(fIBufferIdx);
        S->writeInt(fIStartIdx);
    }
    S->writeInt(fILength);
    if (fProps & kPropFacesSortable) {
        for (size_t i=0; i<(fILength / 3); i++)
            fSortData[i].write(S);
    }
}

void plIcicle::IPrcWrite(pfPrcHelper* prc)
{
    plVertexSpan::IPrcWrite(prc);
    prc->startTag("Icicle");
    prc->writeParam("BufferIdx", fIBufferIdx);
    prc->writeParam("StartIdx", fIStartIdx);
    prc->writeParam("Length", fILength);
    prc->endTag(true);
    if (fProps & kPropFacesSortable) {
        prc->writeSimpleTag("SortData");
        for (size_t i=0; i<(fILength / 3); i++)
            fSortData[i].prcWrite(prc);
        prc->closeTag();
    }
}

void plIcicle::IPrcParse(const pfPrcTag* tag)
{
    if (tag->getName() == "Icicle") {
        fIBufferIdx = tag->getParam("BufferIdx", "0").to_uint();
        fIStartIdx = tag->getParam("StartIdx", "0").to_uint();
        fILength = tag->getParam("Length", "0").to_uint();
    } else if (tag->getName() == "SortData") {
        if (tag->countChildren() != (fILength / 3))
            throw pfPrcParseException(__FILE__, __LINE__, "SortData should have exactly Length/3 triangles");
        delete[] fSortData;
        fSortData = new plGBufferTriangle[fILength / 3];
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<(fILength / 3); i++) {
            fSortData[i].prcParse(child);
            child = child->getNextSibling();
        }
    } else {
        plVertexSpan::IPrcParse(tag);
    }
}

void plIcicle::setSortData(const plGBufferTriangle* data)
{
    delete[] fSortData;
    if (data == nullptr) {
        fProps &= ~kPropFacesSortable;
        fSortData = nullptr;
    } else {
        fProps |= kPropFacesSortable;
        fSortData = new plGBufferTriangle[fILength / 3];
        for (size_t i=0; i<(fILength / 3); i++)
            fSortData[i] = data[i];
    }
}


/* plParticleSpan */
void plParticleSpan::IPrcParse(const pfPrcTag* tag)
{
    throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
}
