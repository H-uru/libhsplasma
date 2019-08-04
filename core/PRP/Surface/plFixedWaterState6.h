/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _PLFIXEDWATERSTATE6_H
#define _PLFIXEDWATERSTATE6_H

#include "Math/hsGeometry3.h"
#include "Sys/hsColor.h"

class PLASMA_DLL plFixedWaterState6
{
public:
    struct PLASMA_DLL WaveState
    {
        float fMaxLength, fMinLength, fAmpOverLen, fChop, fAngleDev;

        WaveState()
            : fMaxLength(), fMinLength(), fAmpOverLen(), fChop(), fAngleDev() { }

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
    plFixedWaterState6()
        : fRippleScale(), fWaterHeight(), fWispiness(), fEdgeOpac(),
          fEdgeRadius(), fPeriod(), fFingerLength(), fEnvRefresh(),
          fEnvRadius() { }

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

public:
    hsVector3 getWaterOffset() const { return fWaterOffset; }
    const WaveState& getGeoState() const { return fGeoState; }
    WaveState& getGeoState() { return fGeoState; }
    const WaveState& getTexState() const { return fTexState; }
    WaveState& getTexState() { return fTexState; }
    float getRippleScale() const { return fRippleScale; }
    float getWaterHeight() const { return fWaterHeight; }
    hsVector3 getWindDir() const { return fWindDir; }
    hsVector3 getSpecVector() const { return fSpecVec; }
    hsVector3 getMaxAtten() const { return fMaxAtten; }
    hsVector3 getMinAtten() const { return fMinAtten; }
    float getWispiness() const { return fWispiness; }
    hsColorRGBA getShoreTint() const { return fShoreTint; }
    hsColorRGBA getMaxColor() const { return fMaxColor; }
    hsColorRGBA getMinColor() const { return fMinColor; }
    float getEdgeOpacity() const { return fEdgeOpac; }
    float getEdgeRadius() const { return fEdgeRadius; }
    float getPeriod() const { return fPeriod; }
    float getFingerLength() const { return fFingerLength; }
    hsVector3 getEnvCenter() const { return fEnvCenter; }
    float getEnvRefresh() const { return fEnvRefresh; }
    float getEnvRadius() const { return fEnvRadius; }

    void setWaterOffset(const hsVector3& offset) { fWaterOffset = offset; }
    void setRippleScale(float scale) { fRippleScale = scale; }
    void setWaterHeight(float height) { fWaterHeight = height; }
    void setWindDir(const hsVector3& dir) { fWindDir = dir; }
    void setSpecVector(const hsVector3& vec) { fSpecVec = vec; }
    void setMaxAtten(const hsVector3& atten) { fMaxAtten = atten; }
    void setMinAtten(const hsVector3& atten) { fMinAtten = atten; }
    void setWispiness(float wispiness) { fWispiness = wispiness; }
    void setShoreTint(const hsColorRGBA& tint) { fShoreTint = tint; }
    void setMaxColor(const hsColorRGBA& color) { fMaxColor = color; }
    void setMinColor(const hsColorRGBA& color) { fMinColor = color; }
    void setEdgeOpacity(float opacity) { fEdgeOpac = opacity; }
    void setEdgeRadius(float radius) { fEdgeRadius = radius; }
    void setPeriod(float period) { fPeriod = period; }
    void setFingerLength(float length) { fFingerLength = length; }
    void setEnvCenter(const hsVector3& center) { fEnvCenter = center; }
    void setEnvRefresh(float refresh) { fEnvRefresh = refresh; }
    void setEnvRadius(float radius) { fEnvRadius = radius; }
};

#endif
