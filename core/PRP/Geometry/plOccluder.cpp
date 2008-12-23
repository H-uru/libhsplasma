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

void plOccluder::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "WorldBounds") {
        if (tag->hasChildren())
            fWorldBounds.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "Priority") {
        fPriority = tag->getParam("value", "0").toFloat();
    } else if (tag->getName() == "Polys") {
        fPolys.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fPolys.getSize(); i++) {
            fPolys[i].prcParse(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "SceneNode") {
        if (tag->hasChildren())
            fSceneNode = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "VisRegions") {
        fVisRegions.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fVisRegions.getSize(); i++) {
            fVisRegions[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else {
        plObjInterface::IPrcParse(tag, mgr);
    }
}

float plOccluder::GetPriority() const {
    return fPriority;
}

const hsBounds3Ext&  plOccluder::GetBounds() {
    return fWorldBounds;
}

size_t plOccluder::GetNumPolys() const {
    return fPolys.getSize();
}

const plCullPoly& plOccluder::GetPoly(size_t idx) {
    return fPolys[idx];
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

    prc->writeSimpleTag("LocalToWorld");
    fLocalToWorld.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("WorldToLocal");
    fWorldToLocal.prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("LocalBounds");
    fLocalBounds.prcWrite(prc);
    prc->closeTag();
}

void plMobileOccluder::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "LocalToWorld") {
        if (tag->hasChildren())
            fLocalToWorld.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "WorldToLocal") {
        if (tag->hasChildren())
            fWorldToLocal.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "LocalBounds") {
        if (tag->hasChildren())
            fLocalBounds.prcParse(tag->getFirstChild());
    } else {
        plOccluder::IPrcParse(tag, mgr);
    }
}
