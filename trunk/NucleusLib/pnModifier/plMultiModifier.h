#ifndef _PLMULTIMODIFIER_H
#define _PLMULTIMODIFIER_H

#include "plModifier.h"
#include "../pnSceneObject/plSceneObject.h"
#include "../../CoreLib/hsBitVector.h"

class plMultiModifier : public plModifier {
protected:
    hsTArray<plSceneObject*> targets;
    hsBitVector flags;

public:
    plMultiModifier(PlasmaVer pv = pvUnknown);

    virtual short ClassIndex();

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
};

#endif
