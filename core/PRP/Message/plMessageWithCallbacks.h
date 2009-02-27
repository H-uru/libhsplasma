#ifndef _PLMESSAGEWITHCALLBACKS_H
#define _PLMESSAGEWITHCALLBACKS_H

#include "plMessage.h"

DllClass plMessageWithCallbacks : public plMessage {
protected:
    hsTArray<plMessage*> fCallbacks;

public:
    plMessageWithCallbacks();
    virtual ~plMessageWithCallbacks();

    DECLARE_CREATABLE(plMessageWithCallbacks)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    size_t getNumCallbacks() const;
    plMessage* getCallback(size_t idx) const;
    void addCallback(plMessage* callback);
    void delCallback(size_t idx);
    void clearCallbacks();
};

#endif
