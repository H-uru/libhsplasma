#ifndef _PLLAYER_H

#include "plLayerInterface.h"

class plLayer : public plLayerInterface {
public:
    plLayer();
    virtual ~plLayer();

    DECLARE_CREATABLE(plLayer)

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
