#ifndef _PLPARTICLESYSTEM_H
#define _PLPARTICLESYSTEM_H

#include "PRP/Object/plSynchedObject.h"
#include "PRP/Animation/plController.h"
#include "plParticleEmitter.h"

DllClass plParticleSystem : public plSynchedObject {
public:
    enum EffectType {
        kEffectForce = 0x1,
        kEffectMisc = 0x2,
        kEffectConstraint = 0x4
    };

    enum MiscFlags {
        kParticleSystemAlwaysUpdate = 0x1
    };

protected:
    plKey fMaterial;
    unsigned int fXTiles, fYTiles;
    hsVector3 fAccel;
    float fPreSim, fDrag, fWindMult;
    unsigned int fMaxTotalParticles, fNumValidEmitters, fMaxEmitters;
    hsTArray<plParticleEmitter*> fEmitters;
    hsTArray<plKey> fForces, fEffects, fConstraints;
    hsTArray<plKey> fPermaLights;
    plController* fAmbientCtl;
    plController* fDiffuseCtl;
    plController* fOpacityCtl;
    plController* fWidthCtl;
    plController* fHeightCtl;

public:
    plParticleSystem();
    virtual ~plParticleSystem();

    DECLARE_CREATABLE(plParticleSystem)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plKey getMaterial() const;
    unsigned int getXTiles() const;
    unsigned int getYTiles() const;
    hsVector3 getAccel() const;
    float getPreSim() const;
    float getDrag() const;
    float getWindMult() const;
    unsigned int getMaxTotalParticles() const;
    plController* getAmbientCtl() const;
    plController* getDiffuseCtl() const;
    plController* getOpacityCtl() const;
    plController* getWidthCtl() const;
    plController* getHeightCtl() const;

    void setMaterial(plKey mat);
    void setTiles(unsigned int xtiles, unsigned int ytiles);
    void setAccel(const hsVector3& accel);
    void setPreSim(float preSim);
    void setDrag(float drag);
    void setWindMult(float windMult);
    void setMaxTotalParticles(unsigned int max);
    void setAmbientCtl(plController* ctl);
    void setDiffuseCtl(plController* ctl);
    void setOpacityCtl(plController* ctl);
    void setWidthCtl(plController* ctl);
    void setHeightCtl(plController* ctl);

    unsigned int getNumValidEmitters() const;
    unsigned int getMaxEmitters() const;
    void setMaxEmitters(unsigned int max);
    plParticleEmitter* getEmitter(size_t idx) const;
    void addEmitter(plParticleEmitter* emitter);
    void delEmitter(size_t idx);
    void clearEmitters();

    size_t getNumForces() const;
    plKey getForce(size_t idx) const;
    void addForce(plKey force);
    void delForce(size_t idx);
    void clearForces();

    size_t getNumEffects() const;
    plKey getEffect(size_t idx) const;
    void addEffect(plKey effect);
    void delEffect(size_t idx);
    void clearEffects();

    size_t getNumConstraints() const;
    plKey getConstraint(size_t idx) const;
    void addConstraint(plKey constraint);
    void delConstraint(size_t idx);
    void clearConstraints();

    size_t getNumPermaLights() const;
    plKey getPermaLight(size_t idx) const;
    void addPermaLight(plKey light);
    void delPermaLight(size_t idx);
    void clearPermaLights();
};

#endif
