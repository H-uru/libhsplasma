#ifndef _PLSEEKPOINTMOD_H
#define _PLSEEKPOINTMOD_H

#include "PRP/Modifier/plModifier.h"

DllClass plSeekPointMod : public plMultiModifier {
    CREATABLE(plSeekPointMod, kSeekPointMod, plMultiModifier)

protected:
    plString fName;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plString getName() const { return fName; }
    void setName(const plString& name) { fName = name; }
};

#endif
