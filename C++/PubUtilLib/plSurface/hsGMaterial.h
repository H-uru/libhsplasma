#ifndef _HSGMATERIAL_H
#define _HSGMATERIAL_H

#include "../../NucleusLib/pnNetCommon/plSynchedObject.h"

class hsGMaterial : public plSynchedObject {
private:
    int Unknown;
    int LayerFlags;
    hsTArray<plKeyRef> Layers1, Layers2;

public:
    hsGMaterial(PlasmaVer pv = pvUnknown);
    ~hsGMaterial();

    void read(hsStream *S);
    void write(hsStream *S);
};

#endif

