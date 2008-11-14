#ifndef _PLRESPONDERMODIFIER_H
#define _PLRESPONDERMODIFIER_H

#include "plModifier.h"

DllClass plResponderModifier : public plSingleModifier {
public:
    DllClass plResponderCmd {
    public:
        plMessage* fMsg;
        hsByte fWaitOn;

        plResponderCmd(plMessage* msg = NULL, hsByte waitOn = -1);
        ~plResponderCmd();
    };

    DllClass plResponderState {
    public:
        hsTArray<plResponderCmd*> fCmds;
        hsByte fNumCallbacks, fSwitchToState;
        std::map<hsByte, hsByte> fWaitToCmd;

        plResponderState();
        ~plResponderState();

        void addCommand(plMessage* msg, hsByte waitOn);
        void delCommand(size_t idx);
        void clearCommands();
    };

    enum {
        kDetectTrigger = 0x1,
        kDetectUnTrigger = 0x2,
        kSkipFFSound = 0x4
    };

protected:
    hsTArray<plResponderState*> fStates;
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

public:
    size_t getNumStates() const;
    plResponderState* getState(size_t idx) const;
    void addState(plResponderState* state);
    void delState(size_t idx);
    void clearStates();

    bool isEnabled() const;
    size_t getCurState() const;
    unsigned char getFlags() const;

    void setEnabled(bool enabled);
    void setCurState(size_t state);
    void setFlags(unsigned char flags);
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

public:
    bool getEnable() const;
    void setEnable(bool enable);
};

#endif
