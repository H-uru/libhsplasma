#ifndef _PLDISTOPACITYMOD_H
#define _PLDISTOPACITYMOD_H

#include "../Modifier/plModifier.h"

DllClass plDistOpacityMod : public plSingleModifier {
protected:
    float fDists[4];

public:
    plDistOpacityMod();
    virtual ~plDistOpacityMod();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
