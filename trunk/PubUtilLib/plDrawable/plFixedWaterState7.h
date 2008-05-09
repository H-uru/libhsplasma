#ifndef _PLFIXEDWATERSTATE7_H
#define _PLFIXEDWATERSTATE7_H

#include "CoreLib/hsGeometry3.h"
#include "CoreLib/hsColor.h"

DllClass plFixedWaterState7 {
public:
    DllClass WaveState {
    protected:
        float fMaxLength, fMinLength, fAmpOverLen, fChop, fAngleDev;

    public:
        WaveState();
        ~WaveState();
        
        void read(hsStream* S);
        void write(hsStream* S);
        void prcWrite(pfPrcHelper* prc);
        void prcParse(const pfPrcTag* tag);
    };

    enum { kNoise, kSpecStart, kSpecEnd };

protected:
    WaveState fGeoState, fTexState;
    float fRippleScale, fWaterHeight;
    hsVector3 fWindDir, fSpecVec, fWaterOffset;
    hsVector3 fMaxAtten, fMinAtten, fDepthFalloff;
    float fWispiness;
    hsColorRGBA fShoreTint, fMaxColor, fMinColor;
    float fEdgeOpac, fEdgeRadius, fPeriod, fFingerLength;
    hsColorRGBA fWaterTint, fSpecularTint;
    hsVector3 fEnvCenter;
    float fEnvRefresh, fEnvRadius;

public:
    plFixedWaterState7();
    ~plFixedWaterState7();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);
};

#endif
