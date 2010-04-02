#ifndef _PLMESSAGEWITHCALLBACKS_H
#define _PLMESSAGEWITHCALLBACKS_H

#include "plMessage.h"

DllClass plMessageWithCallbacks : public plMessage {
    CREATABLE(plMessageWithCallbacks, kMessageWithCallbacks, plMessage)

protected:
    hsTArray<plMessage*> fCallbacks;

public:
    plMessageWithCallbacks() { }
    virtual ~plMessageWithCallbacks();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const hsTArray<plMessage*>& getCallbacks() const { return fCallbacks; }
    hsTArray<plMessage*>& getCallbacks() { return fCallbacks; }
    void addCallback(plMessage* callback) { fCallbacks.append(callback); }
    void delCallback(size_t idx);
    void clearCallbacks();
};

#endif
