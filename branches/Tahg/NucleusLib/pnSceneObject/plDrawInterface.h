#ifndef _PLDRAWINTERFACE_H
#define _PLDRAWINTERFACE_H

#include "plObjInterface.h"

class plDrawInterface : public plObjInterface {
public:
    hsTArray<plKey*> Drawables;
    hsTArray<plKey*> Objects;
    hsTArray<int> DrawableKeys;

public:
    plDrawInterface(PlasmaVer pv = pvUnknown);
    virtual ~plDrawInterface();

    virtual unsigned short ClassIndex();

    virtual void read(hsStream *S);
    virtual void write(hsStream *S);
};

#endif

