#ifndef _PLLAYER_H

#include "plLayerInterface.h"

class plLayer : public plLayerInterface {
public:
    plLayer(PlasmaVer pv = pvUnknown);
    virtual ~plLayer();

    virtual short ClassIndex();
    virtual const char* ClassName();

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(hsStream* S, pfPrcHelper* prc);
};

#endif
