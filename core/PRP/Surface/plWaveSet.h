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

class PLASMA_DLL plWaveSetBase : public virtual plMultiModifier {
    CREATABLE(plWaveSetBase, kWaveSetBase, plMultiModifier)
};


class PLASMA_DLL plWaveSet6 : public virtual plWaveSetBase {
    CREATABLE(plWaveSet6, kWaveSet6, plWaveSetBase)

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


class PLASMA_DLL plWaveSet7 : public virtual plWaveSetBase {
    CREATABLE(plWaveSet7, kWaveSet7, plWaveSetBase)

public:
    enum { kHasRefObject = 0x10 };

protected:
    plFixedWaterState7 fState;
    float fMaxLen;
    std::vector<plKey> fShores, fDecals;
    plKey fEnvMap, fRefObj;

public:
    plWaveSet7() : fMaxLen(0.0f) {
        fFlags.setName(kHasRefObject, "kHasRefObject");
    }

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    std::vector<plKey>& getShores() { return fShores; }
    const std::vector<plKey>& getShores() const { return fShores; }
    void addShore(plKey key) { fShores.push_back(key); }
    void delShore(size_t idx) { fShores.erase(fShores.begin() + idx); }
    void clearShores() { fShores.clear(); }

    std::vector<plKey>& getDecals() { return fDecals; }
    const std::vector<plKey>& getDecals() const { return fDecals; }
    void addDecal(plKey key) { fDecals.push_back(key); }
    void delDecal(size_t idx) { fDecals.erase(fDecals.begin() + idx); }
    void clearDecals() { fDecals.clear(); }

    plFixedWaterState7& getState() { return fState; }
    const plFixedWaterState7& getState() const { return fState; }
    float getMaxLen() const { return fMaxLen; }
    plKey getEnvMap() const { return fEnvMap; }
    plKey getRefObj() const { return fRefObj; }

    void setState(const plFixedWaterState7& value) { fState = value; }
    void setMaxLen(float value) { fMaxLen = value; }
    void setEnvMap(plKey value) { fEnvMap = value; }
    void setRefObj(plKey value) { fRefObj = value; }
};

#endif
