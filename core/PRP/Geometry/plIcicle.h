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

#ifndef _PLICICLE_H
#define _PLICICLE_H

#include "plGBufferGroup.h"
#include "plVertexSpan.h"

class PLASMA_DLL plIcicle : public plVertexSpan
{
protected:
    unsigned int fIBufferIdx, fIStartIdx, fILength;
    plGBufferTriangle* fSortData;

public:
    const char* ClassName() const HS_OVERRIDE { return "plIcicle"; }

    plIcicle() : fIBufferIdx(), fIStartIdx(), fILength(), fSortData() { }
    plIcicle(const plIcicle& init);
    ~plIcicle();

    void read(hsStream* S) HS_OVERRIDE;
    void write(hsStream* S) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag) HS_OVERRIDE;

public:
    unsigned int getIBufferIdx() const { return fIBufferIdx; }
    unsigned int getIStartIdx() const { return fIStartIdx; }
    unsigned int getILength() const { return fILength; }
    const plGBufferTriangle* getSortData() const { return fSortData; }

    void setIBufferIdx(unsigned int idx) { fIBufferIdx = idx; }
    void setIStartIdx(unsigned int idx) { fIStartIdx = idx; }
    void setILength(unsigned int len) { fILength = len; }
    void setSortData(const plGBufferTriangle* data);
};

class PLASMA_DLL plParticleSpan : public plIcicle
{
public:
    const char* ClassName() const HS_OVERRIDE { return "plParticleSpan"; }

    void read(hsStream*) HS_OVERRIDE { }
    void write(hsStream*) HS_OVERRIDE { }

protected:
    void IPrcWrite(pfPrcHelper*) HS_OVERRIDE { }
    void IPrcParse(const pfPrcTag* tag) HS_OVERRIDE;
};

#endif
