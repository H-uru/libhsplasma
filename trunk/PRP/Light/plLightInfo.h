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

    enum VolatileFlags {
        kVolNone = 0x0,
        kVolDirty = 0x1,
        kVolEmpty = 0x2,
        kVolZero = 0x4
    };

protected:
    hsTArray<plKey> fVisRegions;
    hsColorRGBA fAmbient, fDiffuse, fSpecular;
    hsMatrix44 fLightToLocal, fLocalToLight, fLightToWorld, fWorldToLight;
    plKey fProjection, fSoftVolume;
    plWeakKey fSceneNode;

public:
    plLightInfo();
    virtual ~plLightInfo();

    DECLARE_CREATABLE(plLightInfo)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
