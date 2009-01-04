#ifndef _PLCROSSFADE_H
#define _PLCROSSFADE_H

#include "PRP/Modifier/plModifier.h"
#include "PRP/Message/plMessage.h"

DllClass plCrossfade : public plSingleModifier {
protected:
    unsigned short fFirstIdx, fSecondIdx;
    unsigned int fStartType, fEndType, fFlags;
    bool fRegistered;

public:
    plCrossfade();

    DECLARE_CREATABLE(plCrossfade)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plCrossfadeMsg : public plMessage {
public:
    DECLARE_CREATABLE(plCrossfadeMsg)
};

#endif
