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

#include <string_theory/format>

/* plIcicle */
plIcicle::plIcicle(const plIcicle& init)
    : plVertexSpan(init), fIBufferIdx(init.fIBufferIdx),
      fIStartIdx(init.fIStartIdx), fILength(init.fILength),
      fSortData(init.fSortData)
{ }

void plIcicle::read(hsStream* S)
{
    plVertexSpan::read(S);
    if (!S->getVer().isHexIsle()) {
        fIBufferIdx = S->readInt();
        fIStartIdx = S->readInt();
    }
    fILength = S->readInt();
    if (fProps & kPropFacesSortable) {
        fSortData.resize(fILength / 3);
        for (size_t i = 0; i < (fILength / 3); i++)
            fSortData[i].read(S);
    } else {
        fSortData.clear();
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

        fSortData.resize(fILength / 3);
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
    if (data == nullptr) {
        fProps &= ~kPropFacesSortable;
        fSortData.clear();
    } else {
        fProps |= kPropFacesSortable;
        fSortData = std::vector<plGBufferTriangle>(data, data + (fILength / 3));
    }
}

void plIcicle::setSortData(std::vector<plGBufferTriangle> sortData)
{
    if (sortData.empty()) {
        fProps &= ~kPropFacesSortable;
        fSortData.clear();
        return;
    }

    if (sortData.size() != (fILength / 3))
        throw hsBadParamException(__FILE__, __LINE__, ST::format("Expected {} triangles, not {}",
                                  fILength/3, sortData.size()));

    fProps |= kPropFacesSortable;
    fSortData = std::move(sortData);
}

/* plParticleSpan */
void plParticleSpan::IPrcParse(const pfPrcTag* tag)
{
    throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
}
