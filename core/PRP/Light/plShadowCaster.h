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

#ifndef _PLSHADOWCASTER_H
#define _PLSHADOWCASTER_H

#include "PRP/Modifier/plModifier.h"
#include "PRP/Geometry/plDrawableSpans.h"

class PLASMA_DLL plShadowCaster : public plMultiModifier
{
    CREATABLE(plShadowCaster, kShadowCaster, plMultiModifier)

public:
    struct PLASMA_DLL DrawSpan
    {
        plDrawableSpans* fDraw;
        plSpan* fSpan;
        unsigned int fIndex;
    };

    enum
    {
        kNone = 0,
        kSelfShadow = 0x1,
        kPerspective = 0x2,
        kLimitRes = 0x4
    };

protected:
    unsigned char fCastFlags;
    float fBoost, fAttenScale, fBlurScale, fMaxOpacity;

public:
    plShadowCaster()
        : fCastFlags(), fBoost(), fAttenScale(), fBlurScale(), fMaxOpacity() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    unsigned char getCastFlags() const { return fCastFlags; }
    float getBoost() const { return fBoost; }
    float getAttenScale() const { return fAttenScale; }
    float getBlurScale() const { return fBlurScale; }
    float getMaxOpacity() const { return fMaxOpacity; }

    void setCastFlags(unsigned char flags) { fCastFlags = flags; }
    void setBoost(float boost) { fBoost = boost; }
    void setAttenScale(float scale) { fAttenScale = scale; }
    void setBlurScale(float scale) { fBlurScale = scale; }
    void setMaxOpacity(float opacity) { fMaxOpacity = opacity; }
};

#endif
