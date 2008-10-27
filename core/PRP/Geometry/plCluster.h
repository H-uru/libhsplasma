#ifndef _PLCLUSTER_H
#define _PLCLUSTER_H

#include "plSpanInstance.h"
#include "Util/hsTArray.hpp"

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

    plSpanEncoding& getEncoding();
    plClusterGroup* getGroup() const;
    void setGroup(plClusterGroup* group);

    size_t getNumInstances() const;
    plSpanInstance* getInstance(size_t idx) const;
    void addInstance(plSpanInstance* inst);
    void delInstance(size_t idx);
    void clearInstances();
};

#endif
