#ifndef _PLAUDIOINTERFACE_H
#define _PLAUDIOINTERFACE_H

#include "plObjInterface.h"

DllClass plAudioInterface : public plObjInterface {
    CREATABLE(plAudioInterface, kAudioInterface, plObjInterface)

protected:
    plKey fAudible;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plKey getAudible() const { return fAudible; }
    void setAudible(plKey audible) { fAudible = audible; }
};

#endif
