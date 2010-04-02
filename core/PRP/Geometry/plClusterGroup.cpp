#include "plClusterGroup.h"

/* plLODDist */
plLODDist::plLODDist() : fMinDist(0.0f), fMaxDist(0.0f) { }

void plLODDist::read(hsStream* S) {
    fMinDist = S->readFloat();
    fMaxDist = S->readFloat();
}

void plLODDist::write(hsStream* S) {
    S->writeFloat(fMinDist);
    S->writeFloat(fMaxDist);
}

void plLODDist::prcWrite(pfPrcHelper* prc) {
    prc->startTag("plLODDist");
    prc->writeParam("Min", fMinDist);
    prc->writeParam("Max", fMaxDist);
    prc->endTag(true);
}

void plLODDist::prcParse(const pfPrcTag* tag) {
    if (tag->getName() != "plLODDist")
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());

    fMinDist = tag->getParam("Min", "0").toFloat();
    fMaxDist = tag->getParam("Max", "0").toFloat();
}


/* plClusterGroup */
plClusterGroup::plClusterGroup() : fRenderLevel(0) { }

plClusterGroup::~plClusterGroup() {
    for (size_t i=0; i<fClusters.getSize(); i++)
        delete fClusters[i];
}

void plClusterGroup::read(hsStream* S, plResManager* mgr) {
    hsKeyedObject::read(S, mgr);

    fTemplate.read(S);
    fMaterial = mgr->readKey(S);

    clearClusters();
    fClusters.setSizeNull(S->readInt());
    for (size_t i=0; i<fClusters.getSize(); i++) {
        fClusters[i] = new plCluster();
        fClusters[i]->read(S, this);
    }

    fRegions.setSize(S->readInt());
    for (size_t i=0; i<fRegions.getSize(); i++)
        fRegions[i] = mgr->readKey(S);
    fLights.setSize(S->readInt());
    for (size_t i=0; i<fLights.getSize(); i++)
        fLights[i] = mgr->readKey(S);

    fLOD.read(S);
    fRenderLevel = S->readInt();
    fSceneNode = mgr->readKey(S);
}

void plClusterGroup::write(hsStream* S, plResManager* mgr) {
    hsKeyedObject::write(S, mgr);

    fTemplate.write(S);
    mgr->writeKey(S, fMaterial);

    S->writeInt(fClusters.getSize());
    for (size_t i=0; i<fClusters.getSize(); i++)
        fClusters[i]->write(S);

    S->writeInt(fRegions.getSize());
    for (size_t i=0; i<fRegions.getSize(); i++)
        mgr->writeKey(S, fRegions[i]);
    S->writeInt(fLights.getSize());
    for (size_t i=0; i<fLights.getSize(); i++)
        mgr->writeKey(S, fLights[i]);

    fLOD.write(S);
    S->writeInt(fRenderLevel);
    mgr->writeKey(S, fSceneNode);
}

void plClusterGroup::IPrcWrite(pfPrcHelper* prc) {
    hsKeyedObject::IPrcWrite(prc);

    prc->writeSimpleTag("Template");
    fTemplate.prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Material");
    fMaterial->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Clusters");
    for (size_t i=0; i<fClusters.getSize(); i++)
        fClusters[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Regions");
    for (size_t i=0; i<fRegions.getSize(); i++)
        fRegions[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Lights");
    for (size_t i=0; i<fLights.getSize(); i++)
        fLights[i]->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("LOD");
    fLOD.prcWrite(prc);
    prc->closeTag();

    prc->startTag("RenderLevel");
    prc->writeParamHex("Level", fRenderLevel);
    prc->endTag(true);

    prc->writeSimpleTag("SceneNode");
    fSceneNode->prcWrite(prc);
    prc->closeTag();
}

void plClusterGroup::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Template") {
        if (tag->hasChildren())
            fTemplate.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "Material") {
        if (tag->hasChildren())
            fMaterial = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "Clusters") {
        clearClusters();
        fClusters.setSizeNull(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fClusters.getSize(); i++) {
            fClusters[i] = new plCluster();
            fClusters[i]->prcParse(child, this);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Regions") {
        fRegions.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fRegions.getSize(); i++) {
            fRegions[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "Lights") {
        fLights.setSize(tag->countChildren());
        const pfPrcTag* child = tag->getFirstChild();
        for (size_t i=0; i<fLights.getSize(); i++) {
            fLights[i] = mgr->prcParseKey(child);
            child = child->getNextSibling();
        }
    } else if (tag->getName() == "LOD") {
        if (tag->hasChildren())
            fLOD.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "RenderLevel") {
        fRenderLevel = tag->getParam("Level", "0").toUint();
    } else if (tag->getName() == "SceneNode") {
        if (tag->hasChildren())
            fSceneNode = mgr->prcParseKey(tag->getFirstChild());
    } else {
        hsKeyedObject::IPrcParse(tag, mgr);
    }
}

void plClusterGroup::delCluster(size_t idx) {
    delete fClusters[idx];
    fClusters.remove(idx);
}

void plClusterGroup::clearClusters() {
    for (size_t i=0; i<fClusters.getSize(); i++)
        delete fClusters[i];
    fClusters.clear();
}
