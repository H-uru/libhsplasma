#ifndef _PLIMAGELIBMOD_H

#include "../../NucleusLib/pnModifier/plModifier.h"

class plImageLibMod : public plSingleModifier {
protected:
    hsTArray<plKey*> fImages;

public:
    plImageLibMod();
    virtual ~plImageLibMod();
    
    virtual short ClassIndex();
    virtual short ClassIndex(PlasmaVer ver);

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(hsStream* S, pfPrcHelper* prc);
};

#endif
