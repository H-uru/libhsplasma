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

DllClass plAudible : public virtual hsKeyedObject {
    CREATABLE(plAudible, kAudible, hsKeyedObject)
};


DllClass plAudibleNull : public virtual plAudible {
    CREATABLE(plAudibleNull, kAudibleNull, plAudible)
};


DllClass plWinAudible : public virtual plAudible {
    CREATABLE(plWinAudible, kWinAudible, plAudible)

private:
    hsTArray<plKey> fSoundObjs;
    plKey fSceneNode;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const hsTArray<plKey>& getSounds() const { return fSoundObjs; }
    hsTArray<plKey>& getSounds() { return fSoundObjs; }
    void addSound(plKey sound) { fSoundObjs.append(sound); }
    void delSound(size_t idx) { fSoundObjs.remove(idx); }
    void clearSounds() { fSoundObjs.clear(); }

    plKey getSceneNode() const { return fSceneNode; }
    void setSceneNode(plKey node) { fSceneNode = node; }
};


DllClass pl2WayWinAudible : public virtual plWinAudible {
    CREATABLE(pl2WayWinAudible, k2WayWinAudible, plWinAudible)
};

#endif
