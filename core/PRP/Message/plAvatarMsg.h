#ifndef _PLAVATARMSG_H
#define _PLAVATARMSG_H

#include "plMessage.h"

DllClass plAvatarMsg : public plMessage {
public:
    plAvatarMsg();
    virtual ~plAvatarMsg();

    DECLARE_CREATABLE(plAvatarMsg)
};

DllClass plArmatureUpdateMsg : public plAvatarMsg {
public:
    plArmatureUpdateMsg();
    virtual ~plArmatureUpdateMsg();

    DECLARE_CREATABLE(plArmatureUpdateMsg)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plAvatarSetTypeMsg : public plAvatarMsg {
private:
    bool fIsPlayer;

public:
    plAvatarSetTypeMsg();
    virtual ~plAvatarSetTypeMsg();

    DECLARE_CREATABLE(plAvatarSetTypeMsg)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plAvatarStealthModeMsg : public plAvatarMsg {
public:
    plAvatarStealthModeMsg();
    virtual ~plAvatarStealthModeMsg();

    DECLARE_CREATABLE(plAvatarStealthModeMsg)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plAvBrainGenericMsg : public plAvatarMsg {
public:
    enum Type {
        kNextStage, kPrevStage, kGotoStage, kSetLoopCount
    };

private:
    unsigned int fType, fWhichStage;
    bool fSetTime, fSetDirection, fNewDirection;
    float fNewTime, fTransitionTime;

public:
    plAvBrainGenericMsg();
    virtual ~plAvBrainGenericMsg();

    DECLARE_CREATABLE(plAvBrainGenericMsg)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

DllClass plAvTaskSeekDoneMsg : public plAvatarMsg {
private:
    bool fAborted;

public:
    plAvTaskSeekDoneMsg();
    virtual ~plAvTaskSeekDoneMsg();

    DECLARE_CREATABLE(plAvTaskSeekDoneMsg)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
