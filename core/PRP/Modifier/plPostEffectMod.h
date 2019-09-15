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

#ifndef _PLPOSTEFFECTMOD_H
#define _PLPOSTEFFECTMOD_H

#include "plModifier.h"
#include "Math/hsMatrix44.h"

class PLASMA_DLL plPostEffectMod : public plSingleModifier
{
    CREATABLE(plPostEffectMod, kPostEffectMod, plSingleModifier)

public:
    enum plPostEffectModStates { kEnabled };

protected:
    hsBitVector fState;
    float fHither, fYon, fFovX, fFovY;
    plKey fNodeKey;
    hsMatrix44 fDefaultW2C, fDefaultC2W;

public:
    plPostEffectMod() : fHither(1.0f), fYon(100.0f), fFovX(0.7854f), fFovY(0.589f) { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    const hsBitVector& getState() const { return fState; }
    hsBitVector& getState() { return fState; }

    float getHither() const { return fHither; }
    float getYon() const { return fYon; }
    float getFovX() const { return fFovX; }
    float getFovY() const { return fFovY; }
    plKey getNodeKey() const { return fNodeKey; }
    hsMatrix44 getDefaultW2C() const { return fDefaultW2C; }
    hsMatrix44 getDefaultC2W() const { return fDefaultC2W; }

    void setHither(float hither) { fHither = hither; }
    void setYon(float yon) { fYon = yon; }
    void setFovX(float x) { fFovX = x; }
    void setFovY(float y) { fFovY = y; }
    void setFov(float x, float y) { fFovX = x; fFovY = y; }
    void setNodeKey(plKey node) { fNodeKey = std::move(node); }
    void setDefaultW2C(const hsMatrix44& w2c) { fDefaultW2C = w2c; }
    void setDefaultC2W(const hsMatrix44& c2w) { fDefaultC2W = c2w; }
};

#endif
