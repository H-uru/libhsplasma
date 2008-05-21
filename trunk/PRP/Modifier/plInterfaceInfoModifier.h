#ifndef _PLINTERFACEINFOMODIFIER_H
#define _PLINTERFACEINFOMODIFIER_H

#include "NucleusLib/pnModifier/plModifier.h"

DllClass plInterfaceInfoModifier : public plSingleModifier {
protected:
    hsTArray<plKey> fKeyList;

public:
    plInterfaceInfoModifier();
    virtual ~plInterfaceInfoModifier();

    DECLARE_CREATABLE(plInterfaceInfoModifier)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
