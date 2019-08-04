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

#include "plVertexSpan.h"

void plVertexSpan::read(hsStream* S)
{
    plSpan::read(S);
    fGroupIdx = S->readInt();
    fVBufferIdx = S->readInt();
    fCellIdx = S->readInt();
    fCellOffset = S->readInt();
    fVStartIdx = S->readInt();
    fVLength = S->readInt();
}

void plVertexSpan::write(hsStream* S)
{
    plSpan::write(S);
    S->writeInt(fGroupIdx);
    S->writeInt(fVBufferIdx);
    S->writeInt(fCellIdx);
    S->writeInt(fCellOffset);
    S->writeInt(fVStartIdx);
    S->writeInt(fVLength);
}

void plVertexSpan::IPrcWrite(pfPrcHelper* prc)
{
    plSpan::IPrcWrite(prc);
    prc->startTag("VertexSpan");
    prc->writeParam("GroupIdx", fGroupIdx);
    prc->writeParam("BufferIdx", fVBufferIdx);
    prc->writeParam("CellIdx", fCellIdx);
    prc->writeParam("CellOffset", fCellOffset);
    prc->writeParam("StartIdx", fVStartIdx);
    prc->writeParam("Length", fVLength);
    prc->endTag(true);
}

void plVertexSpan::IPrcParse(const pfPrcTag* tag)
{
    if (tag->getName() == "VertexSpan") {
        fGroupIdx = tag->getParam("GroupIdx", "0").to_uint();
        fVBufferIdx = tag->getParam("BufferIdx", "0").to_uint();
        fCellIdx = tag->getParam("CellIdx", "0").to_uint();
        fCellOffset = tag->getParam("CellOffset", "0").to_uint();
        fVStartIdx = tag->getParam("StartIdx", "0").to_uint();
        fVLength = tag->getParam("Length", "0").to_uint();
    } else {
        plSpan::IPrcParse(tag);
    }
}
