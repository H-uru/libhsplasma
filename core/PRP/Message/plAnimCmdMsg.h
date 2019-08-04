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

#ifndef _PLANIMCMDMSG_H
#define _PLANIMCMDMSG_H

#include "plMessageWithCallbacks.h"
#include "Util/hsBitVector.h"

class PLASMA_DLL plAnimCmdMsg : public plMessageWithCallbacks
{
    CREATABLE(plAnimCmdMsg, kAnimCmdMsg, plMessageWithCallbacks)

public:
    enum ModCmds
    {
        kContinue, kStop, kSetLooping, kUnSetLooping, kSetBegin, kSetEnd,
        kSetLoopEnd, kSetLoopBegin, kSetSpeed, kGoToTime, kSetBackwards,
        kSetForwards, kToggleState, kAddCallbacks, kRemoveCallbacks,
        kGoToBegin, kGoToEnd, kGoToLoopBegin, kGoToLoopEnd, kIncrementForward,
        kIncrementBackward, kRunForward, kRunBackward, kPlayToTime,
        kPlayToPercentage, kFastForward, kGoToPercent, kNumCmds
    };

protected:
    ST::string fAnimName, fLoopName;
    hsBitVector fCmd;
    float fBegin, fEnd, fLoopBegin, fLoopEnd, fSpeed;
    float fSpeedChangeRate, fTime;

public:
    plAnimCmdMsg();

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    ST::string getAnimName() const { return fAnimName; }
    ST::string getLoopName() const { return fLoopName; }
    bool getCmd(size_t cmd) const { return fCmd.get(cmd); }
    float getBegin() const { return fBegin; }
    float getEnd() const { return fEnd; }
    float getLoopBegin() const { return fLoopBegin; }
    float getLoopEnd() const { return fLoopEnd; }
    float getSpeed() const { return fSpeed; }
    float getSpeedChangeRate() const { return fSpeedChangeRate; }
    float getTime() const { return fTime; }

    void setAnimName(const ST::string& value) { fAnimName = value; }
    void setLoopName(const ST::string& value) { fLoopName = value; }
    void setCmd(size_t cmd, bool value) { fCmd.set(cmd, value); }
    void setBegin(float value) { fBegin = value; }
    void setEnd(float value) { fEnd = value; }
    void setLoopBegin(float value) { fLoopBegin = value; }
    void setLoopEnd(float value) { fLoopEnd = value; }
    void setSpeed(float value) { fSpeed = value; }
    void setSpeedChangeRate(float value) { fSpeedChangeRate = value; }
    void setTime(float value) { fTime = value; }
};

#endif
