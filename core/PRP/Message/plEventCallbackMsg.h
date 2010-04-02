#ifndef _PLEVENTCALLBACKMSG_H
#define _PLEVENTCALLBACKMSG_H

#include "plMessage.h"

DllClass plEventCallbackMsg : public plMessage {
    CREATABLE(plEventCallbackMsg, kEventCallbackMsg, plMessage)

protected:
    float fEventTime;
    CallbackEvent fEvent;
    short fIndex, fRepeats, fUser;

public:
    plEventCallbackMsg();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    float getEventTime() const { return fEventTime; }
    CallbackEvent getEvent() const { return fEvent; }
    short getIndex() const { return fIndex; }
    short getRepeats() const { return fRepeats; }
    short getUser() const { return fUser; }

    void setEventTime(float time) { fEventTime = time; }
    void setEvent(CallbackEvent evt) { fEvent = evt; }
    void setIndex(short idx) { fIndex = idx; }
    void setRepeats(short repeats) { fRepeats = repeats; }
    void setUser(short user) { fUser = user; }
};

#endif
