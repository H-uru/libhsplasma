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

#ifndef _PLMORPHDELTA_H
#define _PLMORPHDELTA_H

#include "PRP/plCreatable.h"
#include "Math/hsGeometry3.h"

struct HSPLASMA_EXPORT plVertDelta
{
    unsigned short fIdx, fPadding;
    hsVector3 fPos, fNorm;

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);
};


struct HSPLASMA_EXPORT plMorphSpan
{
    std::vector<plVertDelta> fDeltas;
    unsigned short fNumUVWChans;
    std::vector<hsVector3> fUVWs;

    plMorphSpan() : fNumUVWChans() { }

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);
};


class HSPLASMA_EXPORT plMorphDelta : public plCreatable
{
    CREATABLE(plMorphDelta, kMorphDelta, plCreatable)

protected:
    std::vector<plMorphSpan> fSpans;
    float fWeight;

public:
    plMorphDelta() : fWeight() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    const std::vector<plMorphSpan>& getSpans() const { return fSpans; }
    std::vector<plMorphSpan>& getSpans() { return fSpans; }
    float getWeight() const { return fWeight; }

    void setWeight(float weight) { fWeight = weight; }
};

#endif
