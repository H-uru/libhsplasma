#include "plSceneObject.h"

plSceneObject::plSceneObject() { }
plSceneObject::~plSceneObject() { }

IMPLEMENT_CREATABLE(plSceneObject, kSceneObject, plSynchedObject)

void plSceneObject::read(hsStream* S, plResManager* mgr) {
    plSynchedObject::read(S, mgr);

    fDrawIntf = mgr->readKey(S);
    fSimIntf = mgr->readKey(S);
    fCoordIntf = mgr->readKey(S);
    fAudioIntf = mgr->readKey(S);

    fInterfaces.setSize(S->readInt());
    for (size_t i=0; i<fInterfaces.getSize(); i++)
        fInterfaces[i] = mgr->readKey(S);
    fModifiers.setSize(S->readInt());
    for (size_t i=0; i<fModifiers.getSize(); i++)
        fModifiers[i] = mgr->readKey(S);

    fSceneNode = mgr->readKey(S);
}

void plSceneObject::write(hsStream* S, plResManager* mgr) {
    plSynchedObject::write(S, mgr);

    mgr->writeKey(S, fDrawIntf);
    mgr->writeKey(S, fSimIntf);
    mgr->writeKey(S, fCoordIntf);
    mgr->writeKey(S, fAudioIntf);

    S->writeInt(fInterfaces.getSize());
    for (size_t i=0; i<fInterfaces.getSize(); i++)
        mgr->writeKey(S, fInterfaces[i]);
    S->writeInt(fModifiers.getSize());
    for (size_t i=0; i<fModifiers.getSize(); i++)
        mgr->writeKey(S, fModifiers[i]);
    mgr->writeKey(S, fSceneNode);
}

void plSceneObject::IPrcWrite(pfPrcHelper* prc) {
    plSynchedObject::IPrcWrite(prc);

    prc->writeSimpleTag("DrawInterface");
      fDrawIntf->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("SimulationInterface");
      fSimIntf->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("CoordinateInterface");
      fCoordIntf->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("AudioInterface");
      fAudioIntf->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Interfaces");
    for (size_t i=0; i<fInterfaces.getSize(); i++)
        fInterfaces[i]->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Modifiers");
    for (size_t i=0; i<fModifiers.getSize(); i++)
        fModifiers[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("SceneNode");
      fSceneNode->prcWrite(prc);
    prc->closeTag();
}

void plSceneObject::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "DrawInterface") {
        if (tag->hasChildren())
            fDrawIntf = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "SimulationInterface") {
        if (tag->hasChildren())
            fSimIntf = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "CoordinateInterface") {
        if (tag->hasChildren())
            fCoordIntf = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "AudioInterface") {
        if (tag->hasChildren())
            fAudioIntf = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Interfaces") {
        fInterfaces.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fInterfaces.getSize(); i++) {
            fInterfaces[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Modifiers") {
        fModifiers.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fModifiers.getSize(); i++) {
            fModifiers[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "SceneNode") {
        if (tag->hasChildren())
            fSceneNode = mgr->prcParseKey(tag->getFirstChild());
    } else {
        plSynchedObject::IPrcParse(tag, mgr);
    }
}

plKey plSceneObject::getDrawInterface() const { return fDrawIntf; }
plKey plSceneObject::getSimInterface() const { return fSimIntf; }
plKey plSceneObject::getCoordInterface() const { return fCoordIntf; }
plKey plSceneObject::getAudioInterface() const { return fAudioIntf; }
plKey plSceneObject::getSceneNode() const { return fSceneNode; }

void plSceneObject::setDrawInterface(plKey intf) { fDrawIntf = intf; }
void plSceneObject::setSimInterface(plKey intf) { fSimIntf = intf; }
void plSceneObject::setCoordInterface(plKey intf) { fCoordIntf = intf; }
void plSceneObject::setAudioInterface(plKey intf) { fAudioIntf = intf; }
void plSceneObject::setSceneNode(plKey node) { fSceneNode = node; }

size_t plSceneObject::getNumInterfaces() const { return fInterfaces.getSize(); }
size_t plSceneObject::getNumModifiers() const { return fModifiers.getSize(); }
plKey plSceneObject::getInterface(size_t idx) const { return fInterfaces[idx]; }
plKey plSceneObject::getModifier(size_t idx) const { return fModifiers[idx]; }
void plSceneObject::clearInterfaces() { fInterfaces.clear(); }
void plSceneObject::clearModifiers() { fModifiers.clear(); }
void plSceneObject::addInterface(plKey intf) { fInterfaces.append(intf); }
void plSceneObject::addModifier(plKey mod) { fModifiers.append(mod); }
void plSceneObject::delInterface(size_t idx) { fInterfaces.remove(idx); }
void plSceneObject::delModifier(size_t idx) { fModifiers.remove(idx); }
