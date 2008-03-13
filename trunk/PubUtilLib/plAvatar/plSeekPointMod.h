#ifndef _PLSEEKPOINTMOD_H
#define _PLSEEKPOINTMOD_H

#include "NucleusLib/pnModifier/plModifier.h"

DllClass plSeekPointMod : public plMultiModifier {
protected:
    plString fName;

public:
    plSeekPointMod();
    virtual ~plSeekPointMod();

    DECLARE_CREATABLE(plSeekPointMod)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
