#ifndef _PLMSGFORWARDER_H
#define _PLMSGFORWARDER_H

#include "PRP/KeyedObject/hsKeyedObject.h"

DllClass plMsgForwarder : public hsKeyedObject {
    CREATABLE(plMsgForwarder, kMsgForwarder, hsKeyedObject)

protected:
    hsTArray<plKey> fForwardKeys;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const hsTArray<plKey>& getForwardKeys() const { return fForwardKeys; }
    hsTArray<plKey>& getForwardKeys() { return fForwardKeys; }
    void addForwardKey(plKey fwd) { fForwardKeys.append(fwd); }
    void delForwardKey(size_t idx) { fForwardKeys.remove(idx); }
    void clearForwardKeys() { fForwardKeys.clear(); }
};

#endif
