#ifndef _PLRIDEANIMATEDPHYSMSG_H
#define _PLRIDEANIMATEDPHYSMSG_H

#include "plMessage.h"

DllClass plRideAnimatedPhysMsg : public plMessage {
    CREATABLE(plRideAnimatedPhysMsg, kRideAnimatedPhysMsg, plMessage)

private:
    bool fEntering;
    plKey fRegion;

public:
    plRideAnimatedPhysMsg();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* s, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
