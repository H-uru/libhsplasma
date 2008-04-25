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


/* plClusterGroup */
plClusterGroup::plClusterGroup() : fTemplate(NULL) { }

plClusterGroup::~plClusterGroup() {
    if (fTemplate != NULL)
        delete fTemplate;
    for (size_t i=0; i<fClusters.getSize(); i++)
        delete fClusters[i];
}

IMPLEMENT_CREATABLE(plClusterGroup, kClusterGroup, hsKeyedObject)

void plClusterGroup::read(hsStream* S, plResManager* mgr) {
    hsKeyedObject::read(S, mgr);

    if (fTemplate != NULL)
        delete fTemplate;
    fTemplate = new plSpanTemplate();
    fTemplate->read(S);
    fMaterial = mgr->readKey(S);

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
    fRenderLevel.level = S->readInt();
    fSceneNode = mgr->readKey(S);
}

void plClusterGroup::write(hsStream* S, plResManager* mgr) {
    hsKeyedObject::write(S, mgr);

    fTemplate->write(S);
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
    S->writeInt(fRenderLevel.level);
    mgr->writeKey(S, fSceneNode);
}

void plClusterGroup::IPrcWrite(pfPrcHelper* prc) {
    hsKeyedObject::IPrcWrite(prc);

    prc->writeSimpleTag("Template");
    fTemplate->prcWrite(prc);
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
    prc->writeParamHex("Level", fRenderLevel.level);
    prc->endTag(true);

    prc->writeSimpleTag("SceneNode");
    fSceneNode->prcWrite(prc);
    prc->closeTag();
}

plSpanTemplate* plClusterGroup::getTemplate() const { return fTemplate; }
