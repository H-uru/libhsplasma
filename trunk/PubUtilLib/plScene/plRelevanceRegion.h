#ifndef PLRELEVANCEREGION_H
#define PLRELEVANCEREGION_H

#include "NucleusLib/pnSceneObject/plObjInterface.h"
#include "CoreLib/hsBitVector.h"

DllClass plRelevanceRegion : public plObjInterface {
protected:
    plKey fRegion;
	hsBitVector fRegionsICareAbout;
    unsigned int fMgrIdx;

public:
    plRelevanceRegion();
    virtual ~plRelevanceRegion();

    DECLARE_CREATABLE(plRelevanceRegion)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
