#ifndef _PLGAMEMARKERMODIFIER_H
#define _PLGAMEMARKERMODIFIER_H

#include "plModifier.h"

DllClass plGameMarkerModifier : public plSingleModifier {
    CREATABLE(plGameMarkerModifier, kGameMarkerModifier, plSingleModifier)

private:
    plKey fGreenAnimKey, fRedAnimKey, fOpenAnimKey, fBounceAnimKey;
    unsigned short fPlaceSoundIdx, fHitSoundIdx;

public:
    plGameMarkerModifier();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
