#ifndef _PLDIRECTIONALLIGHTINFO_H
#define _PLDIRECTIONALLIGHTINFO_H

#include "plLightInfo.h"

DllClass plDirectionalLightInfo : public plLightInfo {
public:
    plDirectionalLightInfo();
    virtual ~plDirectionalLightInfo();

    DECLARE_CREATABLE(plDirectionalLightInfo)
};

DllClass plLimitedDirLightInfo : public plDirectionalLightInfo {
protected:
    float fWidth, fHeight, fDepth;

public:
    plLimitedDirLightInfo();
    virtual ~plLimitedDirLightInfo();

    DECLARE_CREATABLE(plLimitedDirLightInfo)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

    float getWidth() const;
    float getHeight() const;
    float getDepth() const;

    void setWidth(float width);
    void setHeight(float height);
    void setDepth(float depth);
};

#endif
