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

#ifndef _PLSOUNDMSG_H
#define _PLSOUNDMSG_H

#include "plMessageWithCallbacks.h"
#include "Util/hsBitVector.h"

class PLASMA_DLL plSoundMsg : public plMessageWithCallbacks
{
    CREATABLE(plSoundMsg, kSoundMsg, plMessageWithCallbacks)

public:
    enum ModCmds
    {
        kPlay, kStop, kSetLooping, kUnSetLooping, kSetBegin, kToggleState,
        kAddCallbacks, kRemoveCallbacks, kGetStatus, kNumSounds, kStatusReply,
        kGoToTime, kSetVolume, kSetTalkIcon, kClearTalkIcon, kSetFadeIn,
        kSetFadeOut, kIsLocalOnly, kSelectFromGroup, kNumCmds,
        kFastForwardPlay, kFastForwardToggle
    };

    enum FadeType { kLinear, kLogarithmic, kExponential };

protected:
    hsBitVector fCmd;
    double fBegin, fEnd;
    bool fLoop, fPlaying;
    float fSpeed;
    double fTime;
    int fIndex, fRepeats;
    unsigned int fNameStr;
    float fVolume;
    FadeType fFadeType;

public:
    plSoundMsg();

    void read(hsStream* S, plResManager* mgr) HS_OVERRIDE;
    void write(hsStream* S, plResManager* mgr) HS_OVERRIDE;

protected:
    void IPrcWrite(pfPrcHelper* prc) HS_OVERRIDE;
    void IPrcParse(const pfPrcTag* tag, plResManager* mgr) HS_OVERRIDE;

public:
    bool getCmd(size_t cmd) const { return fCmd.get(cmd); }
    void setCmd(size_t cmd, bool value=true) { fCmd.set(cmd, value); }

    double getBegin() const { return fBegin; }
    double getEnd() const { return fEnd; }
    bool getLoop() const { return fLoop; }
    bool getPlaying() const { return fPlaying; }
    float getSpeed() const { return fSpeed; }
    double getTime() const { return fTime; }
    int getIndex() const { return fIndex; }
    int getRepeats() const { return fRepeats; }
    unsigned int getNameStr() const { return fNameStr; }
    float getVolume() const { return fVolume; }
    FadeType getFadeType() const { return fFadeType; }

    void setBegin(double value) { fBegin = value; }
    void setEnd(double value) { fEnd = value; }
    void setLoop(bool value) { fLoop = value; }
    void setPlaying(bool value) { fPlaying = value; }
    void setSpeed(float value) { fSpeed = value; }
    void setTime(double value) { fTime = value; }
    void setIndex(int value) { fIndex = value; }
    void setRepeats(int value) { fRepeats = value; }
    void setNameStr(unsigned int value) { fNameStr = value; }
    void setVolume(float value) { fVolume = value; }
    void setFadeType(FadeType value) { fFadeType = value; }
};

#endif
