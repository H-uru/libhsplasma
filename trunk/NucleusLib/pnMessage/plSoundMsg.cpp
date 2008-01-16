#include "plSoundMsg.h"

plSoundMsg::plSoundMsg()
          : fBegin(0.0), fEnd(0.0), fLoop(false), fPlaying(false), fSpeed(0.0f),
            fTime(0.0), fIndex(0), fRepeats(0), fNameStr(0), fVolume(0.0f),
            fFadeType(kLinear) {
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

plSoundMsg::~plSoundMsg() { }

IMPLEMENT_CREATABLE(plSoundMsg, kSoundMsg, plMessageWithCallbacks)

void plSoundMsg::read(hsStream* S, plResManager* mgr) {
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
    fVolume = S->readInt();
    fFadeType = (FadeType)S->readByte();
}

void plSoundMsg::write(hsStream* S, plResManager* mgr) {
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
    S->writeByte((hsUbyte)fFadeType);
}

void plSoundMsg::prcWrite(pfPrcHelper* prc) {
    plMessageWithCallbacks::prcWrite(prc);

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
    prc->writeParam("FadeType", (hsUbyte)fFadeType);
    prc->endTag(true);

    prc->writeSimpleTag("Command");
    fCmd.prcWrite(prc);
    prc->closeTag();
}
