#ifndef _PLRESPONDERMODIFIER_H
#define _PLRESPONDERMODIFIER_H

#include "NucleusLib/pnModifier/plModifier.h"

DllClass plResponderModifier : public plSingleModifier {
public:
    DllClass plResponderCmd {
    public:
        plMessage* fMsg;
        hsByte fWaitOn;

        plResponderCmd();
        ~plResponderCmd();
    };

    DllClass plResponderState {
    public:
        hsTArray<plResponderCmd> fCmds;
        hsByte fNumCallbacks, fSwitchToState;
        std::map<hsByte, hsByte> fWaitToCmd;
    };

    enum {
        kDetectTrigger = 0x1,
        kDetectUnTrigger = 0x2,
        kSkipFFSound = 0x4
    };

protected:
    hsTArray<plResponderState> fStates;
    signed char fCurState, fCurCommand;
    bool fNetRequest, fEnabled;
    hsBitVector fCompletedEvents;
    plKey fPlayerKey, fTriggerer;
    bool fEnter, fGotFirstLoad;
    //plResponderSDLModifier* fResponderSDLMod;
    unsigned char fFlags;
    unsigned long fNotifyMsgFlags;

public:
    plResponderModifier();
    virtual ~plResponderModifier();

    DECLARE_CREATABLE(plResponderModifier)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

DllClass plResponderEnableMsg : public plMessage {
protected:
    bool fEnable;

public:
    plResponderEnableMsg();
    virtual ~plResponderEnableMsg();

    DECLARE_CREATABLE(plResponderEnableMsg)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);
    virtual void prcWrite(pfPrcHelper* prc);
};

#endif
