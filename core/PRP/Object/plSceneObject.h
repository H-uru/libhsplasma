#ifndef _PLSCENEOBJECT_H
#define _PLSCENEOBJECT_H

#include "plSynchedObject.h"
#include "Util/hsTArray.hpp"

DllClass plSceneObject : public plSynchedObject {
public:
    plKey fDrawIntf, fSimIntf, fCoordIntf, fAudioIntf;
    hsTArray<plKey> fInterfaces, fModifiers;
    plKey fSceneNode;

public:
    plSceneObject();
    virtual ~plSceneObject();

    DECLARE_CREATABLE(plSceneObject)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plKey getDrawInterface() const;
    plKey getSimInterface() const;
    plKey getCoordInterface() const;
    plKey getAudioInterface() const;
    plKey getSceneNode() const;

    void setDrawInterface(plKey intf);
    void setSimInterface(plKey intf);
    void setCoordInterface(plKey intf);
    void setAudioInterface(plKey intf);
    void setSceneNode(plKey node);

    size_t getNumInterfaces() const;
    size_t getNumModifiers() const;
    plKey getInterface(size_t idx) const;
    plKey getModifier(size_t idx) const;
    void clearInterfaces();
    void clearModifiers();
    void addInterface(plKey intf);
    void addModifier(plKey mod);
    void delInterface(size_t idx);
    void delModifier(size_t idx);
};

#endif
