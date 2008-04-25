#ifndef _PLFIXEDWATERSTATE6_H
#define _PLFIXEDWATERSTATE6_H

#include "CoreLib/hsGeometry3.h"
#include "CoreLib/hsColor.h"

DllClass plFixedWaterState6 {
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
    };

    enum { kNoise, kSpecStart, kSpecEnd };

protected:
    hsVector3 fWaterOffset;
    WaveState fGeoState, fTexState;
    float fRippleScale, fWaterHeight;
    hsVector3 fWindDir, fSpecVec;
    hsVector3 fMaxAtten, fMinAtten;
    float fWispiness;
    hsColorRGBA fShoreTint, fMaxColor, fMinColor;
    float fEdgeOpac, fEdgeRadius, fPeriod, fFingerLength;
    hsVector3 fEnvCenter;
    float fEnvRefresh, fEnvRadius;

public:
    plFixedWaterState6();
    ~plFixedWaterState6();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
};

#endif
