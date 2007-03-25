#ifndef _PLIMAGELIBMOD_H

#include "../../NucleusLib/pnModifier/plModifier.h"

class plImageLibMod : public plSingleModifier {
public:
    enum Refs { kRefImage };

protected:
    hsTArray<plKey*> fImages;

public:
    plImageLibMod(PlasmaVer pv = pvUnknown);
    virtual ~plImageLibMod();
    
    virtual short ClassIndex();
    virtual const char* ClassName();

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(hsStream* S, pfPrcHelper* prc);
};

#endif
