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

#ifndef _PLSOFTVOLUME_H
#define _PLSOFTVOLUME_H

#include "plRegionBase.hpp"
#include "plVolumeIsect.h"

class PLASMA_DLL plSoftVolume : public plRegionBase
{
    CREATABLE(plSoftVolume, kSoftVolume, plRegionBase)

public:
    enum
    {
        kListenNone = 0,
        kListenCheck = 0x1,
        kListenPosSet = 0x2,
        kListenDirty = 0x4,
        kListenRegistered = 0x8
    };

protected:
    unsigned int fListenState;
    float fInsideStrength, fOutsideStrength;

public:
    plSoftVolume()
        : fListenState(kListenNone), fInsideStrength(), fOutsideStrength() { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    unsigned int getListenState() const { return fListenState; }
    float getInsideStrength() const { return fInsideStrength; }
    float getOutsideStrength() const { return fOutsideStrength; }

    void setListenState(unsigned int value) { fListenState = value; }
    void setInsideStrength(float value) { fInsideStrength = value; }
    void setOutsideStrength(float value) { fOutsideStrength = value; }
};


class PLASMA_DLL plSoftVolumeSimple : public plSoftVolume
{
    CREATABLE(plSoftVolumeSimple, kSoftVolumeSimple, plSoftVolume)

protected:
    plVolumeIsect* fVolume;
    float fSoftDist;

public:
    plSoftVolumeSimple() : fVolume(), fSoftDist() { }
    ~plSoftVolumeSimple();

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    plVolumeIsect* getVolume() const { return fVolume; }
    float getSoftDist() const { return fSoftDist; }

    void setVolume(plVolumeIsect* vol);
    void setSoftDist(float dist) { fSoftDist = dist; }
};


class PLASMA_DLL plSoftVolumeComplex : public plSoftVolume
{
    CREATABLE(plSoftVolumeComplex, kSoftVolumeComplex, plSoftVolume)

protected:
    std::vector<plKey> fSubVolumes;

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    std::vector<plKey>& getSubVolumes() { return fSubVolumes; }
    const std::vector<plKey>& getSubVolumes() const { return fSubVolumes; }
    void addSubVolume(plKey key) { fSubVolumes.emplace_back(std::move(key)); }
    void clearSubVolumes() { fSubVolumes.clear(); }
    void delSubVolume(size_t idx) { fSubVolumes.erase(fSubVolumes.begin() + idx); }
};


class PLASMA_DLL plSoftVolumeIntersect : public plSoftVolumeComplex
{
    CREATABLE(plSoftVolumeIntersect, kSoftVolumeIntersect, plSoftVolumeComplex)
};


class PLASMA_DLL plSoftVolumeInvert : public plSoftVolumeComplex
{
    CREATABLE(plSoftVolumeInvert, kSoftVolumeInvert, plSoftVolumeComplex)
};


class PLASMA_DLL plSoftVolumeUnion : public plSoftVolumeComplex
{
    CREATABLE(plSoftVolumeUnion, kSoftVolumeUnion, plSoftVolumeComplex)
};

#endif
