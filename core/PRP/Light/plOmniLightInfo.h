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

#ifndef _PLOMNILIGHTINFO_H
#define _PLOMNILIGHTINFO_H

#include "plLightInfo.h"

class PLASMA_DLL plOmniLightInfo : public plLightInfo
{
    CREATABLE(plOmniLightInfo, kOmniLightInfo, plLightInfo)

protected:
    float fAttenConst, fAttenLinear, fAttenQuadratic, fAttenCutoff;

public:
    plOmniLightInfo()
        : fAttenConst(), fAttenLinear(), fAttenQuadratic(), fAttenCutoff() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    float getAttenConst() const { return fAttenConst; }
    float getAttenLinear() const { return fAttenLinear; }
    float getAttenQuadratic() const { return fAttenQuadratic; }
    float getAttenCutoff() const { return fAttenCutoff; }

    void setAttenConst(float atten) { fAttenConst = atten; }
    void setAttenLinear(float atten) { fAttenLinear = atten; }
    void setAttenQuadratic(float atten) { fAttenQuadratic = atten; }
    void setAttenCutoff(float cutoff) { fAttenCutoff = cutoff; }
};


class PLASMA_DLL plSpotLightInfo : public plOmniLightInfo
{
    CREATABLE(plSpotLightInfo, kSpotLightInfo, plOmniLightInfo)

protected:
    float fFalloff, fSpotInner, fSpotOuter;

public:
    plSpotLightInfo();

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    float getFalloff() const { return fFalloff; }
    float getSpotInner() const { return fSpotInner; }
    float getSpotOuter() const { return fSpotOuter; }

    void setFalloff(float falloff) { fFalloff = falloff; }
    void setSpotInner(float spot) { fSpotInner = spot; }
    void setSpotOuter(float spot) { fSpotOuter = spot; }
};

#endif
