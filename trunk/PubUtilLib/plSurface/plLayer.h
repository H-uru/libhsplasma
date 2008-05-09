#ifndef _PLLAYER_H

#include "plLayerInterface.h"

DllClass plLayer : public plLayerInterface {
protected:
    hsGMatState fState;

public:
    plLayer();
    virtual ~plLayer();

    DECLARE_CREATABLE(plLayer)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plLayerDepth : public plLayer {
public:
    DECLARE_CREATABLE(plLayerDepth)
};

#endif
