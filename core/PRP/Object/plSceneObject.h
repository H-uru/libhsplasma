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

#ifndef _PLSCENEOBJECT_H
#define _PLSCENEOBJECT_H

#include "plSynchedObject.h"
#include "Util/hsTArray.hpp"

class PLASMA_DLL plSceneObject : public virtual plSynchedObject {
    CREATABLE(plSceneObject, kSceneObject, plSynchedObject)

    void addTarget (hsKeyedObject* obj);
public:
    plKey fDrawIntf, fSimIntf, fCoordIntf, fAudioIntf;
    hsTArray<plKey> fInterfaces, fModifiers;
    plKey fSceneNode;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plKey getDrawInterface() const { return fDrawIntf; }
    plKey getSimInterface() const { return fSimIntf; }
    plKey getCoordInterface() const { return fCoordIntf; }
    plKey getAudioInterface() const { return fAudioIntf; }
    plKey getSceneNode() const { return fSceneNode; }

    void setDrawInterface(plKey intf) { fDrawIntf = intf; }
    void setSimInterface(plKey intf) { fSimIntf = intf; }
    void setCoordInterface(plKey intf) { fCoordIntf = intf; }
    void setAudioInterface(plKey intf) { fAudioIntf = intf; }
    void setSceneNode(plKey node) { fSceneNode = node; }

    const hsTArray<plKey>& getInterfaces() const { return fInterfaces; }
    hsTArray<plKey>& getInterfaces() { return fInterfaces; }
    void addInterface(plKey intf) { fInterfaces.append(intf); }
    void delInterface(size_t idx) { fInterfaces.remove(idx); }
    void clearInterfaces() { fInterfaces.clear(); }

    const hsTArray<plKey>& getModifiers() const { return fModifiers; }
    hsTArray<plKey>& getModifiers() { return fModifiers; }
    void addModifier(plKey intf);
    void delModifier(size_t idx);
    void clearModifiers();

    virtual ~plSceneObject();
};

#endif
