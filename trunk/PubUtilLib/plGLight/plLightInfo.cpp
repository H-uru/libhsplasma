#include "plLightInfo.h"
#include "../plResMgr/plResManager.h"

plLightInfo::plLightInfo() : deviceRef(NULL) { }
plLightInfo::~plLightInfo() { }

IMPLEMENT_CREATABLE(plLightInfo, kLightInfo, plObjInterface)

void plLightInfo::read(hsStream* S) {
    //if (deviceRef != NULL)
    //    deviceRef->UnRef();
    //deviceRef = NULL;

    plObjInterface::read(S);
    ambient.read(S);
    diffuse.read(S);
    specular.read(S);
    lightToLocal.read(S);
    localToLight.read(S);
    lightToWorld.read(S);
    worldToLight.read(S);
    localToWorld = lightToWorld * localToLight;
    worldToLocal = lightToLocal * worldToLight;

    projection = plResManager::inst->readKey(S);
    softVolume = plResManager::inst->readKey(S);
    sceneNode = plResManager::inst->readKey(S);

    visRegions.setSize(S->readInt());
    for (size_t i=0; i<visRegions.getSize(); i++)
        visRegions[i] = plResManager::inst->readKey(S);
    volFlags |= kVolDirty;
}

void plLightInfo::write(hsStream* S) {
    plObjInterface::write(S);
    ambient.write(S);
    diffuse.write(S);
    specular.write(S);
    lightToLocal.write(S);
    localToLight.write(S);
    lightToWorld.write(S);
    worldToLight.write(S);

    plResManager::inst->writeKey(S, projection);
    plResManager::inst->writeKey(S, softVolume);
    plResManager::inst->writeKey(S, sceneNode);

    S->writeInt(visRegions.getSize());
    for (size_t i=0; i<visRegions.getSize(); i++)
        plResManager::inst->writeKey(S, visRegions[i]);
}

void plLightInfo::prcWrite(pfPrcHelper* prc) {
    plObjInterface::prcWrite(prc);
    prc->writeSimpleTag("Ambient");
    ambient.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Diffuse");
    diffuse.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Specular");
    specular.prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("LightToLocal");
    lightToLocal.prcWrite(prc);
    localToLight.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("LightToWorld");
    lightToWorld.prcWrite(prc);
    worldToLight.prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Projection");
    projection->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("SoftVolume");
    softVolume->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("SceneNode");
    sceneNode->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("VisRegions");
    for (size_t i=0; i<visRegions.getSize(); i++)
        visRegions[i]->prcWrite(prc);
    prc->closeTag();
}

