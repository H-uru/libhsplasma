#ifndef _PLEXCLUDEREGIONMODIFIER_H
#define _PLEXCLUDEREGIONMODIFIER_H

#include "NucleusLib/pnModifier/plModifier.h"

DllClass plExcludeRegionModifier : public plSingleModifier {
public:
    enum { kBlockCameras };

protected:
    hsTArray<plKey> fSafePoints, fContainedAvatars;
    bool fSeek;
    float fSeekTime;

public:
    plExcludeRegionModifier();
    virtual ~plExcludeRegionModifier();

    DECLARE_CREATABLE(plExcludeRegionModifier)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

#endif
