#include "plLightInfo.h"

plLightInfo::plLightInfo() : deviceRef(NULL) {
    fProps.setName(kDisable, "kDisable");
    fProps.setName(kLPObsolete, "kLPObsolete");
    fProps.setName(kLPCastShadows, "kLPCastShadows");
    fProps.setName(kLPMovable, "kLPMovable");
    fProps.setName(kLPHasIncludes, "kLPHasIncludes");
    fProps.setName(kLPIncludesChars, "kLPIncludesChars");
    fProps.setName(kLPOverAll, "kLPOverAll");
    fProps.setName(kLPHasSpecular, "kLPHasSpecular");
    fProps.setName(kLPShadowOnly, "kLPShadowOnly");
    fProps.setName(kLPShadowLightGroup, "kLPShadowLightGroup");
    fProps.setName(kLPForceProj, "kLPForceProj");
}

plLightInfo::~plLightInfo() { }

IMPLEMENT_CREATABLE(plLightInfo, kLightInfo, plObjInterface)

void plLightInfo::read(hsStream* S, plResManager* mgr) {
    plObjInterface::read(S, mgr);
    
    ambient.read(S);
    diffuse.read(S);
    specular.read(S);
    lightToLocal.read(S);
    localToLight.read(S);
    lightToWorld.read(S);
    worldToLight.read(S);
    localToWorld = lightToWorld * localToLight;
    worldToLocal = lightToLocal * worldToLight;

    projection = mgr->readKey(S);
    softVolume = mgr->readKey(S);
    sceneNode = mgr->readKey(S);

    visRegions.setSize(S->readInt());
    for (size_t i=0; i<visRegions.getSize(); i++)
        visRegions[i] = mgr->readKey(S);
    volFlags |= kVolDirty;
}

void plLightInfo::write(hsStream* S, plResManager* mgr) {
    plObjInterface::write(S, mgr);
    
    ambient.write(S);
    diffuse.write(S);
    specular.write(S);
    lightToLocal.write(S);
    localToLight.write(S);
    lightToWorld.write(S);
    worldToLight.write(S);

    mgr->writeKey(S, projection);
    mgr->writeKey(S, softVolume);
    mgr->writeKey(S, sceneNode);

    S->writeInt(visRegions.getSize());
    for (size_t i=0; i<visRegions.getSize(); i++)
        mgr->writeKey(S, visRegions[i]);
}

void plLightInfo::IPrcWrite(pfPrcHelper* prc) {
    plObjInterface::IPrcWrite(prc);
    
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
