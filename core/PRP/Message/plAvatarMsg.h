#ifndef _PLAVATARMSG_H
#define _PLAVATARMSG_H

#include "plMessage.h"

DllClass plAvatarMsg : public plMessage {
public:
    plAvatarMsg();
    virtual ~plAvatarMsg();

    DECLARE_CREATABLE(plAvatarMsg)
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

#endif
