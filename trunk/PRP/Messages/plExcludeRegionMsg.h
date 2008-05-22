#ifndef _PLEXCLUDEREGIONMSG_H
#define _PLEXCLUDEREGIONMSG_H

#include "plMessage.h"

DllClass plExcludeRegionMsg : public plMessage {
public:
    enum CmdType { kClear, kRelease };

protected:
    unsigned char fCmd;
    unsigned int fSynchFlags;

public:
    plExcludeRegionMsg();
    virtual ~plExcludeRegionMsg();

    DECLARE_CREATABLE(plExcludeRegionMsg)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
