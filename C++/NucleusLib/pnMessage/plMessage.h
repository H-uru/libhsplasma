#ifndef _PLMESSAGE_H
#define _PLMESSAGE_H

#include "../pnKeyedObject/plReceiver.h"
#include "../../CoreLib/hsTArray.hpp"
#include <vector>

class plMessage : public plReceiver {
protected:
    plKey fSender;
    hsTArray<plKey> fReceivers;
    double fTimeStamp;
    unsigned int fBCastFlags;
    std::vector<unsigned long> fNetRcvrPlayerIDs;
    
public:
    plMessage(PlasmaVer pv = pvUnknown);
    virtual ~plMessage();

    void IMsgRead(hsStream* S);
    void IMsgWrite(hsStream* S);
};

#endif

