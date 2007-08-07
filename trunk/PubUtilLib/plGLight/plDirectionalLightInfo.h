#ifndef _PLDIRECTIONALLIGHTINFO_H
#define _PLDIRECTIONALLIGHTINFO_H

#include "plLightInfo.h"

class plDirectionalLightInfo : public plLightInfo {
public:
    plDirectionalLightInfo();
    virtual ~plDirectionalLightInfo();

    DECLARE_CREATABLE(plDirectionalLightInfo)
    
    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
};

class plLimitedDirLightInfo : public plDirectionalLightInfo {
protected:
    float fWidth, fHeight, fDepth;
    //plParallelIsect* fParPlanes;

public:
    plLimitedDirLightInfo();
    virtual ~plLimitedDirLightInfo();

    DECLARE_CREATABLE(plLimitedDirLightInfo)

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif

