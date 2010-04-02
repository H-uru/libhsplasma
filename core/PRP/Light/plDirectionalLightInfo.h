#ifndef _PLDIRECTIONALLIGHTINFO_H
#define _PLDIRECTIONALLIGHTINFO_H

#include "plLightInfo.h"

DllClass plDirectionalLightInfo : public plLightInfo {
    CREATABLE(plDirectionalLightInfo, kDirectionalLightInfo, plLightInfo)
};


DllClass plLimitedDirLightInfo : public plDirectionalLightInfo {
    CREATABLE(plLimitedDirLightInfo, kLimitedDirLightInfo,
              plDirectionalLightInfo)

protected:
    float fWidth, fHeight, fDepth;

public:
    plLimitedDirLightInfo();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    float getWidth() const { return fWidth; }
    float getHeight() const { return fHeight; }
    float getDepth() const { return fDepth; }

    void setWidth(float width) { fWidth = width; }
    void setHeight(float height) { fHeight = height; }
    void setDepth(float depth) { fDepth = depth; }
};

#endif
