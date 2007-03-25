#ifndef _PLAUDIOINTERFACE_H
#define _PLAUDIOINTERFACE_H

#include "plObjInterface.h"

class plAudioInterface : public plObjInterface {
protected:
    plKey * Audible;

public:
    plAudioInterface(PlasmaVer pv = pvUnknown);
    virtual ~plAudioInterface();

    virtual short ClassIndex();
    virtual const char* ClassName();

    virtual void read(hsStream *S);
    virtual void write(hsStream *S);
    virtual void prcWrite(hsStream* S, pfPrcHelper* prc);
};

#endif

