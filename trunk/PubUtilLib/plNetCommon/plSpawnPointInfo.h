#ifndef _PLSPAWNPOINTINFO_H
#define _PLSPAWNPOINTINFO_H

#include "../../CoreLib/hsStream.h"
#include "../../FeatureLib/pfPRC/pfPrcHelper.h"

DllClass plSpawnPointInfo {
protected:
    plString fTitle, fSpawnPt, fCameraStack;

public:
    plSpawnPointInfo();
    ~plSpawnPointInfo();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
};

#endif
