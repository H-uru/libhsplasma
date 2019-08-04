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

#ifndef _PLSPANINSTANCE_H
#define _PLSPANINSTANCE_H

#include "Stream/pfPrcHelper.h"
#include "Stream/pfPrcParser.h"
#include "Math/hsGeometry3.h"
#include "Math/hsMatrix44.h"

class PLASMA_DLL plSpanEncoding
{
public:
    enum
    {
        kPosNone = 0,
        kPos888 = 0x1,
        kPos161616 = 0x2,
        kPos101010 = 0x4,
        kPos008 = 0x8,
        kPosMask = kPos888 | kPos161616 | kPos101010 | kPos008,

        kColNone = 0,
        kColA8 = 0x10,
        kColI8 = 0x20,
        kColAI88 = 0x40,
        kColRGB888 = 0x80,
        kColARGB8888 = 0x100,
        kColMask = kColA8 | kColI8 | kColAI88 | kColRGB888 | kColARGB8888
    };

protected:
    unsigned int fCode;
    float fPosScale;

public:
    plSpanEncoding() : fCode(), fPosScale() { }

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

public:
    unsigned int getCode() const { return fCode; }
    float getPosScale() const { return fPosScale; }

    void setCode(unsigned int code) { fCode = code; }
    void setPosScale(float scale) { fPosScale = scale; }
};


class PLASMA_DLL plSpanInstance
{
protected:
    unsigned char* fPosDelta;
    unsigned char* fCol;
    float fL2W[3][4];   // OpenGL ordering

    plSpanEncoding fEncoding;
    unsigned int fNumVerts;

public:
    plSpanInstance() : fPosDelta(), fCol(), fL2W(), fNumVerts() { }
    ~plSpanInstance();

    void read(hsStream* S, const plSpanEncoding& encoding, unsigned int numVerts);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag, const plSpanEncoding& encoding, unsigned int numVerts);

private:
    static unsigned int CalcPosStride(const plSpanEncoding& encoding);
    static unsigned int CalcColStride(const plSpanEncoding& encoding);

public:
    std::vector<hsVector3> getPosDeltas() const;
    std::vector<unsigned int> getColors() const;
    hsMatrix44 getLocalToWorld() const;

    void setPosDeltas(const std::vector<hsVector3>& verts);
    void setColors(const std::vector<unsigned int>& colors);
    void setLocalToWorld(const hsMatrix44& l2w);
};

#endif
