#include "plAnimCmdMsg.h"

plAnimCmdMsg::plAnimCmdMsg()
            : fBegin(0.0f), fEnd(0.0f), fLoopBegin(0.0f), fLoopEnd(0.0f),
              fSpeed(0.0f), fSpeedChangeRate(0.0f), fTime(0.0f) {
    fCmd.setName(kContinue, "kContinue");
    fCmd.setName(kStop, "kStop");
    fCmd.setName(kSetLooping, "kSetLooping");
    fCmd.setName(kUnSetLooping, "kUnSetLooping");
    fCmd.setName(kSetBegin, "kSetBegin");
    fCmd.setName(kSetEnd, "kSetEnd");
    fCmd.setName(kSetLoopEnd, "kSetLoopEnd");
    fCmd.setName(kSetLoopBegin, "kSetLoopBegin");
    fCmd.setName(kSetSpeed, "kSetSpeed");
    fCmd.setName(kGoToTime, "kGoToTime");
    fCmd.setName(kSetBackwards, "kSetBackwards");
    fCmd.setName(kSetForwards, "kSetForwards");
    fCmd.setName(kToggleState, "kToggleState");
    fCmd.setName(kAddCallbacks, "kAddCallbacks");
    fCmd.setName(kRemoveCallbacks, "kRemoveCallbacks");
    fCmd.setName(kGoToBegin, "kGoToBegin");
    fCmd.setName(kGoToEnd, "kGoToEnd");
    fCmd.setName(kGoToLoopBegin, "kGoToLoopBegin");
    fCmd.setName(kGoToLoopEnd, "kGoToLoopEnd");
    fCmd.setName(kIncrementForward, "kIncrementForward");
    fCmd.setName(kIncrementBackward, "kIncrementBackward");
    fCmd.setName(kRunForward, "kRunForward");
    fCmd.setName(kRunBackward, "kRunBackward");
    fCmd.setName(kPlayToTime, "kPlayToTime");
    fCmd.setName(kPlayToPercentage, "kPlayToPercentage");
    fCmd.setName(kFastForward, "kFastForward");
    fCmd.setName(kGoToPercent, "kGoToPercent");
}

plAnimCmdMsg::~plAnimCmdMsg() { }

IMPLEMENT_CREATABLE(plAnimCmdMsg, kAnimCmdMsg, plMessageWithCallbacks)

void plAnimCmdMsg::read(hsStream* S, plResManager* mgr) {
    plMessageWithCallbacks::read(S, mgr);

    fCmd.read(S);
    fBegin = S->readFloat();
    fEnd = S->readFloat();
    fLoopEnd = S->readFloat();
    fLoopBegin = S->readFloat();
    fSpeed = S->readFloat();
    fSpeedChangeRate = S->readFloat();
    fTime = S->readFloat();
    fAnimName = S->readSafeStr();
    fLoopName = S->readSafeStr();
}

void plAnimCmdMsg::write(hsStream* S, plResManager* mgr) {
    plMessageWithCallbacks::write(S, mgr);

    fCmd.write(S);
    S->writeFloat(fBegin);
    S->writeFloat(fEnd);
    S->writeFloat(fLoopEnd);
    S->writeFloat(fLoopBegin);
    S->writeFloat(fSpeed);
    S->writeFloat(fSpeedChangeRate);
    S->writeFloat(fTime);
    S->writeSafeStr(fAnimName);
    S->writeSafeStr(fLoopName);
}

void plAnimCmdMsg::IPrcWrite(pfPrcHelper* prc) {
    plMessageWithCallbacks::IPrcWrite(prc);

    prc->startTag("AnimParams");
    prc->writeParam("Begin", fBegin);
    prc->writeParam("End", fEnd);
    prc->writeParam("LoopBegin", fLoopBegin);
    prc->writeParam("LoopEnd", fLoopEnd);
    prc->writeParam("Speed", fSpeed);
    prc->writeParam("SpeedChangeRate", fSpeedChangeRate);
    prc->writeParam("Time", fTime);
    prc->endTag(true);

    prc->startTag("Anims");
    prc->writeParam("AnimName", fAnimName);
    prc->writeParam("LoopName", fLoopName);
    prc->endTag(true);

    prc->writeSimpleTag("Command");
    fCmd.prcWrite(prc);
    prc->closeTag();
}
