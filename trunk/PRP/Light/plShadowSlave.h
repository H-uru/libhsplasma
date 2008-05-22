#ifndef _PLSHADOWSLAVE_H
#define _PLSHADOWSLAVE_H

#include "PRP/Region/hsBounds.h"
#include "PRP/Misc/plViewTransform.h"
#include "plShadowCaster.h"

DllClass plShadowSlave {
public:
    enum SlaveFlag {
        kObeysLightGroups = 0x1,
        kIncludesChars = 0x2,
        kSelfShadow = 0x4,
        kCastInCameraSpace = 0x8,
        kReverseZ = 0x10,
        kTwoSided = 0x20,
        kReverseCull = 0x40,
        kPositional = 0x80
    };

protected:
    unsigned int fIndex;
    hsMatrix44 fWorldToLight, fLightToWorld;
    hsVector3 fLightPos, fLightDir;
    hsMatrix44 fWorldToTexture;
    hsMatrix44 fCastLUT, fRcvLUT;
    plViewTransform fView;
    float fPower, fBlurScale;
    hsBounds3Ext fCasterWorldBounds, fWorldBounds;
    unsigned int fWidth, fHeight;
    float fAttenDist;
    float fPriority;
    unsigned int flags;
    plShadowCaster* fCaster;
    int fLightIndex, fLightRefIdx, fSelfShadowOn;
};

#endif
