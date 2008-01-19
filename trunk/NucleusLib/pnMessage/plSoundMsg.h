#ifndef _PLSOUNDMSG_H
#define _PLSOUNDMSG_H

#include "plMessageWithCallbacks.h"
#include "CoreLib/hsBitVector.h"

DllClass plSoundMsg : public plMessageWithCallbacks {
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
    virtual ~plSoundMsg();

    DECLARE_CREATABLE(plSoundMsg)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
