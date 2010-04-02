#ifndef _PLLAYER_H

#include "plLayerInterface.h"

DllClass plLayer : public plLayerInterface {
    CREATABLE(plLayer, kLayer, plLayerInterface)

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plLayerDepth : public plLayer {
    CREATABLE(plLayerDepth, kLayerDepth, plLayer)
};

#endif
