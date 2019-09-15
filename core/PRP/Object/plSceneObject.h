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

class PLASMA_DLL plSceneObject : public plSynchedObject
{
    CREATABLE(plSceneObject, kSceneObject, plSynchedObject)

public:
    ~plSceneObject() { clearModifiers(); }

    plKey fDrawIntf, fSimIntf, fCoordIntf, fAudioIntf;
    std::vector<plKey> fInterfaces, fModifiers;
    plKey fSceneNode;

public:
    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    plKey getDrawInterface() const { return fDrawIntf; }
    plKey getSimInterface() const { return fSimIntf; }
    plKey getCoordInterface() const { return fCoordIntf; }
    plKey getAudioInterface() const { return fAudioIntf; }
    plKey getSceneNode() const { return fSceneNode; }

    void setDrawInterface(plKey intf) { fDrawIntf = std::move(intf); }
    void setSimInterface(plKey intf) { fSimIntf = std::move(intf); }
    void setCoordInterface(plKey intf) { fCoordIntf = std::move(intf); }
    void setAudioInterface(plKey intf) { fAudioIntf = std::move(intf); }
    void setSceneNode(plKey node) { fSceneNode = std::move(node); }

    const std::vector<plKey>& getInterfaces() const { return fInterfaces; }
    std::vector<plKey>& getInterfaces() { return fInterfaces; }
    void addInterface(plKey intf) { fInterfaces.emplace_back(std::move(intf)); }
    void delInterface(size_t idx) { fInterfaces.erase(fInterfaces.begin() + idx); }
    void clearInterfaces() { fInterfaces.clear(); }

    const std::vector<plKey>& getModifiers() const { return fModifiers; }
    std::vector<plKey>& getModifiers() { return fModifiers; }
    void addModifier(plKey intf);
    void delModifier(size_t idx);
    void clearModifiers();

private:
    void addTarget (hsKeyedObject* obj);
};

#endif
