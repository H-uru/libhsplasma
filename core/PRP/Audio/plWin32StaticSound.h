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

#ifndef _PLWIN32STATICSOUND_H
#define _PLWIN32STATICSOUND_H

#include "plWin32Sound.h"

DllClass plWin32StaticSound : public plWin32Sound {
    CREATABLE(plWin32StaticSound, kWin32StaticSound, plWin32Sound)
};


DllClass plWin32GroupedSound : public plWin32StaticSound {
    CREATABLE(plWin32GroupedSound, kWin32GroupedSound, plWin32StaticSound)

protected:
    hsTArray<unsigned int> fStartPositions;
    hsTArray<float> fVolumes;

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
    virtual void IRead(hsStream* S, plResManager* mgr);
    virtual void IWrite(hsStream* S, plResManager* mgr);

public:
    size_t getNumVolumes() const { return fVolumes.getSize(); }
    unsigned int getPosition(size_t idx) const { return fStartPositions[idx]; }
    float getVolume(size_t idx) const { return fVolumes[idx]; }
    void setVolumes(size_t count, unsigned int* positions, float* volumes);
};


DllClass plWin32LinkSound : public plWin32StaticSound {
    CREATABLE(plWin32LinkSound, kWin32LinkSound, plWin32StaticSound)

public:
    virtual void read(hsStream* S, plResManager* mgr);
};

#endif
