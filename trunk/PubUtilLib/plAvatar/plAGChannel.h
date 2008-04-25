#ifndef _PLAGCHANNEL_H
#define _PLAGCHANNEL_H

#include "NucleusLib/pnFactory/plCreatable.h"

DllClass plAGChannel : public plCreatable {
protected:
    plString fName;

public:
    plAGChannel();
    virtual ~plAGChannel();

    DECLARE_CREATABLE(plAGChannel)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

#endif
