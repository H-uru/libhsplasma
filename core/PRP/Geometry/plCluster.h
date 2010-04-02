#ifndef _PLCLUSTER_H
#define _PLCLUSTER_H

#include "plSpanInstance.h"
#include "Util/hsTArray.hpp"

DllClass plCluster {
protected:
    hsTArray<plSpanInstance*> fInstances;
    plSpanEncoding fEncoding;
    class plClusterGroup* fGroup;   // Not owned by the cluster

public:
    plCluster() { }
    ~plCluster();

    void read(hsStream* S, class plClusterGroup* group);
    void write(hsStream* S);
    void prcWrite(pfPrcHelper* prc);
    void prcParse(const pfPrcTag* tag, class plClusterGroup* group);

    const plSpanEncoding& getEncoding() const { return fEncoding; }
    plSpanEncoding& getEncoding() { return fEncoding; }

    plClusterGroup* getGroup() const { return fGroup; }
    void setGroup(plClusterGroup* group) { fGroup = group; }

    const hsTArray<plSpanInstance*>& getInstances() const { return fInstances; }
    hsTArray<plSpanInstance*>& getInstances() { return fInstances; }
    void addInstance(plSpanInstance* inst) { fInstances.append(inst); }
    void delInstance(size_t idx);
    void clearInstances();
};

#endif
