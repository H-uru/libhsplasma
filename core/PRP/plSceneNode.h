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

#ifndef _PLSCENENODE_H
#define _PLSCENENODE_H

#include "PRP/KeyedObject/hsKeyedObject.h"
#include "PRP/Object/plSceneObject.h"

class PLASMA_DLL plSceneNode : public hsKeyedObject
{
    CREATABLE(plSceneNode, kSceneNode, hsKeyedObject)

protected:
    std::vector<plKey> fSceneObjects;
    std::vector<plKey> fPoolObjects;

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    const std::vector<plKey>& getSceneObjects() const { return fSceneObjects; }
    std::vector<plKey>& getSceneObjects() { return fSceneObjects; }
    void addSceneObject(plKey obj) { fSceneObjects.emplace_back(std::move(obj)); }
    void delSceneObject(size_t idx) { fSceneObjects.erase(fSceneObjects.begin() + idx); }
    void clearSceneObjects() { fSceneObjects.clear(); }

    const std::vector<plKey>& getPoolObjects() const { return fPoolObjects; }
    std::vector<plKey>& getPoolObjects() { return fPoolObjects; }
    void addPoolObject(plKey obj) { fPoolObjects.emplace_back(std::move(obj)); }
    void delPoolObject(size_t idx) { fPoolObjects.erase(fPoolObjects.begin() + idx); }
    void clearPoolObjects() { fPoolObjects.clear(); }
};

#endif
