#ifndef _PLRECEIVER_H
#define _PLRECEIVER_H

#include "../pnFactory/plCreatable.h"
#include "plKey.h"
//#include "NucleusLib/pnMessage/plMessage.h"

class plReceiver : public plCreatable {
public:
    plReceiver(PlasmaVer pv = pvUnknown);
    virtual ~plReceiver();

    virtual bool msgReceive(class plMessage * msg);
};

#endif

