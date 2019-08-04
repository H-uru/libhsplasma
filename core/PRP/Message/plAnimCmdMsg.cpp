/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "plAnimCmdMsg.h"

plAnimCmdMsg::plAnimCmdMsg()
    : fBegin(), fEnd(), fLoopBegin(), fLoopEnd(), fSpeed(), fSpeedChangeRate(),
      fTime()
{
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

void plAnimCmdMsg::read(hsStream* S, plResManager* mgr)
{
    plMessageWithCallbacks::read(S, mgr);

    fCmd.read(S);
    if (S->getVer().isUru() || S->getVer().isUniversal()) {
        fBegin = S->readFloat();
        fEnd = S->readFloat();
        fLoopEnd = S->readFloat();
        fLoopBegin = S->readFloat();
        fSpeed = S->readFloat();
        fSpeedChangeRate = S->readFloat();
        fTime = S->readFloat();
    } else {
        if (fCmd[kSetBegin])
            fBegin = S->readFloat();
        if (fCmd[kSetEnd])
            fEnd = S->readFloat();
        if (fCmd[kSetLoopBegin])
            fLoopBegin = S->readFloat();
        if (fCmd[kSetLoopEnd])
            fLoopEnd = S->readFloat();
        if (fCmd[kSetSpeed]) {
            fSpeed = S->readFloat();
            fSpeedChangeRate = S->readFloat();
        }
        if (fCmd[kGoToTime] || fCmd[kPlayToTime] || fCmd[kPlayToPercentage])
            fTime = S->readFloat();
    }
    fAnimName = S->readSafeStr();
    fLoopName = S->readSafeStr();
}

void plAnimCmdMsg::write(hsStream* S, plResManager* mgr)
{
    plMessageWithCallbacks::write(S, mgr);

    fCmd.write(S);
    if (S->getVer().isUru() || S->getVer().isUniversal()) {
        S->writeFloat(fBegin);
        S->writeFloat(fEnd);
        S->writeFloat(fLoopEnd);
        S->writeFloat(fLoopBegin);
        S->writeFloat(fSpeed);
        S->writeFloat(fSpeedChangeRate);
        S->writeFloat(fTime);
    } else {
        if (fCmd[kSetBegin])
            S->writeFloat(fBegin);
        if (fCmd[kSetEnd])
            S->writeFloat(fEnd);
        if (fCmd[kSetLoopBegin])
            S->writeFloat(fLoopBegin);
        if (fCmd[kSetLoopEnd])
            S->writeFloat(fLoopEnd);
        if (fCmd[kSetSpeed]) {
            S->writeFloat(fSpeed);
            S->writeFloat(fSpeedChangeRate);
        }
        if (fCmd[kGoToTime] || fCmd[kPlayToTime] || fCmd[kPlayToPercentage])
            S->writeFloat(fTime);
    }
    S->writeSafeStr(fAnimName);
    S->writeSafeStr(fLoopName);
}

void plAnimCmdMsg::IPrcWrite(pfPrcHelper* prc)
{
    plMessageWithCallbacks::IPrcWrite(prc);

    prc->writeSimpleTag("Command");
    fCmd.prcWrite(prc);
    prc->closeTag();

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
}

void plAnimCmdMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "Command") {
        if (tag->hasChildren())
            fCmd.prcParse(tag->getFirstChild());
    } else if (tag->getName() == "AnimParams") {
        fBegin = tag->getParam("Begin", "0").to_float();
        fEnd = tag->getParam("End", "0").to_float();
        fLoopBegin = tag->getParam("LoopBegin", "0").to_float();
        fLoopEnd = tag->getParam("LoopEnd", "0").to_float();
        fSpeed = tag->getParam("Speed", "0").to_float();
        fSpeedChangeRate = tag->getParam("SpeedChangeRate", "0").to_float();
        fTime = tag->getParam("Time", "0").to_float();
    } else if (tag->getName() == "Anims") {
        fAnimName = tag->getParam("AnimName", "");
        fLoopName = tag->getParam("LoopName", "");
    } else {
        plMessageWithCallbacks::IPrcParse(tag, mgr);
    }
}
