#ifndef _PLGRASSSHADERMOD_H
#define _PLGRASSSHADERMOD_H

#include "PRP/Modifier/plModifier.h"

DllClass plGrassWave {
protected:
    float fDistX, fDistY, fDistZ;
    float fDirX, fDirY, fSpeed;

public:
    plGrassWave();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);
};

DllClass plGrassShaderMod : public plModifier {
public:
    enum { kNumWaves = 4 };

protected:
    plGrassWave fWaves[kNumWaves];
    plKey fMaterial;

public:
    plGrassShaderMod();
    virtual ~plGrassShaderMod();

    DECLARE_CREATABLE(plGrassShaderMod)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
