#ifndef _PLLIGHTINFO_H
#define _PLLIGHTINFO_H

#include "../../NucleusLib/pnSceneObject/plObjInterface.h"
#include "../../CoreLib/hsBitVector.h"
#include "../../CoreLib/hsColor.h"
#include "../../CoreLib/hsMatrix44.h"
#include "../plPipeline/hsGDeviceRef.h"

class plLightInfo : public plObjInterface {
public:
    enum {
        kDisable, kLPObsolete, kLPCastShadows, kLPMovable, kLPHasIncludes,
        kLPIncludesChars, kLP_OBSOLECTE_0, kLPOverAll, kLPHasSpecular,
        kLPShadowOnly, kLPShadowLightGroup, kLPForceProj, kNumProps
    };

    enum LIRefType {
        kProjection, k_OBSOLECTE_REF_0, kOBSOLECTE_REF_1, kOBSOLECTE_REF_2,
        kSoftVolume, kVisRegion
    };

    enum VolatileFlags {
        kVolNone = 0x0,
        kVolDirty = 0x1,
        kVolEmpty = 0x2,
        kVolZero = 0x4
    };

protected:
    unsigned char volFlags;
    hsBitVector visSet, visNot;
    hsTArray<plKey*> visRegions;
    plLightInfo** prevDevPtr;
    plLightInfo*  nextDevPtr;
    hsGDeviceRef* deviceRef;
    plKey* projection;
    hsMatrix44 worldToProj;
    hsColorRGBA ambient, diffuse, specular;
    hsMatrix44 lightToLocal, localToLight, localToWorld, worldToLocal,
               lightToWorld, worldToLight;
    plKey* sceneNode;
    //plLightProxy* proxyGen;
    plKey* softVolume;
    float maxStrength;
    bool registeredForRenderMsg;
    hsBitVector slaveBits;

public:
    plLightInfo(PlasmaVer pv = pvUnknown);
    virtual ~plLightInfo();

    virtual short ClassIndex();

    virtual void read(hsStream *S);
    virtual void write(hsStream *S);
};

#endif
