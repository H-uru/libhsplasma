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

class PLASMA_DLL plIcicle : public plVertexSpan {
protected:
    unsigned int fIBufferIdx, fIStartIdx, fILength;
    plGBufferTriangle* fSortData;

public:
    virtual const char* ClassName() const { return "plIcicle"; }

    plIcicle();
    plIcicle(const plIcicle& init);
    virtual ~plIcicle();

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag);

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

class PLASMA_DLL plParticleSpan : public plIcicle {
public:
    virtual const char* ClassName() const { return "plParticleSpan"; }

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag);
};

#endif
