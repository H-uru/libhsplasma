#ifndef _PLSCENEOBJECT_H
#define _PLSCENEOBJECT_H

#include "plSynchedObject.h"
#include "Util/hsTArray.hpp"

DllClass plSceneObject : public plSynchedObject {
    CREATABLE(plSceneObject, kSceneObject, plSynchedObject)

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
    void addModifier(plKey intf) { fModifiers.append(intf); }
    void delModifier(size_t idx) { fModifiers.remove(idx); }
    void clearModifiers() { fModifiers.clear(); }
};

#endif
