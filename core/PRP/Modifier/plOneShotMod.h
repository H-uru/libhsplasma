#ifndef _PLONESHOTMOD_H
#define _PLONESHOTMOD_H

#include "plModifier.h"

DllClass plOneShotMod : public plMultiModifier {
protected:
    plString fAnimName;
    bool fDrivable, fReversable, fSmartSeek, fNoSeek;
    float fSeekDuration;

public:
    plOneShotMod();
    virtual ~plOneShotMod();

    DECLARE_CREATABLE(plOneShotMod)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    plString getAnimName() const;
    bool isDrivable() const;
    bool isReversable() const;
    bool getSmartSeek() const;
    bool getNoSeek() const;
    float getSeekDuration();

    void setAnimName(const plString& name);
    void setDrivable(bool drivable);
    void setReversable(bool reversable);
    void setSmartSeek(bool smartSeek);
    void setNoSeek(bool noSeek);
    void setSeekDuration(float duration);
};

#endif
