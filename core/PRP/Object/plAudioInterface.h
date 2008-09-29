#ifndef _PLAUDIOINTERFACE_H
#define _PLAUDIOINTERFACE_H

#include "plObjInterface.h"

DllClass plAudioInterface : public plObjInterface {
protected:
    plKey fAudible;

public:
    plAudioInterface();
    virtual ~plAudioInterface();

    DECLARE_CREATABLE(plAudioInterface)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plKey getAudible() const;
    void setAudible(plKey audible);
};

#endif
