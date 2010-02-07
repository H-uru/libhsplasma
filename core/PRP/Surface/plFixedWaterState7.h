#ifndef _PLFIXEDWATERSTATE7_H
#define _PLFIXEDWATERSTATE7_H

#include "Math/hsGeometry3.h"
#include "Sys/hsColor.h"

DllClass plFixedWaterState7 {
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

    WaveState& getGeoState();
    const WaveState& getGeoState() const;
    WaveState& getTexState();
    const WaveState& getTexState() const;
    float getRippleScale() const;
    float getWaterHeight() const;
    hsVector3 getWindDir() const;
    hsVector3 getSpecVector() const;
    hsVector3 getWaterOffset() const;
    hsVector3 getMaxAtten() const;
    hsVector3 getMinAtten() const;
    hsVector3 getDepthFalloff() const;
    float getWispiness() const;
    hsColorRGBA getShoreTint() const;
    hsColorRGBA getMaxColor() const;
    hsColorRGBA getMinColor() const;
    float getEdgeOpacity() const;
    float getEdgeRadius() const;
    float getPeriod() const;
    float getFingerLength() const;
    hsColorRGBA getWaterTint() const;
    hsColorRGBA getSpecularTint() const;
    hsVector3 getEnvCenter() const;
    float getEnvRefresh() const;
    float getEnvRadius() const;

    void setRippleScale(float scale);
    void setWaterHeight(float height);
    void setWindDir(const hsVector3& dir);
    void setSpecVector(const hsVector3& vec);
    void setWaterOffset(const hsVector3& offset);
    void setMaxAtten(const hsVector3& atten);
    void setMinAtten(const hsVector3& atten);
    void setDepthFalloff(const hsVector3& falloff);
    void setWispiness(float wispiness);
    void setShoreTint(const hsColorRGBA& tint);
    void setMaxColor(const hsColorRGBA& color);
    void setMinColor(const hsColorRGBA& color);
    void setEdgeOpacity(float opacity);
    void setEdgeRadius(float radius);
    void setPeriod(float period);
    void setFingerLength(float length);
    void setWaterTint(const hsColorRGBA& tint);
    void setSpecularTint(const hsColorRGBA& tint);
    void setEnvCenter(const hsVector3& center);
    void setEnvRefresh(float refresh);
    void setEnvRadius(float radius);
};

#endif
