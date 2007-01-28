#ifndef _PLMESSAGE_H
#define _PLMESSAGE_H

#include "../pnKeyedObject/plReceiver.h"
#include "../../CoreLib/hsTArray.hpp"
#include <vector>

class plMessage : public plReceiver {
public:
    enum plBCastFlags {
        kBCastNone = 0x0,
        kBCastByType = 0x1,
        kBCastUNUSED_0 = 0x2,
        kPropagateToChildren = 0x4,
        kBCastByExactType = 0x8,
        kPropagateToModifiers = 0x10,
        kClearAfterBCast = 0x20,
        kNetPropagate = 0x40,
        kNetSent = 0x80,
        kNetUseRelevanceRegions = 0x100,
        kNetForce = 0x200,
        kNetNonLocal = 0x400,
        kLocalPropagate = 0x800,
        kNetNonDeterministic = 0x200,
        kMsgWatch = 0x1000,
        kNetStartCascade = 0x2000,
        kNetAllowInterAge = 0x4000,
        kNetSendUnreliable = 0x8000,
        kCCRSendToAllPlayers = 0x10000,
        kNetCreatedRemotely = 0x20000
    };

protected:
    plKey* fSender;
    hsTArray<plKey*> fReceivers;
    double fTimeStamp;
    unsigned int fBCastFlags;
    std::vector<unsigned long> fNetRcvrPlayerIDs;
    
public:
    plMessage(PlasmaVer pv = pvUnknown);
    virtual ~plMessage();
    
    virtual short ClassIndex();

    void IMsgRead(hsStream* S);
    void IMsgWrite(hsStream* S);
};

#endif

