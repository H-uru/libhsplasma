#ifndef _PLRESPONDERMODIFIER_H
#define _PLRESPONDERMODIFIER_H

#include "plModifier.h"

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
    signed char fCurState;
    bool fEnabled;
    unsigned char fFlags;

public:
    plResponderModifier();
    virtual ~plResponderModifier();

    DECLARE_CREATABLE(plResponderModifier)

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
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

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);
};

#endif
