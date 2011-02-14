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

class PLASMA_DLL plSoundMsg : public plMessageWithCallbacks {
    CREATABLE(plSoundMsg, kSoundMsg, plMessageWithCallbacks)

public:
    enum ModCmds {
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

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
