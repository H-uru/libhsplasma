#ifndef _PLMODIFIER_H
#define _PLMODIFIER_H

#include "../pnNetCommon/plSynchedObject.h"
#include "../pnSceneObject/plSceneObject.h"
#include "../../CoreLib/hsBitVector.h"

class plModifier : public plSynchedObject {
public:
    plModifier(PlasmaVer pv = pvUnknown);

    virtual short ClassIndex();
    virtual const char* ClassName();
};


class plSingleModifier : public plModifier {
protected:
    plSceneObject* target;
    hsBitVector flags;

public:
    plSingleModifier(PlasmaVer pv = pvUnknown);

    virtual short ClassIndex();
    virtual const char* ClassName();

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(hsStream* S, pfPrcHelper* prc);
};


class plMultiModifier : public plModifier {
protected:
    hsTArray<plSceneObject*> targets;
    hsBitVector flags;

public:
    plMultiModifier(PlasmaVer pv = pvUnknown);

    virtual short ClassIndex();
    virtual const char* ClassName();

    virtual void read(hsStream* S);
    virtual void write(hsStream* S);
    virtual void prcWrite(hsStream* S, pfPrcHelper* prc);
};

#endif
