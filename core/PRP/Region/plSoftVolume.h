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

DllClass plSoftVolume : public plRegionBase {
    CREATABLE(plSoftVolume, kSoftVolume, plRegionBase)

public:
    enum {
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
    plSoftVolume();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plSoftVolumeSimple : public plSoftVolume {
    CREATABLE(plSoftVolumeSimple, kSoftVolumeSimple, plSoftVolume)

protected:
    plVolumeIsect* fVolume;
    float fSoftDist;

public:
    plSoftVolumeSimple();
    virtual ~plSoftVolumeSimple();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    void setVolume(plVolumeIsect* vol);
};


DllClass plSoftVolumeComplex : public plSoftVolume {
    CREATABLE(plSoftVolumeComplex, kSoftVolumeComplex, plSoftVolume)

protected:
    hsTArray<plKey> fSubVolumes;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plSoftVolumeIntersect : public plSoftVolumeComplex {
    CREATABLE(plSoftVolumeIntersect, kSoftVolumeIntersect, plSoftVolumeComplex)
};


DllClass plSoftVolumeInvert : public plSoftVolumeComplex {
    CREATABLE(plSoftVolumeInvert, kSoftVolumeInvert, plSoftVolumeComplex)
};


DllClass plSoftVolumeUnion : public plSoftVolumeComplex {
    CREATABLE(plSoftVolumeUnion, kSoftVolumeUnion, plSoftVolumeComplex)
};

#endif
