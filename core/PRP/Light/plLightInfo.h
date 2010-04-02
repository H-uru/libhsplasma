#ifndef _PLLIGHTINFO_H
#define _PLLIGHTINFO_H

#include "PRP/Object/plObjInterface.h"
#include "Util/hsBitVector.h"
#include "Sys/hsColor.h"
#include "Math/hsMatrix44.h"
#include "PRP/Geometry/hsGDeviceRef.h"

DllClass plLightInfo : public plObjInterface {
    CREATABLE(plLightInfo, kLightInfo, plObjInterface)

public:
    enum {
        kDisable, kLPObsolete, kLPCastShadows, kLPMovable, kLPHasIncludes,
        kLPIncludesChars, kLP_OBSOLECTE_0, kLPOverAll, kLPHasSpecular,
        kLPShadowOnly, kLPShadowLightGroup, kLPForceProj, kNumProps
    };

protected:
    hsTArray<plKey> fVisRegions;
    hsColorRGBA fAmbient, fDiffuse, fSpecular;
    hsMatrix44 fLightToLocal, fLocalToLight, fLightToWorld, fWorldToLight;
    plKey fProjection, fSoftVolume;
    plKey fSceneNode;

public:
    plLightInfo();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    hsColorRGBA getAmbient() const { return fAmbient; }
    hsColorRGBA getDiffuse() const { return fDiffuse; }
    hsColorRGBA getSpecular() const { return fSpecular; }
    hsMatrix44 getLightToLocal() const { return fLightToLocal; }
    hsMatrix44 getLocalToLight() const { return fLocalToLight; }
    hsMatrix44 getLightToWorld() const { return fLightToWorld; }
    hsMatrix44 getWorldToLight() const { return fWorldToLight; }
    plKey getProjection() const { return fProjection; }
    plKey getSoftVolume() const { return fSoftVolume; }
    plKey getSceneNode() const { return fSceneNode; }

    void setAmbient(const hsColorRGBA& color) { fAmbient = color; }
    void setDiffuse(const hsColorRGBA& color) { fDiffuse = color; }
    void setSpecular(const hsColorRGBA& color) { fSpecular = color; }
    void setLightToLocal(const hsMatrix44& xform) { fLightToLocal = xform; }
    void setLocalToLight(const hsMatrix44& xform) { fLocalToLight = xform; }
    void setLightToWorld(const hsMatrix44& xform) { fLightToWorld = xform; }
    void setWorldToLight(const hsMatrix44& xform) { fWorldToLight = xform; }
    void setProjection(plKey proj) { fProjection = proj; }
    void setSoftVolume(plKey vol) { fSoftVolume = vol; }
    void setSceneNode(plKey node) { fSceneNode = node; }

    const hsTArray<plKey>& getVisRegions() const { return fVisRegions; }
    hsTArray<plKey>& getVisRegions() { return fVisRegions; }
    void addVisRegion(plKey region) { fVisRegions.append(region); }
    void delVisRegion(size_t idx) { fVisRegions.remove(idx); }
    void clearVisRegions() { fVisRegions.clear(); }
};

#endif
