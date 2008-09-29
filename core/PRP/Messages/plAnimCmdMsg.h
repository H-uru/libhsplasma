#ifndef _PLANIMCMDMSG_H
#define _PLANIMCMDMSG_H

#include "plMessageWithCallbacks.h"
#include "Util/hsBitVector.h"

DllClass plAnimCmdMsg : public plMessageWithCallbacks {
public:
    enum ModCmds {
        kContinue, kStop, kSetLooping, kUnSetLooping, kSetBegin, kSetEnd,
        kSetLoopEnd, kSetLoopBegin, kSetSpeed, kGoToTime, kSetBackwards,
        kSetForwards, kToggleState, kAddCallbacks, kRemoveCallbacks,
        kGoToBegin, kGoToEnd, kGoToLoopBegin, kGoToLoopEnd, kIncrementForward,
        kIncrementBackward, kRunForward, kRunBackward, kPlayToTime,
        kPlayToPercentage, kFastForward, kGoToPercent, kNumCmds
    };

protected:
    plString fAnimName, fLoopName;
    hsBitVector fCmd;
    float fBegin, fEnd, fLoopBegin, fLoopEnd, fSpeed;
    float fSpeedChangeRate, fTime;

public:
    plAnimCmdMsg();
    virtual ~plAnimCmdMsg();

    DECLARE_CREATABLE(plAnimCmdMsg)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
