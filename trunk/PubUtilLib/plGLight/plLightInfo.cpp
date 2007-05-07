#include "plLightInfo.h"
#include "../plResMgr/plResManager.h"

plLightInfo::plLightInfo() { }
plLightInfo::~plLightInfo() { }

short plLightInfo::ClassIndex() { return kLightInfo; }
short plLightInfo::ClassIndex(PlasmaVer ver) {
    return pdUnifiedTypeMap::MappedToPlasma(kLightInfo, ver);
}

void plLightInfo::read(hsStream *S) {
    if (deviceRef != NULL)
        deviceRef->UnRef();
    deviceRef = NULL;

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

    int count = S->readInt();
    visRegions.setSize(count);
    for (int i=0; i<count; i++)
        visRegions[i] = plResManager::inst->readKey(S);
    volFlags |= kVolDirty;
}

void plLightInfo::write(hsStream *S) {
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
    for (int i=0; i<visRegions.getSize(); i++)
        plResManager::inst->writeKey(S, visRegions[i]);
}
