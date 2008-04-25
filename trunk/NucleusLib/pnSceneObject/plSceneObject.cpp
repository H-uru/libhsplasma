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
    size_t i;
    for (i=0; i<fInterfaces.getSize(); i++)
        fInterfaces[i] = mgr->readKey(S);
    fModifiers.setSize(S->readInt());
    for (i=0; i<fModifiers.getSize(); i++)
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
    size_t i;
    for (i=0; i<fInterfaces.getSize(); i++)
        mgr->writeKey(S, fInterfaces[i]);
    S->writeInt(fModifiers.getSize());
    for (i=0; i<fModifiers.getSize(); i++)
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

    size_t i;
    prc->writeSimpleTag("Interfaces");
    for (i=0; i<fInterfaces.getSize(); i++)
        fInterfaces[i]->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Modifiers");
    for (i=0; i<fModifiers.getSize(); i++)
        fModifiers[i]->prcWrite(prc);
    prc->closeTag();
    
    prc->writeSimpleTag("SceneNode");
      fSceneNode->prcWrite(prc);
    prc->closeTag();
}
