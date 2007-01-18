#ifndef _PLMESSAGE_H
#define _PLMESSAGE_H

#include "../pnKeyedObject/plReceiver.h"

class plMessage : public plReceiver {
public:
    plMessage(PlasmaVer pv = pvUnknown);
    virtual ~plMessage();
};

#endif

