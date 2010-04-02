#ifndef _PLRELEVANCEREGION_H
#define _PLRELEVANCEREGION_H

#include "PRP/Object/plObjInterface.h"
#include "Util/hsBitVector.h"

DllClass plRelevanceRegion : public plObjInterface {
    CREATABLE(plRelevanceRegion, kRelevanceRegion, plObjInterface)

protected:
    plKey fRegion;
    hsBitVector fRegionsICareAbout;
    unsigned int fMgrIdx;

public:
    plRelevanceRegion();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
