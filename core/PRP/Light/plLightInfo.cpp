#include "plLightInfo.h"

plLightInfo::plLightInfo() {
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
    
    fAmbient.read(S);
    fDiffuse.read(S);
    fSpecular.read(S);
    fLightToLocal.read(S);
    fLocalToLight.read(S);
    fLightToWorld.read(S);
    fWorldToLight.read(S);
    //fLocalToWorld = fLightToWorld * fLocalToLight;
    //fWorldToLocal = fLightToLocal * fWorldToLight;

    fProjection = mgr->readKey(S);
    fSoftVolume = mgr->readKey(S);
    fSceneNode = mgr->readKey(S);

    fVisRegions.setSize(S->readInt());
    for (size_t i=0; i<fVisRegions.getSize(); i++)
        fVisRegions[i] = mgr->readKey(S);
}

void plLightInfo::write(hsStream* S, plResManager* mgr) {
    plObjInterface::write(S, mgr);
    
    fAmbient.write(S);
    fDiffuse.write(S);
    fSpecular.write(S);
    fLightToLocal.write(S);
    fLocalToLight.write(S);
    fLightToWorld.write(S);
    fWorldToLight.write(S);

    mgr->writeKey(S, fProjection);
    mgr->writeKey(S, fSoftVolume);
    mgr->writeKey(S, fSceneNode);

    S->writeInt(fVisRegions.getSize());
    for (size_t i=0; i<fVisRegions.getSize(); i++)
        mgr->writeKey(S, fVisRegions[i]);
}

void plLightInfo::IPrcWrite(pfPrcHelper* prc) {
    plObjInterface::IPrcWrite(prc);
    
    prc->writeSimpleTag("Ambient");
    fAmbient.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Diffuse");
    fDiffuse.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("Specular");
    fSpecular.prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("LightToLocal");
    fLightToLocal.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("LocalToLight");
    fLocalToLight.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("LightToWorld");
    fLightToWorld.prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("WorldToLight");
    fWorldToLight.prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("Projection");
    fProjection->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("SoftVolume");
    fSoftVolume->prcWrite(prc);
    prc->closeTag();
    prc->writeSimpleTag("SceneNode");
    fSceneNode->prcWrite(prc);
    prc->closeTag();

    prc->writeSimpleTag("VisRegions");
    for (size_t i=0; i<fVisRegions.getSize(); i++)
        fVisRegions[i]->prcWrite(prc);
    prc->closeTag();
}

void plLightInfo::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "Ambient") {
        if (tag->hasChildren())
            fAmbient.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "Diffuse") {
        if (tag->hasChildren())
            fDiffuse.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "Specular") {
        if (tag->hasChildren())
            fSpecular.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "LightToLocal") {
        if (tag->hasChildren())
            fLightToLocal.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "LocalToLight") {
        if (tag->hasChildren())
            fLocalToLight.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "LightToWorld") {
        if (tag->hasChildren())
            fLightToWorld.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "WorldToLight") {
        if (tag->hasChildren())
            fWorldToLight.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "Projection") {
        if (tag->hasChildren())
            fProjection = mgr->prcParseKey(tag->getFirstChild());
    } else if (tag->getName() == "SoftVolume") {
        if (tag->hasChildren())
            fSoftVolume = mgr->prcParseKey(tag->getFirstChild());
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

hsColorRGBA plLightInfo::getAmbient() const { return fAmbient; }
hsColorRGBA plLightInfo::getDiffuse() const { return fDiffuse; }
hsColorRGBA plLightInfo::getSpecular() const { return fSpecular; }
hsMatrix44 plLightInfo::getLightToLocal() const { return fLightToLocal; }
hsMatrix44 plLightInfo::getLocalToLight() const { return fLocalToLight; }
hsMatrix44 plLightInfo::getLightToWorld() const { return fLightToWorld; }
hsMatrix44 plLightInfo::getWorldToLight() const { return fWorldToLight; }
plKey plLightInfo::getProjection() const { return fProjection; }
plKey plLightInfo::getSoftVolume() const { return fSoftVolume; }
plKey plLightInfo::getSceneNode() const { return fSceneNode; }

void plLightInfo::setAmbient(const hsColorRGBA& color) { fAmbient = color; }
void plLightInfo::setDiffuse(const hsColorRGBA& color) { fDiffuse = color; }
void plLightInfo::setSpecular(const hsColorRGBA& color) { fSpecular = color; }
void plLightInfo::setLightToLocal(const hsMatrix44& xform) { fLightToLocal = xform; }
void plLightInfo::setLocalToLight(const hsMatrix44& xform) { fLocalToLight = xform; }
void plLightInfo::setLightToWorld(const hsMatrix44& xform) { fLightToWorld = xform; }
void plLightInfo::setWorldToLight(const hsMatrix44& xform) { fWorldToLight = xform; }
void plLightInfo::setProjection(plKey proj) { fProjection = proj; }
void plLightInfo::setSoftVolume(plKey vol) { fSoftVolume = vol; }
void plLightInfo::setSceneNode(plKey node) { fSceneNode = node; }

size_t plLightInfo::getNumVisRegions() const { return fVisRegions.getSize(); }
plKey plLightInfo::getVisRegion(size_t idx) { return fVisRegions[idx]; }
void plLightInfo::clearVisRegions() { fVisRegions.clear(); }
void plLightInfo::addVisRegion(plKey region) { fVisRegions.append(region); }
