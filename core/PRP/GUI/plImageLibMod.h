#ifndef _PLIMAGELIBMOD_H

#include "PRP/Modifier/plModifier.h"

DllClass plImageLibMod : public plSingleModifier {
protected:
    hsTArray<plKey> fImages;

public:
    plImageLibMod();
    virtual ~plImageLibMod();
    
    DECLARE_CREATABLE(plImageLibMod)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
