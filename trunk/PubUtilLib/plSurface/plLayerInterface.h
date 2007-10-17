#ifndef _PLLAYERINTERFACE_H
#define _PLLAYERINTERFACE_H

#include "../../NucleusLib/pnNetCommon/plSynchedObject.h"
#include "../../CoreLib/hsColor.h"
#include "../../CoreLib/hsMatrix44.h"
#include "../plGImage/plBitmap.h"
#include "../../NucleusLib/inc/hsGMatState.h"
#include "../plResMgr/plResManager.h"

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
        kUVWIdxMask = 0xFFFFFFFF,
        kUVWNormal = 0x10000,
        kUVWPosition = 0x20000,
        kUVWReflect = 0x30000
    };

protected:
    plKey fUnderLay, fOverLay;
    unsigned int fOwnedChannels, fPassThruChannels;
    hsMatrix44 fTransform;
    hsColorRGBA fPreshadeColor, fRuntimeColor, fAmbientColor, fSpecularColor;
    float fOpacity;
    hsGMatState* fState;
    unsigned int fUVWSrc;
    float fLODBias;
    float fSpecularPower;
    plKey fTexture, fVertexShader, fPixelShader;
    hsMatrix44 fBumpEnvXfm;

public:
    plLayerInterface();
    virtual ~plLayerInterface();

    DECLARE_CREATABLE(plLayerInterface)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
