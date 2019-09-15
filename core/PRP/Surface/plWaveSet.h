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

#ifndef _PLWAVESET_H
#define _PLWAVESET_H

#include "PRP/Modifier/plModifier.h"
#include "plFixedWaterState6.h"
#include "plFixedWaterState7.h"

class PLASMA_DLL plWaveSetBase : public plMultiModifier
{
    CREATABLE(plWaveSetBase, kWaveSetBase, plMultiModifier)
};


class PLASMA_DLL plWaveSet6 : public plWaveSetBase
{
    CREATABLE(plWaveSet6, kWaveSet6, plWaveSetBase)

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;
};


class PLASMA_DLL plWaveSet7 : public plWaveSetBase
{
    CREATABLE(plWaveSet7, kWaveSet7, plWaveSetBase)

public:
    enum { kHasRefObject = 0x10 };

protected:
    plFixedWaterState7 fState;
    float fMaxLen;
    std::vector<plKey> fShores, fDecals;
    plKey fEnvMap, fRefObj;

public:
    plWaveSet7() : fMaxLen()
    {
        fFlags.setName(kHasRefObject, "kHasRefObject");
    }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    std::vector<plKey>& getShores() { return fShores; }
    const std::vector<plKey>& getShores() const { return fShores; }
    void addShore(plKey key) { fShores.emplace_back(std::move(key)); }
    void delShore(size_t idx) { fShores.erase(fShores.begin() + idx); }
    void clearShores() { fShores.clear(); }

    std::vector<plKey>& getDecals() { return fDecals; }
    const std::vector<plKey>& getDecals() const { return fDecals; }
    void addDecal(plKey key) { fDecals.emplace_back(std::move(key)); }
    void delDecal(size_t idx) { fDecals.erase(fDecals.begin() + idx); }
    void clearDecals() { fDecals.clear(); }

    plFixedWaterState7& getState() { return fState; }
    const plFixedWaterState7& getState() const { return fState; }
    float getMaxLen() const { return fMaxLen; }
    plKey getEnvMap() const { return fEnvMap; }
    plKey getRefObj() const { return fRefObj; }

    void setState(const plFixedWaterState7& value) { fState = value; }
    void setMaxLen(float value) { fMaxLen = value; }
    void setEnvMap(plKey value) { fEnvMap = std::move(value); }
    void setRefObj(plKey value) { fRefObj = std::move(value); }
};

#endif
