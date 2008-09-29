#ifndef _PLEXCLUDEREGIONMODIFIER_H
#define _PLEXCLUDEREGIONMODIFIER_H

#include "plModifier.h"

DllClass plExcludeRegionModifier : public plSingleModifier {
public:
    enum { kBlockCameras };

protected:
    hsTArray<plWeakKey> fSafePoints, fContainedAvatars;
    bool fSeek;
    float fSeekTime;

public:
    plExcludeRegionModifier();
    virtual ~plExcludeRegionModifier();

    DECLARE_CREATABLE(plExcludeRegionModifier)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
