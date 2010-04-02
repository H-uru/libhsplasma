#ifndef _PLAVATARMSG_H
#define _PLAVATARMSG_H

#include "plMessage.h"

DllClass plAvatarMsg : public plMessage {
    CREATABLE(plAvatarMsg, kAvatarMsg, plMessage)
};


DllClass plArmatureUpdateMsg : public plAvatarMsg {
    CREATABLE(plArmatureUpdateMsg, kArmatureUpdateMsg, plAvatarMsg)

public:
    plArmatureUpdateMsg();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plAvatarSetTypeMsg : public plAvatarMsg {
    CREATABLE(plAvatarSetTypeMsg, kAvatarSetTypeMsg, plAvatarMsg)

private:
    bool fIsPlayer;

public:
    plAvatarSetTypeMsg();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plAvatarStealthModeMsg : public plAvatarMsg {
    CREATABLE(plAvatarStealthModeMsg, kAvatarStealthModeMsg, plAvatarMsg)

public:
    plAvatarStealthModeMsg();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plAvBrainGenericMsg : public plAvatarMsg {
    CREATABLE(plAvBrainGenericMsg, kAvBrainGenericMsg, plAvatarMsg)

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

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};


DllClass plAvTaskSeekDoneMsg : public plAvatarMsg {
    CREATABLE(plAvTaskSeekDoneMsg, kAvTaskSeekDoneMsg, plAvatarMsg)

private:
    bool fAborted;

public:
    plAvTaskSeekDoneMsg();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
