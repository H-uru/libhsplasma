#ifndef _PLEVENTCALLBACKMSG_H
#define _PLEVENTCALLBACKMSG_H

#include "plMessage.h"

DllClass plEventCallbackMsg : public plMessage {
protected:
    float fEventTime;
    CallbackEvent fEvent;
    short fIndex, fRepeats, fUser;

public:
    plEventCallbackMsg();
    virtual ~plEventCallbackMsg();

    DECLARE_CREATABLE(plEventCallbackMsg)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    float getEventTime() const;
    CallbackEvent getEvent() const;
    short getIndex() const;
    short getRepeats() const;
    short getUser() const;

    void setEventTime(float time);
    void setEvent(CallbackEvent evt);
    void setIndex(short idx);
    void setRepeats(short repeats);
    void setUser(short user);
};

#endif
