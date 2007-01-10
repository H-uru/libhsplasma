#ifndef _PLAUDIOINTERFACE_H
#define _PLAUDIOINTERFACE_H

#include "plObjInterface.h"

class plAudioInterface : public plObjInterface {
protected:
    plKey * Audible;

public:
    plAudioInterface(PlasmaVer pv = pvUnknown);
    ~plAudioInterface();

    void read(hsStream *S);
    void write(hsStream *S);
};

#endif

