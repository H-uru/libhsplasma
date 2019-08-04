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

#ifndef _PLFOGENVIRONMENT_H
#define _PLFOGENVIRONMENT_H

#include "PRP/KeyedObject/hsKeyedObject.h"
#include "Sys/hsColor.h"

class PLASMA_DLL plFogEnvironment : public hsKeyedObject
{
    CREATABLE(plFogEnvironment, kFogEnvironment, hsKeyedObject)

public:
    enum FogType { kLinearFog, kExpFog, kExp2Fog, kNoFog };

    static const char* const FogTypeNames[];

protected:
    unsigned char fType;
    float fStart, fEnd, fDensity;
    hsColorRGBA fColor;

public:
    plFogEnvironment()
        : fType(kLinearFog), fStart(1.0f), fEnd(1000.0f), fDensity(0.5f) { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    unsigned char getType() const { return fType; }
    void setType(unsigned char type) { fType = type; }

    float getStart() const { return fStart; }
    float getEnd() const { return fEnd; }
    float getDensity() const { return fDensity; }
    void setStart(float start) { fStart = start; }
    void setEnd(float end) { fEnd = end; }
    void setDensity(float density) { fDensity = density; }

    hsColorRGBA getColor() const { return fColor; }
    void setColor(const hsColorRGBA& color) { fColor = color; }
};

#endif
