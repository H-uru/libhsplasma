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

#ifndef _PLGRASSSHADERMOD_H
#define _PLGRASSSHADERMOD_H

#include "PRP/Modifier/plModifier.h"

class PLASMA_DLL plGrassWave {
protected:
    float fDistX, fDistY, fDistZ;
    float fDirX, fDirY, fSpeed;

public:
    plGrassWave() : fDistX(0.0f), fDistY(0.0f), fDistZ(0.0f),
                    fDirX(0.0f), fDirY(0.0f), fSpeed(0.0f) { }

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);
};


class PLASMA_DLL plGrassShaderMod : public plModifier {
    CREATABLE(plGrassShaderMod, kGrassShaderMod, plModifier)

public:
    enum { kNumWaves = 4 };

protected:
    plGrassWave fWaves[kNumWaves];
    plKey fMaterial;

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;
};

#endif
