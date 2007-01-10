#ifndef _PLDRAWINTERFACE_H
#define _PLDRAWINTERFACE_H

#include "plObjInterface.h"

class plDrawableKeyRef : public plKeyRef {
public:
    int DrawKey;
public:
    plDrawableKeyRef();
    ~plDrawableKeyRef();

    void read(hsStream *S);
    void write(hsStream *S);
};

class plDrawInterface : public plObjInterface {
public:
    hsTArray<plDrawableKeyRef> Drawables;
    hsTArray<plKeyRef> Objects;

public:
    plDrawInterface(PlasmaVer pv = pvUnknown);
    ~plDrawInterface();

    void read(hsStream *S);
    void write(hsStream *S);
};

#endif

