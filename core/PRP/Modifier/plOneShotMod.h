#ifndef _PLONESHOTMOD_H
#define _PLONESHOTMOD_H

#include "plModifier.h"

DllClass plOneShotMod : public plMultiModifier {
    CREATABLE(plOneShotMod, kOneShotMod, plMultiModifier)

protected:
    plString fAnimName;
    bool fDrivable, fReversable, fSmartSeek, fNoSeek;
    float fSeekDuration;

public:
    plOneShotMod();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plString getAnimName() const { return fAnimName; }
    bool isDrivable() const { return fDrivable; }
    bool isReversable() const { return fReversable; }
    bool getSmartSeek() const { return fSmartSeek; }
    bool getNoSeek() const { return fNoSeek; }
    float getSeekDuration() { return fSeekDuration; }

    void setAnimName(const plString& name) { fAnimName = name; }
    void setDrivable(bool drivable) { fDrivable = drivable; }
    void setReversable(bool reversable) { fReversable = reversable; }
    void setSmartSeek(bool smartSeek) { fSmartSeek = smartSeek; }
    void setNoSeek(bool noSeek) { fNoSeek = noSeek; }
    void setSeekDuration(float duration) { fSeekDuration = duration; }
};

#endif
