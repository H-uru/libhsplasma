#ifndef _PLAUDIOINTERFACE_H
#define _PLAUDIOINTERFACE_H

#include "plObjInterface.h"

class plAudioInterface : public plObjInterface {
protected:
    plKey * Audible;

public:
    plAudioInterface();
    virtual ~plAudioInterface();

    virtual short ClassIndex();
    virtual short ClassIndex(PlasmaVer ver);

    virtual void read(hsStream *S);
    virtual void write(hsStream *S);
    virtual void prcWrite(hsStream* S, pfPrcHelper* prc);
};

#endif

