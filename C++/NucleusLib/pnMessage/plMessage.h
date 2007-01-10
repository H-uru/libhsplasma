#ifndef _PLMESSAGE_H
#define _PLMESSAGE_H

#include "../../plReceiver.h"

class plMessage : public plReceiver {
public:
    plMessage(PlasmaVer pv = pvUnknown);
    ~plMessage();
};

#endif

