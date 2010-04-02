#ifndef _PLNETMSGGAMEMESSAGE_H
#define _PLNETMSGGAMEMESSAGE_H

#include "plNetMsgStream.h"
#include "Sys/plUnifiedTime.h"
#include "PRP/Message/plMessage.h"

DllClass plNetMsgGameMessage : public plNetMsgStream {
    CREATABLE(plNetMsgGameMessage, kNetMsgGameMessage, plNetMsgStream)

private:
    plUnifiedTime fDeliveryTime;
    plMessage* fMessage;

public:
    plNetMsgGameMessage();
    ~plNetMsgGameMessage();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plUnifiedTime getDeliveryTime() const { return fDeliveryTime; }
    plMessage* getMessage() const { return fMessage; }

    void setDeliveryTime(const plUnifiedTime& deliveryTime) { fDeliveryTime = deliveryTime; }
    void setMessage(plMessage* Message);
};


DllClass plNetMsgGameMessageDirected : public plNetMsgGameMessage {
    CREATABLE(plNetMsgGameMessageDirected, kNetMsgGameMessageDirected,
              plNetMsgGameMessage)

private:
    hsTArray<unsigned int> fReceivers;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const hsTArray<unsigned int>& getReceivers() const { return fReceivers; }
    void setReceivers(const hsTArray<unsigned int>& receivers) { fReceivers = receivers; }
};

#endif
