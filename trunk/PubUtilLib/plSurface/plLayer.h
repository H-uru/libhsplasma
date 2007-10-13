#ifndef _PLLAYER_H

#include "plLayerInterface.h"

DllClass plLayer : public plLayerInterface {
public:
    plLayer();
    virtual ~plLayer();

    DECLARE_CREATABLE(plLayer)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

DllClass plLayerDepth : public plLayer {
public:
    DECLARE_CREATABLE(plLayerDepth)
};

#endif
