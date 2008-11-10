#ifndef _PLSPAWNPOINTINFO_H
#define _PLSPAWNPOINTINFO_H

#include "Stream/pfPrcHelper.h"
#include "Stream/pfPrcParser.h"

DllClass plSpawnPointInfo {
protected:
    enum { kHasTitle, kHasSpawnPt, kHasCameraStack };
    
    plString fTitle, fSpawnPt, fCameraStack;

public:
    plSpawnPointInfo();
    ~plSpawnPointInfo();

    void read(hsStream* S);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag);

    bool isEmpty();
    void clear();
};

#endif
