#ifndef _PLNETMSGRELEVANCEREGIONS_H
#define _PLNETMSGRELEVANCEREGIONS_H

#include "plNetMessage.h"
#include "Util/hsBitVector.h"

DllClass plNetMsgRelevanceRegions : public plNetMessage {
private:
    hsBitVector fRegionsICareAbout;
    hsBitVector fRegionsImIn;

public:
    plNetMsgRelevanceRegions();
    ~plNetMsgRelevanceRegions();

    DECLARE_CREATABLE(plNetMsgRelevanceRegions)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
