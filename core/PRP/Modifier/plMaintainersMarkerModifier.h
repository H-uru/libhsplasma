#ifndef _PLMAINTAINERSMARKERMODIFIER_H
#define _PLMAINTAINERSMARKERMODIFIER_H

#include "plModifier.h"

DllClass plMaintainersMarkerModifier : public plMultiModifier {
public:
    enum { kBroken, kRepaired, kCalibrated, kNumCalibratedLevels };

protected:
    unsigned int fCalibrated;

public:
    plMaintainersMarkerModifier();
    virtual ~plMaintainersMarkerModifier();

    DECLARE_CREATABLE(plMaintainersMarkerModifier)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
