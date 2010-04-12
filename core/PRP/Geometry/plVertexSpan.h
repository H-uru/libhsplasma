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

#ifndef _PLVERTEXSPAN_H
#define _PLVERTEXSPAN_H

#include "plSpan.h"

DllClass plVertexSpan : public plSpan {
public:
    unsigned int fGroupIdx, fVBufferIdx, fCellIdx,
                 fCellOffset, fVStartIdx, fVLength;

public:
    virtual const char* ClassName() const { return "plVertexSpan"; }

    plVertexSpan();
    plVertexSpan(const plVertexSpan& init);

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag);

public:
    unsigned int getGroupIdx() const { return fGroupIdx; }
    unsigned int getVBufferIdx() const { return fVBufferIdx; }
    unsigned int getCellIdx() const { return fCellIdx; }
    unsigned int getCellOffset() const { return fCellOffset; }
    unsigned int getVStartIdx() const { return fVStartIdx; }
    unsigned int getVLength() const { return fVLength; }

    void setGroupIdx(unsigned int idx) { fGroupIdx = idx; }
    void setVBufferIdx(unsigned int idx) { fVBufferIdx = idx; }
    void setCellIdx(unsigned int idx) { fCellIdx = idx; }
    void setCellOffset(unsigned int off) { fCellOffset = off; }
    void setVStartIdx(unsigned int idx) { fVStartIdx = idx; }
    void setVLength(unsigned int len) { fVLength = len; }
};

#endif
