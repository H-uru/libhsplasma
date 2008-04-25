#include "plOccluder.h"

/* plOccluder */
plOccluder::plOccluder() : fPriority(0.0f) { }
plOccluder::~plOccluder() { }

IMPLEMENT_CREATABLE(plOccluder, kOccluder, plObjInterface)

void plOccluder::read(hsStream* S, plResManager* mgr) {
    plObjInterface::read(S, mgr);

    fWorldBounds.read(S);
    fPriority = S->readFloat();
    
    fPolys.setSize(S->readShort());
    for (size_t i=0; i<fPolys.getSize(); i++)
        fPolys[i].read(S);

    fSceneNode = mgr->readKey(S);
    fVisRegions.setSize(S->readShort());
    for (size_t i=0; i<fVisRegions.getSize(); i++)
        fVisRegions[i] = mgr->readKey(S);
}

void plOccluder::write(hsStream* S, plResManager* mgr) {
    plObjInterface::write(S, mgr);

    fWorldBounds.write(S);
    S->writeFloat(fPriority);
    
    S->writeShort(fPolys.getSize());
    for (size_t i=0; i<fPolys.getSize(); i++)
        fPolys[i].write(S);

    mgr->writeKey(S, fSceneNode);
    S->writeShort(fVisRegions.getSize());
    for (size_t i=0; i<fVisRegions.getSize(); i++)
        mgr->writeKey(S, fVisRegions[i]);
}

void plOccluder::IPrcWrite(pfPrcHelper* prc) {
    plObjInterface::IPrcWrite(prc);

    prc->writeSimpleTag("WorldBounds");
    fWorldBounds.prcWrite(prc);
    prc->closeTag();

    prc->startTag("Priority");
    prc->writeParam("value", fPriority);
    prc->endTag(true);

    prc->writeSimpleTag("Polys");
    for (size_t i=0; i<fPolys.getSize(); i++)
        fPolys[i].prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("SceneNode");
    fSceneNode->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("VisRegions");
    for (size_t i=0; i<fVisRegions.getSize(); i++)
        fVisRegions[i]->prcWrite(prc);
    prc->closeTag();
}


/* plMobileOccluder */
plMobileOccluder::plMobileOccluder() { }
plMobileOccluder::~plMobileOccluder() { }

IMPLEMENT_CREATABLE(plMobileOccluder, kMobileOccluder, plOccluder)

void plMobileOccluder::read(hsStream* S, plResManager* mgr) {
    plOccluder::read(S, mgr);

    fLocalToWorld.read(S);
    fWorldToLocal.read(S);
    fLocalBounds.read(S);
}

void plMobileOccluder::write(hsStream* S, plResManager* mgr) {
    plOccluder::write(S, mgr);

    fLocalToWorld.write(S);
    fWorldToLocal.write(S);
    fLocalBounds.write(S);
}

void plMobileOccluder::IPrcWrite(pfPrcHelper* prc) {
    plOccluder::IPrcWrite(prc);

    prc->writeSimpleTag("LocalToWorldTransforms");
    fLocalToWorld.prcWrite(prc);
    fWorldToLocal.prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("LocalBounds");
    fLocalBounds.prcWrite(prc);
    prc->closeTag();
}
