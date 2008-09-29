#ifndef _PLSEEKPOINTMOD_H
#define _PLSEEKPOINTMOD_H

#include "PRP/Modifier/plModifier.h"

DllClass plSeekPointMod : public plMultiModifier {
protected:
    plString fName;

public:
    plSeekPointMod();
    virtual ~plSeekPointMod();

    DECLARE_CREATABLE(plSeekPointMod)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
