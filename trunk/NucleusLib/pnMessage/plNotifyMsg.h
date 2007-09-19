#ifndef _PLNOTIFYMSG_H
#define _PLNOTIFYMSG_H

#include "plMessage.h"
#include "proEventData.h"

DllClass plNotifyMsg : public plMessage {
public:
    enum notificationType {
        kActivator, kVarNotification, kNotifySelf, kResponderFF,
        kResponderChangeState
    };

protected:
    int fType;
    float fState;
    int fID;
    hsTArray<proEventData*> fEvents;

public:
    plNotifyMsg();
    virtual ~plNotifyMsg();

    DECLARE_CREATABLE(plNotifyMsg)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
