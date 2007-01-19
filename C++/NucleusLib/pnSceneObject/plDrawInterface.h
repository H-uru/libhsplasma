#ifndef _PLDRAWINTERFACE_H
#define _PLDRAWINTERFACE_H

#include "plObjInterface.h"

class plDrawableKey : public plKey {
public:
    int DrawKey;
public:
    plDrawableKey();
    virtual ~plDrawableKey();

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);

    virtual void readRef(hsStream* S);
    virtual void writeRef(hsStream* S);
};

class plDrawInterface : public plObjInterface {
public:
    hsTArray<plDrawableKey> Drawables;
    hsTArray<plKey> Objects;

public:
    plDrawInterface(PlasmaVer pv = pvUnknown);
    virtual ~plDrawInterface();

    virtual void read(hsStream *S);
    virtual void write(hsStream *S);
};

#endif

