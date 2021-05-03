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

#ifndef _PLPHYSICALSNDGROUP_H
#define _PLPHYSICALSNDGROUP_H

#include "PRP/KeyedObject/hsKeyedObject.h"

class PLASMA_DLL plPhysicalSndGroup : public hsKeyedObject
{
    CREATABLE(plPhysicalSndGroup, kPhysicalSndGroup, hsKeyedObject)

public:
    enum SoundGroup
    {
        kNone, kMetal, kGrass, kWood,
        kStone, kWater, kBone, kDirt,
        kRug, kCone, kUser1, kUser2,
        kUser3
    };

protected:
    unsigned int fGroup;
    std::vector<plKey> fImpactSounds, fSlideSounds;

public:
    plPhysicalSndGroup() : fGroup(kNone) { }

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    unsigned int getGroup() const { return fGroup; }
    void setGroup(unsigned int group) { fGroup = group; }

    const std::vector<plKey>& getImpactSounds() const { return fImpactSounds; }
    std::vector<plKey>& getImpactSounds() { return fImpactSounds; }
    void addImpactSound(plKey sound) { fImpactSounds.emplace_back(std::move(sound)); }
    void delImpactSound(size_t idx) { fImpactSounds.erase(fImpactSounds.begin() + idx); }
    void clearImpactSounds() { fImpactSounds.clear(); }

    const std::vector<plKey>& getSlideSounds() const { return fSlideSounds; }
    std::vector<plKey>& getSlideSounds() { return fSlideSounds; }
    void addSlideSound(plKey sound) { fSlideSounds.emplace_back(std::move(sound)); }
    void delSlideSound(size_t idx) { fSlideSounds.erase(fSlideSounds.begin() + idx); }
    void clearSlideSounds() { fSlideSounds.clear(); }
};

#endif
