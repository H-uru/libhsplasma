#ifndef _PLANIMSTAGE_H
#define _PLANIMSTAGE_H

#include "PRP/plCreatable.h"

DllClass plAnimStage : public plCreatable {
public:
    enum NotifyType {
        kNotifyEnter = 0x1,
        kNotifyLoop = 0x2,
        kNotifyAdvance = 0x4,
        kNotifyRegress = 0x8
    };

    enum PlayType { kPlayNone, kPlayKey, kPlayAuto, kPlayMax };

    enum AdvanceType {
        kAdvanceNone, kAdvanceOnMove, kAdvanceAuto, kAdvanceOnAnyKey,
        kAdvanceMax
    };

protected:
    PlayType fForwardType, fBackType;
    AdvanceType fAdvanceType, fRegressType;
    plString fAnimName;
    unsigned char fNotify;
    int fLoops;
    bool fDoAdvanceTo, fDoRegressTo;
    unsigned int fAdvanceTo, fRegressTo;

public:
    plAnimStage();
    virtual ~plAnimStage();

    DECLARE_CREATABLE(plAnimStage)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    PlayType getForwardType() const;
    PlayType getBackType() const;
    AdvanceType getAdvanceType() const;
    AdvanceType getRegressType() const;
    plString getAnimName() const;
    unsigned char getNotify() const;
    int getLoops() const;
    bool doAdvanceTo() const;
    bool doRegressTo() const;
    unsigned int getAdvanceTo() const;
    unsigned int getRegressTo() const;

    void setForwardType(PlayType fwd);
    void setBackType(PlayType back);
    void setAdvanceType(AdvanceType adv);
    void setRegressType(AdvanceType reg);
    void setAnimName(const plString& name);
    void setNotify(unsigned char notify);
    void setLoops(int loops);
    void setAdvanceTo(bool doAdvance, unsigned int advance = 0);
    void setRegressTo(bool doRegress, unsigned int regress = 0);
};

#endif
