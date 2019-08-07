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

#ifndef _PLAUDIBLE_H
#define _PLAUDIBLE_H

#include "PRP/KeyedObject/hsKeyedObject.h"

class PLASMA_DLL plAudible : public hsKeyedObject
{
    CREATABLE(plAudible, kAudible, hsKeyedObject)
};


class PLASMA_DLL plAudibleNull : public plAudible
{
    CREATABLE(plAudibleNull, kAudibleNull, plAudible)
};


class PLASMA_DLL plWinAudible : public plAudible
{
    CREATABLE(plWinAudible, kWinAudible, plAudible)

private:
    std::vector<plKey> fSoundObjs;
    plKey fSceneNode;

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    const std::vector<plKey>& getSounds() const { return fSoundObjs; }
    std::vector<plKey>& getSounds() { return fSoundObjs; }
    void addSound(plKey sound) { fSoundObjs.emplace_back(std::move(sound)); }
    void delSound(size_t idx) { fSoundObjs.erase(fSoundObjs.begin() + idx); }
    void clearSounds() { fSoundObjs.clear(); }

    plKey getSceneNode() const { return fSceneNode; }
    void setSceneNode(plKey node) { fSceneNode = std::move(node); }
};


class PLASMA_DLL pl2WayWinAudible : public plWinAudible
{
    CREATABLE(pl2WayWinAudible, k2WayWinAudible, plWinAudible)
};

#endif
