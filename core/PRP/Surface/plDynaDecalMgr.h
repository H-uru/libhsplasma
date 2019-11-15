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

class PLASMA_DLL plDynaDecalMgr : public plSynchedObject
{
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
        : fPartyTime(), fMaxNumVerts(), fMaxNumIdx(), fWaitOnEnable(),
          fWetLength(), fRampEnd(), fDecayStart(), fLifeSpan(), fIntensity(),
          fGridSizeU(), fGridSizeV() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    plKey getMatPreShade() const { return fMatPreShade; }
    plKey getMatRTShade() const { return fMatRTShade; }
    float getPartyTime() const { return fPartyTime; }
    unsigned short getMaxNumVerts() const { return fMaxNumVerts; }
    unsigned short getMaxNumIdx() const { return fMaxNumIdx; }
    unsigned int getWaitOnEnable() const { return fWaitOnEnable; }
    float getWetLength() const { return fWetLength; }
    float getRampEnd() const { return fRampEnd; }
    float getDecayStart() const { return fDecayStart; }
    float getLifeSpan() const { return fLifeSpan; }
    float getIntensity() const { return fIntensity; }
    float getGridSizeU() const { return fGridSizeU; }
    float getGridSizeV() const { return fGridSizeV; }
    hsVector3 getScale() const { return fScale; }

    void setMatPreShade(plKey value) { fMatPreShade = std::move(value); }
    void setMatRTShade(plKey value) { fMatRTShade = std::move(value); }
    void setPartyTime(float value) { fPartyTime = value; }
    void setMaxNumVerts(unsigned short value) { fMaxNumVerts = value; }
    void setMaxNumIdx(unsigned short value) { fMaxNumIdx = value; }
    void setWaitOnEnable(unsigned int value) { fWaitOnEnable = value; }
    void setWetLength(float value) { fWetLength = value; }
    void setRampEnd(float value) { fRampEnd = value; }
    void setDecayStart(float value) { fDecayStart = value; }
    void setLifeSpan(float value) { fLifeSpan = value; }
    void setIntensity(float value) { fIntensity = value; }
    void setGridSizeU(float value) { fGridSizeU = value; }
    void setGridSizeV(float value) { fGridSizeV = value; }
    void setScale(const hsVector3& value) { fScale = value; }

    void addTarget(plKey key) { fTargets.emplace_back(std::move(key)); }
    void clearTargets() { fTargets.clear(); }
    void delTarget(size_t idx) { fTargets.erase(fTargets.begin() + idx); }
    size_t getNumTargets() const { return fTargets.size(); }
    plKey getTarget(size_t idx) const { return fTargets[idx]; }

    void addPartyObject(plKey key) { fPartyObjects.emplace_back(std::move(key)); }
    void clearPartyObjects() { fPartyObjects.clear(); }
    void delPartyObject(size_t idx) { fPartyObjects.erase(fPartyObjects.begin() + idx); }
    size_t getNumPartyObjects() const { return fPartyObjects.size(); }
    plKey getPartyObject(size_t idx) const { return fPartyObjects[idx]; }

    void addNotify(plKey key) { fNotifies.emplace_back(std::move(key)); }
    void clearNotifies() { fNotifies.clear(); }
    void delNotify(size_t idx) { fNotifies.erase(fNotifies.begin() + idx); }
    size_t getNumNotifies() const { return fNotifies.size(); }
    plKey getNotify(size_t idx) const { return fNotifies[idx]; }
};


class PLASMA_DLL plDynaBulletMgr : public plDynaDecalMgr
{
    CREATABLE(plDynaBulletMgr, kDynaBulletMgr, plDynaDecalMgr)
};


class PLASMA_DLL plDynaFootMgr : public plDynaDecalMgr
{
    CREATABLE(plDynaFootMgr, kDynaFootMgr, plDynaDecalMgr)
};

#endif
