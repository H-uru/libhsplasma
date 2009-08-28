#ifndef _PLNETMESSAGE_H
#define _PLNETMESSAGE_H

#include "PRP/plCreatable.h"
#include "Sys/plUnifiedTime.h"
#include "Sys/plUuid.h"

DllClass plNetMessage : public plCreatable {
public:
    enum ContentFlags {
        kHasTimeSent = 0x1,
        kHasGameMsgRecvrs = 0x2,
        kEchoBackToSender = 0x4,
        kRequestP2P = 0x8,
        kAllowTimeOut = 0x10,
        kIndirectMember = 0x20,
        kPublicIPClient = 0x40,
        kHasContext = 0x80,
        kAskVaultForGameState = 0x100,
        kHasTransactionID = 0x200,
        kNewSDLState = 0x400,
        kInitialAgeStateRequest = 0x800,
        kHasPlayerID = 0x1000,
        kUseRelevanceRegions = 0x2000,
        kHasAcctUuid = 0x4000,
        kInterAgeRouting = 0x8000,
        kHasVersion = 0x10000,
        kIsSystemMessage = 0x20000,
        kNeedsReliableSend = 0x40000,
        kRouteToAllPlayers = 0x80000
    };
    
    enum CompressionType {
        kCompressionNone,
        kCompressionFailed,
        kCompressionZlib,
        kCompressionDont
    };

private:
    unsigned int fFlags;
    unsigned char fProtocolVerMaj, fProtocolVerMin;
    plUnifiedTime fTimeSent;
    unsigned int fContext, fTransID, fPlayerID;
    plUuid fAcctUuid;

public:
    plNetMessage();
    virtual ~plNetMessage();

    DECLARE_CREATABLE(plNetMessage)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plNetMsgServerToClient : public plNetMessage {
public:
    DECLARE_CREATABLE(plNetMsgServerToClient)
};

#endif
