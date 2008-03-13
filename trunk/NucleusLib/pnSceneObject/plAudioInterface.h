#ifndef _PLAUDIOINTERFACE_H
#define _PLAUDIOINTERFACE_H

#include "plObjInterface.h"

DllClass plAudioInterface : public plObjInterface {
protected:
    plKey Audible;

public:
    plAudioInterface();
    virtual ~plAudioInterface();

    DECLARE_CREATABLE(plAudioInterface)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif

