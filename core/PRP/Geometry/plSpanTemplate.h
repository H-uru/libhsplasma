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

#ifndef _PLSPANTEMPLATE_H
#define _PLSPANTEMPLATE_H

#include "Math/hsGeometry3.h"

class PLASMA_DLL plSpanTemplate
{
public:
    enum
    {
        kPosMask = 0x1,
        kNormMask = 0x2,
        kColorMask = 0x4,
        kWgtIdxMask = 0x8,
        kUVWMask = 0xF0,
        kWeightMask = 0x300,
        kColor2Mask = 0x400
    };

    struct PLASMA_DLL Vertex
    {
        hsVector3 fPosition, fNormal;
        unsigned int fColor1, fColor2;
        int fWeightIdx;
        hsVector3 fUVWs[10];
        float fWeights[3];
    };

protected:
    unsigned short fNumVerts, fNumTris, fFormat, fStride;
    unsigned char* fData;
    unsigned short* fIndices;

public:
    plSpanTemplate()
        : fNumVerts(), fNumTris(), fFormat(), fStride(), fData(), fIndices() { }
    ~plSpanTemplate();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

private:
    static unsigned short CalcStride(unsigned short format);

public:
    unsigned short getNumVerts() const { return fNumVerts; }
    std::vector<Vertex> getVertices() const;
    void setVertices(const std::vector<Vertex>& verts);

    unsigned short getNumTris() const { return fNumTris; }
    const unsigned short* getIndices() const { return fIndices; }
    void setIndices(unsigned short count, const unsigned short* indices);

    unsigned short getFormat() const { return fFormat; }
    void setFormat(unsigned short fmt);
};

#endif
