#ifndef _PLNETMSGRELEVANCEREGIONS_H
#define _PLNETMSGRELEVANCEREGIONS_H

#include "plNetMessage.h"
#include "Util/hsBitVector.h"

DllClass plNetMsgRelevanceRegions : public plNetMessage {
    CREATABLE(plNetMsgRelevanceRegions, kNetMsgRelevanceRegions, plNetMessage)

private:
    hsBitVector fRegionsICareAbout;
    hsBitVector fRegionsImIn;

public:
    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    bool inRegion(size_t region) { return fRegionsImIn.get(region); }
    bool careAboutRegion(size_t region) { return fRegionsICareAbout.get(region); }
    void setRegion(size_t region, bool in, bool careAbout);
};

#endif
