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

#ifndef _PLRESPONDERMODIFIER_H
#define _PLRESPONDERMODIFIER_H

#include "plModifier.h"
#include "PRP/Message/plMessage.h"

DllClass plResponderModifier : public plSingleModifier {
    CREATABLE(plResponderModifier, kResponderModifier, plSingleModifier)

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

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    const hsTArray<plResponderState*>& getStates() const { return fStates; }
    hsTArray<plResponderState*>& getStates() { return fStates; }
    void addState(plResponderState* state) { fStates.append(state); }
    void delState(size_t idx);
    void clearStates();

    bool isEnabled() const { return fEnabled; }
    signed char getCurState() const { return fCurState; }
    unsigned char getFlags() const { return fFlags; }

    void setEnabled(bool enabled) { fEnabled = enabled; }
    void setCurState(signed char state) { fCurState = state; }
    void setFlags(unsigned char flags) { fFlags = flags; }
};


DllClass plResponderEnableMsg : public plMessage {
    CREATABLE(plResponderEnableMsg, kResponderEnableMsg, plMessage)

protected:
    bool fEnable;

public:
    plResponderEnableMsg();

    virtual void read(hsStream* S, plResManager* mgr);
    virtual void write(hsStream* S, plResManager* mgr);

protected:
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag, plResManager* mgr);

public:
    bool getEnable() const { return fEnable; }
    void setEnable(bool enable) { fEnable = enable; }
};

#endif
