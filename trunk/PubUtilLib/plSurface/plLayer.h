#ifndef _PLLAYER_H

#include "plLayerInterface.h"

class plLayer : public plLayerInterface {
public:
    plLayer();
    virtual ~plLayer();

    virtual short ClassIndex();
    virtual short ClassIndex(PlasmaVer ver);

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(hsStream* S, pfPrcHelper* prc);
};

#endif
