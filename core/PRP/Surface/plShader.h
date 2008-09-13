#ifndef _PLSHADER_H
#define _PLSHADER_H

#include "PRP/KeyedObject/hsKeyedObject.h"

DllClass plShaderConst {
public:
    union {
        struct { float fR, fG, fB, fA; };
        struct { float fX, fY, fZ, fW; };
        float fArray[4];
    };

public:
    plShaderConst();
    plShaderConst(float f1, float f2, float f3, float f4);
    plShaderConst(const plShaderConst& init);

    plShaderConst& operator=(const plShaderConst& init);
    float& operator[](size_t idx);

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);
};

DllClass plShader : public hsKeyedObject {
public:
    enum plShaderID {
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
    hsTArray<plShaderConst> fConsts;
    plShaderID fID;
    unsigned char fInput, fOutput;

public:
    plShader();
    virtual ~plShader();

    DECLARE_CREATABLE(plShader)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

    size_t getNumConsts() const;
    plShaderConst getConst(size_t idx) const;
    void clearConsts();
    void addConst(const plShaderConst& sc);

    plShaderID getID() const;
    unsigned char getInput() const;
    unsigned char getOutput() const;
    void setID(plShaderID id);
    void setInput(unsigned char input);
    void setOutput(unsigned char output);
};

#endif
