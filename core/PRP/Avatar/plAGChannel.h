#ifndef _PLAGCHANNEL_H
#define _PLAGCHANNEL_H

#include "PRP/plCreatable.h"

DllClass plAGChannel : public plCreatable {
    CREATABLE(plAGChannel, kAGChannel, plCreatable)

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
