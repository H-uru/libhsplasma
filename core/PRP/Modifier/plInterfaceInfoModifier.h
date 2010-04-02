#ifndef _PLINTERFACEINFOMODIFIER_H
#define _PLINTERFACEINFOMODIFIER_H

#include "plModifier.h"

DllClass plInterfaceInfoModifier : public plSingleModifier {
    CREATABLE(plInterfaceInfoModifier, kInterfaceInfoModifier, plSingleModifier)

protected:
    hsTArray<plKey> fKeyList;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const hsTArray<plKey>& getIntfKeys() const { return fKeyList; }
    hsTArray<plKey>& getIntfKeys() { return fKeyList; }
    void addIntfKey(plKey key) { fKeyList.append(key); }
    void delIntfKey(size_t idx) { fKeyList.remove(idx); }
    void clearIntfKeys() { fKeyList.clear(); }
};

#endif
