#ifndef _PLFIXEDWATERSTATE7_H
#define _PLFIXEDWATERSTATE7_H

#include "Math/hsGeometry3.h"
#include "Sys/hsColor.h"

DllClass plFixedWaterState7 {
public:
    DllStruct WaveState {
        float fMaxLength, fMinLength, fAmpOverLen, fChop, fAngleDev;

        WaveState();

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

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

public:
    const WaveState& getGeoState() const { return fGeoState; }
    WaveState& getGeoState() { return fGeoState; }
    const WaveState& getTexState() const { return fTexState; }
    WaveState& getTexState() { return fTexState; }
    float getRippleScale() const { return fRippleScale; }
    float getWaterHeight() const { return fWaterHeight; }
    hsVector3 getWindDir() const { return fWindDir; }
    hsVector3 getSpecVector() const { return fSpecVec; }
    hsVector3 getWaterOffset() const { return fWaterOffset; }
    hsVector3 getMaxAtten() const { return fMaxAtten; }
    hsVector3 getMinAtten() const { return fMinAtten; }
    hsVector3 getDepthFalloff() const { return fDepthFalloff; }
    float getWispiness() const { return fWispiness; }
    hsColorRGBA getShoreTint() const { return fShoreTint; }
    hsColorRGBA getMaxColor() const { return fMaxColor; }
    hsColorRGBA getMinColor() const { return fMinColor; }
    float getEdgeOpacity() const { return fEdgeOpac; }
    float getEdgeRadius() const { return fEdgeRadius; }
    float getPeriod() const { return fPeriod; }
    float getFingerLength() const { return fFingerLength; }
    hsColorRGBA getWaterTint() const { return fWaterTint; }
    hsColorRGBA getSpecularTint() const { return fSpecularTint; }
    hsVector3 getEnvCenter() const { return fEnvCenter; }
    float getEnvRefresh() const { return fEnvRefresh; }
    float getEnvRadius() const { return fEnvRadius; }

    void setRippleScale(float scale) { fRippleScale = scale; }
    void setWaterHeight(float height) { fWaterHeight = height; }
    void setWindDir(const hsVector3& dir) { fWindDir = dir; }
    void setSpecVector(const hsVector3& vec) { fSpecVec = vec; }
    void setWaterOffset(const hsVector3& offset) { fWaterOffset = offset; }
    void setMaxAtten(const hsVector3& atten) { fMaxAtten = atten; }
    void setMinAtten(const hsVector3& atten) { fMinAtten = atten; }
    void setDepthFalloff(const hsVector3& falloff) { fDepthFalloff = falloff; }
    void setWispiness(float wispiness) { fWispiness = wispiness; }
    void setShoreTint(const hsColorRGBA& tint) { fShoreTint = tint; }
    void setMaxColor(const hsColorRGBA& color) { fMaxColor = color; }
    void setMinColor(const hsColorRGBA& color) { fMinColor = color; }
    void setEdgeOpacity(float opacity) { fEdgeOpac = opacity; }
    void setEdgeRadius(float radius) { fEdgeRadius = radius; }
    void setPeriod(float period) { fPeriod = period; }
    void setFingerLength(float length) { fFingerLength = length; }
    void setWaterTint(const hsColorRGBA& tint) { fWaterTint = tint; }
    void setSpecularTint(const hsColorRGBA& tint) { fSpecularTint = tint; }
    void setEnvCenter(const hsVector3& center) { fEnvCenter = center; }
    void setEnvRefresh(float refresh) { fEnvRefresh = refresh; }
    void setEnvRadius(float radius) { fEnvRadius = radius; }
};

#endif
