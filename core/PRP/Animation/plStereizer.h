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

#ifndef _PLSTEREIZER_H
#define _PLSTEREIZER_H

#include "PRP/Modifier/plModifier.h"
#include "Math/hsGeometry3.h"

class PLASMA_DLL plStereizer : public plSingleModifier
{
    CREATABLE(plStereizer, kStereizer, plSingleModifier)

public:
    enum { kLeftChannel, kHasMaster };

protected:
    float fAmbientDist, fTransition, fMaxSepDist, fMinSepDist, fTanAng;
    hsVector3 fInitPos;

public:
    plStereizer()
        : fAmbientDist(), fTransition(), fMaxSepDist(), fMinSepDist(), fTanAng()
    {
        fFlags.setName(kLeftChannel, "kLeftChannel");
        fFlags.setName(kHasMaster, "kHasMaster");
    }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    float getAmbientDist() const { return fAmbientDist; }
    float getTransition() const { return fTransition; }
    float getMaxSepDist() const { return fMaxSepDist; }
    float getMinSepDist() const { return fMinSepDist; }
    float getTanAng() const { return fTanAng; }
    hsVector3 getInitPos() const { return fInitPos; }

    void setAmbientDist(float dist) { fAmbientDist = dist; }
    void setTransition(float transition) { fTransition = transition; }
    void setSepDist(float min, float max) { fMinSepDist = min; fMaxSepDist = max; }
    void setTanAng(float ang) { fTanAng = ang; }
    void setInitPos(const hsVector3& pos) { fInitPos = pos; }
};

#endif
