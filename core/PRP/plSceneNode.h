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
#include "Util/hsTArray.hpp"

class PLASMA_DLL plSceneNode : public virtual hsKeyedObject {
    CREATABLE(plSceneNode, kSceneNode, hsKeyedObject)

protected:
    hsTArray<plKey> fSceneObjects;
    hsTArray<plKey> fPoolObjects;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const hsTArray<plKey>& getSceneObjects() const { return fSceneObjects; }
    hsTArray<plKey>& getSceneObjects() { return fSceneObjects; }
    void addSceneObject(plKey obj) { fSceneObjects.append(obj); }
    void delSceneObject(size_t idx) { fSceneObjects.remove(idx); }
    void clearSceneObjects() { fSceneObjects.clear(); }

    const hsTArray<plKey>& getPoolObjects() const { return fPoolObjects; }
    hsTArray<plKey>& getPoolObjects() { return fPoolObjects; }
    void addPoolObject(plKey obj) { fPoolObjects.append(obj); }
    void delPoolObject(size_t idx) { fPoolObjects.remove(idx); }
    void clearPoolObjects() { fPoolObjects.clear(); }
};

#endif
