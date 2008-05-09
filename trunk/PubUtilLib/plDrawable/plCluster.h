#ifndef _PLCLUSTER_H
#define _PLCLUSTER_H

#include "plSpanInstance.h"
#include "CoreLib/hsTArray.hpp"

DllClass plCluster {
protected:
    hsTArray<plSpanInstance*> fInstances;
    plSpanEncoding fEncoding;
    class plClusterGroup* fGroup;

public:
    plCluster();
    ~plCluster();

    void read(hsStream* S, class plClusterGroup* group);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag, class plClusterGroup* group);
};

#endif
