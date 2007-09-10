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

    enum VolatileFlags {
        kVolNone = 0x0,
        kVolDirty = 0x1,
        kVolEmpty = 0x2,
        kVolZero = 0x4
    };

protected:
    unsigned char volFlags;
    hsBitVector visSet, visNot;
    hsTArray<plKey> visRegions;
    plLightInfo** prevDevPtr;
    plLightInfo*  nextDevPtr;
    hsGDeviceRef* deviceRef;
    plKey projection;
    hsMatrix44 worldToProj;
    hsColorRGBA ambient, diffuse, specular;
    hsMatrix44 lightToLocal, localToLight, localToWorld, worldToLocal,
               lightToWorld, worldToLight;
    plKey sceneNode;
    //plLightProxy* proxyGen;
    plKey softVolume;
    float maxStrength;
    bool registeredForRenderMsg;
    hsBitVector slaveBits;

public:
    plLightInfo();
    virtual ~plLightInfo();

    DECLARE_CREATABLE(plLightInfo)

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
