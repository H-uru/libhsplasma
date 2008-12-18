#ifndef _PLMSGFORWARDER_H
#define _PLMSGFORWARDER_H

#include "PRP/KeyedObject/hsKeyedObject.h"

DllClass plMsgForwarder : public hsKeyedObject {
protected:
    hsTArray<plKey> fForwardKeys;

public:
    plMsgForwarder();
    virtual ~plMsgForwarder();

    DECLARE_CREATABLE(plMsgForwarder)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    size_t getNumForwardKeys() const;
    plKey getForwardKey(size_t idx) const;
    void addForwardKey(plKey fwd);
    void delForwardKey(size_t idx);
    void clearForwardKeys();
};

#endif
