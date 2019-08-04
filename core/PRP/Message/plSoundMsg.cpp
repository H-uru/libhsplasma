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

#include "plSoundMsg.h"

plSoundMsg::plSoundMsg()
    : fBegin(), fEnd(), fLoop(), fPlaying(), fSpeed(), fTime(), fIndex(-1),
      fRepeats(), fNameStr(), fVolume(), fFadeType(kLinear)
{
    fCmd.setName(kPlay, "kPlay");
    fCmd.setName(kStop, "kStop");
    fCmd.setName(kSetLooping, "kSetLooping");
    fCmd.setName(kUnSetLooping, "kUnSetLooping");
    fCmd.setName(kSetBegin, "kSetBegin");
    fCmd.setName(kToggleState, "kToggleState");
    fCmd.setName(kAddCallbacks, "kAddCallbacks");
    fCmd.setName(kRemoveCallbacks, "kRemoveCallbacks");
    fCmd.setName(kGetStatus, "kGetStatus");
    fCmd.setName(kNumSounds, "kNumSounds");
    fCmd.setName(kStatusReply, "kStatusReply");
    fCmd.setName(kGoToTime, "kGoToTime");
    fCmd.setName(kSetVolume, "kSetVolume");
    fCmd.setName(kSetTalkIcon, "kSetTalkIcon");
    fCmd.setName(kClearTalkIcon, "kClearTalkIcon");
    fCmd.setName(kSetFadeIn, "kSetFadeIn");
    fCmd.setName(kSetFadeOut, "kSetFadeOut");
    fCmd.setName(kIsLocalOnly, "kIsLocalOnly");
    fCmd.setName(kSelectFromGroup, "kSelectFromGroup");
    fCmd.setName(kFastForwardPlay, "kFastForwardPlay");
    fCmd.setName(kFastForwardToggle, "kFastForwardToggle");
}

void plSoundMsg::read(hsStream* S, plResManager* mgr)
{
    plMessageWithCallbacks::read(S, mgr);

    fCmd.read(S);
    fBegin = S->readDouble();
    fEnd = S->readDouble();
    fLoop = S->readBool();
    fPlaying = S->readBool();
    fSpeed = S->readFloat();
    fTime = S->readDouble();
    fIndex = S->readInt();
    fRepeats = S->readInt();
    fNameStr = S->readInt();
    fVolume = S->readFloat();
    fFadeType = (FadeType)S->readByte();
}

void plSoundMsg::write(hsStream* S, plResManager* mgr)
{
    plMessageWithCallbacks::write(S, mgr);

    fCmd.write(S);
    S->writeDouble(fBegin);
    S->writeDouble(fEnd);
    S->writeBool(fLoop);
    S->writeBool(fPlaying);
    S->writeFloat(fSpeed);
    S->writeDouble(fTime);
    S->writeInt(fIndex);
    S->writeInt(fRepeats);
    S->writeInt(fNameStr);
    S->writeFloat(fVolume);
    S->writeByte((uint8_t)fFadeType);
}

void plSoundMsg::IPrcWrite(pfPrcHelper* prc)
{
    plMessageWithCallbacks::IPrcWrite(prc);

    prc->startTag("SoundParams");
    prc->writeParam("Begin", fBegin);
    prc->writeParam("End", fEnd);
    prc->writeParam("Loop", fLoop);
    prc->writeParam("Playing", fPlaying);
    prc->writeParam("Speed", fSpeed);
    prc->writeParam("Time", fTime);
    prc->writeParam("Index", fIndex);
    prc->writeParam("Repeats", fRepeats);
    prc->writeParam("NameStr", fNameStr);
    prc->writeParam("Volume", fVolume);
    prc->writeParam("FadeType", (uint8_t)fFadeType);
    prc->endTag(true);

    prc->writeSimpleTag("Command");
    fCmd.prcWrite(prc);
    prc->closeTag();
}

void plSoundMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "SoundParams") {
        fBegin = tag->getParam("Begin", "0").to_float();
        fEnd = tag->getParam("End", "0").to_float();
        fLoop = tag->getParam("Loop", "false").to_bool();
        fPlaying = tag->getParam("Playing", "false").to_bool();
        fSpeed = tag->getParam("Speed", "0").to_float();
        fTime = tag->getParam("Time", "0").to_float();
        fIndex = tag->getParam("Index", "0").to_int();
        fRepeats = tag->getParam("Repeats", "0").to_int();
        fNameStr = tag->getParam("NameStr", "0").to_uint();
        fVolume = tag->getParam("Volume", "0").to_float();
        fFadeType = (FadeType)tag->getParam("FadeType", "0").to_int();
    } else if (tag->getName() == "Command") {
        if (tag->hasChildren())
            fCmd.prcParse(tag->getFirstChild());
    } else {
        plMessageWithCallbacks::IPrcParse(tag, mgr);
    }
}
