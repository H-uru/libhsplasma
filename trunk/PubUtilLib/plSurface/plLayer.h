#ifndef _PLLAYER_H

#include "plLayerInterface.h"

class plLayer : public plLayerInterface {
public:
    plLayer();
    virtual ~plLayer();

    DECLARE_CREATABLE(plLayer)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
