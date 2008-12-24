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

float plOccluder::getPriority() const { return fPriority; }
hsBounds3Ext plOccluder::getWorldBounds() const { return fWorldBounds; }
plKey plOccluder::getSceneNode() const { return fSceneNode; }

void plOccluder::setPriority(float priority) { fPriority = priority; }
void plOccluder::setWorldBounds(const hsBounds3Ext& bounds) { fWorldBounds = bounds; }
void plOccluder::setSceneNode(plKey node) { fSceneNode = node; }

size_t plOccluder::getNumPolys() const { return fPolys.getSize(); }
plCullPoly plOccluder::getPoly(size_t idx) const { return fPolys[idx]; }
void plOccluder::addPoly(const plCullPoly& poly) { fPolys.append(poly); }
void plOccluder::delPoly(size_t idx) { fPolys.remove(idx); }
void plOccluder::clearPolys() { fPolys.clear(); }


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

hsMatrix44 plMobileOccluder::getLocalToWorld() const { return fLocalToWorld; }
hsMatrix44 plMobileOccluder::getWorldToLocal() const { return fWorldToLocal; }
hsBounds3Ext plMobileOccluder::getLocalBounds() const { return fLocalBounds; }

void plMobileOccluder::setLocalToWorld(const hsMatrix44& l2w) { fLocalToWorld = l2w; }
void plMobileOccluder::setWorldToLocal(const hsMatrix44& w2l) { fWorldToLocal = w2l; }
void plMobileOccluder::setLocalBounds(const hsBounds3Ext& bounds) { fLocalBounds = bounds; }
