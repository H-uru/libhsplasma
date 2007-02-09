#ifndef _HSGMATERIAL_H
#define _HSGMATERIAL_H

#include "../../NucleusLib/pnNetCommon/plSynchedObject.h"
#include "../../CoreLib/hsTArray.hpp"

class hsGMaterial : public plSynchedObject {
private:
    int Unknown;
    int LayerFlags;
    hsTArray<plKey*> Layers1, Layers2;

public:
    hsGMaterial(PlasmaVer pv = pvUnknown);
    virtual ~hsGMaterial();

    virtual unsigned short ClassIndex();

    virtual void read(hsStream *S);
    virtual void write(hsStream *S);
};

#endif

