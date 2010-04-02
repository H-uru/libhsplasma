#ifndef _PLSOUNDMSG_H
#define _PLSOUNDMSG_H

#include "plMessageWithCallbacks.h"
#include "Util/hsBitVector.h"

DllClass plSoundMsg : public plMessageWithCallbacks {
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
