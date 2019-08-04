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

#ifndef _PLSHADER_H
#define _PLSHADER_H

#include "PRP/KeyedObject/hsKeyedObject.h"

class PLASMA_DLL plShaderConst
{
public:
    union
    {
        struct { float fR, fG, fB, fA; };
        struct { float fX, fY, fZ, fW; };
        float fArray[4];
    };

public:
    plShaderConst() : fArray() { }
    plShaderConst(float f1, float f2, float f3, float f4)
        : fX(f1), fY(f2), fZ(f3), fW(f4) { }
    plShaderConst(const plShaderConst& init);

    plShaderConst& operator=(const plShaderConst& init);
    float operator[](size_t idx) const { return fArray[idx]; }
    float& operator[](size_t idx) { return fArray[idx]; }

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);
};


class PLASMA_DLL plShader : public hsKeyedObject
{
    CREATABLE(plShader, kShader, hsKeyedObject)

public:
    enum plShaderID
    {
        kUnregistered,
        vs_WaveFixedFin6, ps_WaveFixed, vs_CompCosines, ps_CompCosines,
        vs_ShoreLeave6, ps_ShoreLeave6, vs_WaveRip, ps_WaveRip, vs_WaveDec1Lay,
        vs_WaveDec2Lay11, vs_WaveDec2Lay12, vs_WaveDecEnv, ps_CbaseAbase,
        ps_CalphaAbase, ps_CalphaAMult, ps_CalphaAadd, ps_CaddAbase,
        ps_CaddAMult, ps_CaddAAdd, ps_CmultAbase, ps_CmultAMult, ps_CmultAAdd,
        ps_WaveDecEnv, vs_WaveGraph2, ps_WaveGraph, vs_WaveGridFin, ps_WaveGrid,
        vs_BiasNormals, ps_BiasNormals, vs_ShoreLeave7, vs_WaveRip7,
        ps_MoreCosines, vs_WaveDec1Lay_7, vs_WaveDec2Lay11_7, vs_WaveDec2Lay12_7,
        vs_WaveDecEnv_7, vs_WaveFixedFin7, vs_GrassShader, ps_GrassShader,
        kNumShaders
    };

protected:
    std::vector<plShaderConst> fConsts;
    plShaderID fID;
    unsigned char fInput, fOutput;

public:
    plShader() : fID(kUnregistered), fInput(), fOutput() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    const std::vector<plShaderConst>& getConsts() const { return fConsts; }
    plShaderID getID() const { return fID; }
    unsigned char getInput() const { return fInput; }
    unsigned char getOutput() const { return fOutput; }

    void setConsts(const std::vector<plShaderConst>& consts) { fConsts = consts; }
    void setID(plShaderID id) { fID = id; }
    void setInput(unsigned char input) { fInput = input; }
    void setOutput(unsigned char output) { fOutput = output; }
};

#endif
