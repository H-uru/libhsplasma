#ifndef _PLLAYERINTERFACE_H
#define _PLLAYERINTERFACE_H

#include "PRP/Object/plSynchedObject.h"
#include "Sys/hsColor.h"
#include "Math/hsMatrix44.h"
#include "plBitmap.h"
#include "hsGMatState.h"

DllClass plLayerInterface : public plSynchedObject {
public:
    enum plLayerDirtyBits {
        kTransform = 0x1,
        kPreshadeColor = 0x2,
        kAmbientColor = 0x4,
        kOpacity = 0x8,
        kTexture = 0x10,
        kState = 0x20,
        kUVWSrc = 0x40,
        kLODBias = 0x80,
        kSpecularColor = 0x100,
        kSpecularPower = 0x200,
        kRuntimeColor = 0x400,
        kVertexShader = 0x800,
        kPixelShader = 0x1000,
        kBumpEnvXfm = 0x2000,
        kAllDirty = 0xFF
    };
    
    enum plUVWSrcModifiers {
        kUVWPassThru = 0,
        kUVWIdxMask = 0xFFFF,
        kUVWNormal = 0x10000,
        kUVWPosition = 0x20000,
        kUVWReflect = 0x30000
    };

protected:
    plKey fUnderLay;
    hsMatrix44 fTransform;
    hsColorRGBA fPreshade, fRuntime, fAmbient, fSpecular;
    float fOpacity;
    unsigned int fUVWSrc;
    float fLODBias;
    float fSpecularPower;
    plKey fTexture, fVertexShader, fPixelShader;
    hsMatrix44 fBumpEnvXfm;
    hsGMatState fState;

public:
    plLayerInterface();
    virtual ~plLayerInterface();

    DECLARE_CREATABLE(plLayerInterface)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plKey getUnderLay() const;
    plKey getTexture() const;
    plKey getVertexShader() const;
    plKey getPixelShader() const;
    void setUnderLay(plKey layer);
    void setTexture(plKey tex);
    void setVertexShader(plKey shader);
    void setPixelShader(plKey shader);

    hsMatrix44 getTransform() const;
    hsMatrix44 getBumpEnvTransform() const;
    void setTransform(const hsMatrix44& xform);
    void setBumpEnvTransform(const hsMatrix44& xform);

    hsColorRGBA getPreshade() const;
    hsColorRGBA getRuntime() const;
    hsColorRGBA getAmbient() const;
    hsColorRGBA getSpecular() const;
    void setPreshade(const hsColorRGBA& color);
    void setRuntime(const hsColorRGBA& color);
    void setAmbient(const hsColorRGBA& color);
    void setSpecular(const hsColorRGBA& color);

    float getOpacity() const;
    unsigned int getUVWSrc() const;
    float getLODBias() const;
    float getSpecularPower() const;
    void setOpacity(float opac);
    void setUVWSrc(unsigned int src);
    void setLODBias(float bias);
    void setSpecularPower(float power);

    hsGMatState& getState();
};

#endif
