#ifndef _PLCROSSFADE_H
#define _PLCROSSFADE_H

#include "PRP/Modifier/plModifier.h"
#include "PRP/Message/plMessage.h"

DllClass plCrossfade : public plSingleModifier {
    CREATABLE(plCrossfade, kCrossfade, plSingleModifier)

protected:
    unsigned short fFirstIdx, fSecondIdx;
    unsigned int fStartType, fEndType, fFlags;
    bool fRegistered;

public:
    plCrossfade();
    virtual ~plCrossfade() { }

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    unsigned short getFirstIdx() const { return fFirstIdx; }
    unsigned short getSecondIdx() const { return fSecondIdx; }
    unsigned int getStartType() const { return fStartType; }
    unsigned int getEndType() const { return fEndType; }
    unsigned int getFlags() const { return fFlags; }
    bool isRegistered() const { return fRegistered; }

    void setFirstIdx(unsigned short idx) { fFirstIdx = idx; }
    void setSecondIdx(unsigned short idx) { fSecondIdx = idx; }
    void setStartType(unsigned int type) { fStartType = type; }
    void setEndType(unsigned int type) { fEndType = type; }
    void setFlags(unsigned int flags) { fFlags = flags; }
    void setRegistered(bool registered) { fRegistered = registered; }
};

DllClass plCrossfadeMsg : public plMessage {
    CREATABLE(plCrossfadeMsg, kCrossfadeMsg, plMessage)
};

#endif
