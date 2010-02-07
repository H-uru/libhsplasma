#ifndef _PLFIXEDWATERSTATE6_H
#define _PLFIXEDWATERSTATE6_H

#include "Math/hsGeometry3.h"
#include "Sys/hsColor.h"

DllClass plFixedWaterState6 {
public:
    DllClass WaveState {
    public:
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
    void prcParse(const pfPrcTag* tag);

    hsVector3 getWaterOffset() const;
    WaveState& getGeoState();
    const WaveState& getGeoState() const;
    WaveState& getTexState();
    const WaveState& getTexState() const;
    float getRippleScale() const;
    float getWaterHeight() const;
    hsVector3 getWindDir() const;
    hsVector3 getSpecVector() const;
    hsVector3 getMaxAtten() const;
    hsVector3 getMinAtten() const;
    float getWispiness() const;
    hsColorRGBA getShoreTint() const;
    hsColorRGBA getMaxColor() const;
    hsColorRGBA getMinColor() const;
    float getEdgeOpacity() const;
    float getEdgeRadius() const;
    float getPeriod() const;
    float getFingerLength() const;
    hsVector3 getEnvCenter() const;
    float getEnvRefresh() const;
    float getEnvRadius() const;

    void setWaterOffset(const hsVector3& offset);
    void setRippleScale(float scale);
    void setWaterHeight(float height);
    void setWindDir(const hsVector3& dir);
    void setSpecVector(const hsVector3& vec);
    void setMaxAtten(const hsVector3& atten);
    void setMinAtten(const hsVector3& atten);
    void setWispiness(float wispiness);
    void setShoreTint(const hsColorRGBA& tint);
    void setMaxColor(const hsColorRGBA& color);
    void setMinColor(const hsColorRGBA& color);
    void setEdgeOpacity(float opacity);
    void setEdgeRadius(float radius);
    void setPeriod(float period);
    void setFingerLength(float length);
    void setEnvCenter(const hsVector3& center);
    void setEnvRefresh(float refresh);
    void setEnvRadius(float radius);
};

#endif
