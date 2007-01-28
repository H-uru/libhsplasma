#ifndef _PLMODIFIER_H
#define _PLMODIFIER_H

#include "../pnNetCommon/plSynchedObject.h"

class plModifier : public plSynchedObject {
public:
    plModifier(PlasmaVer pv = pvUnknown);

    virtual short ClassIndex();
};

#endif
