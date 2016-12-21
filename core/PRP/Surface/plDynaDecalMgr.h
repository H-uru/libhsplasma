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

#ifndef _PLDYNADECALMGR_H
#define _PLDYNADECALMGR_H

#include "PRP/Object/plSynchedObject.h"
#include "Math/hsGeometry3.h"

class PLASMA_DLL plDynaDecalMgr : public plSynchedObject {
    CREATABLE(plDynaDecalMgr, kDynaDecalMgr, plSynchedObject)

protected:
    plKey fMatPreShade, fMatRTShade;
    std::vector<plKey> fTargets, fPartyObjects;
    float fPartyTime;
    unsigned short fMaxNumVerts, fMaxNumIdx;
    unsigned int fWaitOnEnable;
    float fWetLength, fRampEnd, fDecayStart, fLifeSpan, fIntensity;
    float fGridSizeU, fGridSizeV;
    hsVector3 fScale;
    std::vector<plKey> fNotifies;

public:
    plDynaDecalMgr()
        : fPartyTime(0.0f), fMaxNumVerts(0), fMaxNumIdx(0),
          fWaitOnEnable(0), fWetLength(0.0f), fRampEnd(0.0f),
          fDecayStart(0.0f), fLifeSpan(0.0f), fIntensity(0.0f),
          fGridSizeU(0.0f), fGridSizeV(0.0f) { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;
};


class PLASMA_DLL plDynaBulletMgr : public plDynaDecalMgr {
    CREATABLE(plDynaBulletMgr, kDynaBulletMgr, plDynaDecalMgr)
};


class PLASMA_DLL plDynaFootMgr : public plDynaDecalMgr {
    CREATABLE(plDynaFootMgr, kDynaFootMgr, plDynaDecalMgr)
};

#endif
