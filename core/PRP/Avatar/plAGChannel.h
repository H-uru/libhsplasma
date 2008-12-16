#ifndef _PLAGCHANNEL_H
#define _PLAGCHANNEL_H

#include "PRP/plCreatable.h"

DllClass plAGChannel : public plCreatable {
protected:
    plString fName;

public:
    plAGChannel();
    virtual ~plAGChannel();

    DECLARE_CREATABLE(plAGChannel)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plString getName() const;
    void setName(const plString& name);
};

#endif
