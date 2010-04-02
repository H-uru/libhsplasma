#ifndef _PLCLIMBMSG_H
#define _PLCLIMBMSG_H

#include "plMessage.h"

DllClass plClimbMsg : public plMessage {
    CREATABLE(plClimbMsg, kClimbMsg, plMessage)

public:
    enum Direction {
        kUp = 0x1,
        kDown = 0x2,
        kLeft = 0x4,
        kRight = 0x8,
        kCenter = 0x10
    };

    enum Command {
        kNoCommand = 0,
        kEnableClimb = 0x1,
        kEnableDismount = 0x2,
        kFallOff = 0x4,
        kRelease = 0x8,
        kStartClimbing = 0x8
    };

protected:
    unsigned int fCommand;
    unsigned int fDirection;
    bool fStatus;
    plKey fTarget;

public:
    plClimbMsg();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
