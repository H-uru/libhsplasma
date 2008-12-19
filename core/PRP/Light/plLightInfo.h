#ifndef _PLLIGHTINFO_H
#define _PLLIGHTINFO_H

#include "PRP/Object/plObjInterface.h"
#include "Util/hsBitVector.h"
#include "Sys/hsColor.h"
#include "Math/hsMatrix44.h"
#include "PRP/Geometry/hsGDeviceRef.h"

DllClass plLightInfo : public plObjInterface {
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
    virtual ~plLightInfo();

    DECLARE_CREATABLE(plLightInfo)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    hsColorRGBA getAmbient() const;
    hsColorRGBA getDiffuse() const;
    hsColorRGBA getSpecular() const;
    hsMatrix44 getLightToLocal() const;
    hsMatrix44 getLocalToLight() const;
    hsMatrix44 getLightToWorld() const;
    hsMatrix44 getWorldToLight() const;
    plKey getProjection() const;
    plKey getSoftVolume() const;
    plKey getSceneNode() const;

    void setAmbient(const hsColorRGBA& color);
    void setDiffuse(const hsColorRGBA& color);
    void setSpecular(const hsColorRGBA& color);
    void setLightToLocal(const hsMatrix44& xform);
    void setLocalToLight(const hsMatrix44& xform);
    void setLightToWorld(const hsMatrix44& xform);
    void setWorldToLight(const hsMatrix44& xform);
    void setProjection(plKey proj);
    void setSoftVolume(plKey vol);
    void setSceneNode(plKey node);

    size_t getNumVisRegions() const;
    plKey getVisRegion(size_t idx);
    void clearVisRegions();
    void addVisRegion(plKey region);
};

#endif
