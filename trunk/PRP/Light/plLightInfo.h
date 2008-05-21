#ifndef _PLLIGHTINFO_H
#define _PLLIGHTINFO_H

#include "NucleusLib/pnSceneObject/plObjInterface.h"
#include "CoreLib/hsBitVector.h"
#include "CoreLib/hsColor.h"
#include "CoreLib/hsMatrix44.h"
#include "PubUtilLib/plPipeline/hsGDeviceRef.h"

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
