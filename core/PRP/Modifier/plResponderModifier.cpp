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

#include "plResponderModifier.h"
#include "Debug/plDebug.h"

/* plResponderModifier::plResponderState */
plResponderModifier::plResponderState::~plResponderState()
{
    for (auto cmd = fCmds.begin(); cmd != fCmds.end(); ++cmd)
        delete *cmd;
}

void plResponderModifier::plResponderState::addCommand(plMessage* msg, int8_t waitOn)
{
    fCmds.push_back(new plResponderCmd(msg, waitOn));
}

void plResponderModifier::plResponderState::delCommand(size_t idx)
{
    delete fCmds[idx];
    fCmds.erase(fCmds.begin() + idx);
}

void plResponderModifier::plResponderState::clearCommands()
{
    for (auto cmd = fCmds.begin(); cmd != fCmds.end(); ++cmd)
        delete *cmd;
    fCmds.clear();
}


/* plResponderModifier */
plResponderModifier::~plResponderModifier()
{
    for (auto state = fStates.begin(); state != fStates.end(); ++state)
        delete *state;
}

void plResponderModifier::read(hsStream* S, plResManager* mgr)
{
    plSingleModifier::read(S, mgr);

    clearStates();
    fStates.resize(S->readByte());
    for (size_t i=0; i<fStates.size(); i++) {
        fStates[i] = new plResponderState();
        fStates[i]->fNumCallbacks = S->readByte();
        fStates[i]->fSwitchToState = S->readByte();
        fStates[i]->fCmds.resize(S->readByte());
        for (size_t j=0; j<fStates[i]->fCmds.size(); j++) {
            auto msg = mgr->ReadCreatableC<plMessage>(S);
            int8_t waitOn = S->readByte();
            fStates[i]->fCmds[j] = new plResponderCmd(msg, waitOn);
            if (msg == nullptr)
                throw hsNotImplementedException(__FILE__, __LINE__, "Responder Message");
        }
        size_t count = S->readByte();
        for (size_t j=0; j<count; j++) {
            int8_t wait = S->readByte();
            fStates[i]->fWaitToCmd[wait] = S->readByte();
        }
    }

    int8_t state = S->readByte();
    if (state >= 0 && (size_t)state < fStates.size()) {
        fCurState = state;
    } else {
        plDebug::Warning("Invalid state {} found, will default to 0", state);
        fCurState = 0;
    }
    fEnabled = S->readBool();
    fFlags = S->readByte();
}

void plResponderModifier::write(hsStream* S, plResManager* mgr)
{
    plSingleModifier::write(S, mgr);

    S->writeByte(fStates.size());
    for (size_t i=0; i<fStates.size(); i++) {
        S->writeByte(fStates[i]->fNumCallbacks);
        S->writeByte(fStates[i]->fSwitchToState);
        S->writeByte(fStates[i]->fCmds.size());
        for (size_t j=0; j<fStates[i]->fCmds.size(); j++) {
            mgr->WriteCreatable(S, fStates[i]->fCmds[j]->fMsg);
            S->writeByte(fStates[i]->fCmds[j]->fWaitOn);
        }
        S->writeByte(fStates[i]->fWaitToCmd.size());
        std::map<int8_t, int8_t>::iterator wp = fStates[i]->fWaitToCmd.begin();
        for ( ; wp != fStates[i]->fWaitToCmd.end(); wp++) {
            S->writeByte(wp->first);    // key
            S->writeByte(wp->second);   // value
        }
    }

    S->writeByte(fCurState);
    S->writeBool(fEnabled);
    S->writeByte(fFlags);
}

void plResponderModifier::IPrcWrite(pfPrcHelper* prc)
{
    plSingleModifier::IPrcWrite(prc);

    prc->startTag("ResponderModParams");
    prc->writeParam("CurState", fCurState);
    prc->writeParam("Enabled", fEnabled);
    prc->writeParam("Flags", fFlags);
    prc->endTag(true);

    prc->writeSimpleTag("States");
    for (size_t i=0; i<fStates.size(); i++) {
        prc->startTag("plResponderState");
        prc->writeParam("NumCallbacks", fStates[i]->fNumCallbacks);
        prc->writeParam("SwitchToState", fStates[i]->fSwitchToState);
        prc->endTag();

        prc->writeSimpleTag("Commands");
        for (size_t j=0; j<fStates[i]->fCmds.size(); j++) {
            prc->writeSimpleTag("Command");
            fStates[i]->fCmds[j]->fMsg->prcWrite(prc);
            prc->startTag("WaitOn");
            prc->writeParam("value", fStates[i]->fCmds[j]->fWaitOn);
            prc->endTag(true);
            prc->closeTag();
        }
        prc->closeTag();    // Commands

        prc->writeSimpleTag("WaitToCmdTable");
        std::map<int8_t, int8_t>::iterator wp = fStates[i]->fWaitToCmd.begin();
        for ( ; wp != fStates[i]->fWaitToCmd.end(); wp++) {
            prc->startTag("Item");
            prc->writeParam("Wait", wp->first);
            prc->writeParam("Cmd", wp->second);
            prc->endTag(true);
        }
        prc->closeTag();    // WaitToCmdTable

        prc->closeTag();    // plResponderState
    }
    prc->closeTag();    // States
}

void plResponderModifier::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "ResponderModParams") {
        fCurState = tag->getParam("CurState", "0").to_int();
        fEnabled = tag->getParam("Enabled", "false").to_bool();
        fFlags = tag->getParam("Flags", "0").to_uint();
    } else if (tag->getName() == "States") {
        clearStates();
        fStates.resize(tag->countChildren());
        const pfPrcTag* state = tag->getFirstChild();
        for (size_t i=0; i<fStates.size(); i++) {
            if (state->getName() != "plResponderState")
                throw pfPrcTagException(__FILE__, __LINE__, state->getName());
            fStates[i] = new plResponderState();
            fStates[i]->fNumCallbacks = state->getParam("NumCallbacks", "0").to_int();
            fStates[i]->fSwitchToState = state->getParam("SwitchToState", "-1").to_int();

            const pfPrcTag* child = state->getFirstChild();
            while (child) {
                if (child->getName() == "Commands") {
                    fStates[i]->fCmds.resize(child->countChildren());
                    const pfPrcTag* cmdChild = child->getFirstChild();
                    for (size_t j=0; j<fStates[i]->fCmds.size(); j++) {
                        if (cmdChild->getName() != "Command")
                            throw pfPrcTagException(__FILE__, __LINE__, cmdChild->getName());
                        plMessage* msg = nullptr;
                        int8_t waitOn = -1;
                        const pfPrcTag* subChild = cmdChild->getFirstChild();
                        while (subChild) {
                            if (subChild->getName() == "WaitOn") {
                                waitOn = subChild->getParam("value", "-1").to_int();
                            } else {
                                msg = mgr->prcParseCreatableC<plMessage>(subChild);
                            }
                            subChild = subChild->getNextSibling();
                        }
                        fStates[i]->fCmds[j] = new plResponderCmd(msg, waitOn);
                        cmdChild = cmdChild->getNextSibling();
                    }
                } else if (child->getName() == "WaitToCmdTable") {
                    size_t nWaits = child->countChildren();
                    const pfPrcTag* waitChild = child->getFirstChild();
                    for (size_t j=0; j<nWaits; j++) {
                        if (waitChild->getName() != "Item")
                            throw pfPrcTagException(__FILE__, __LINE__, waitChild->getName());
                        int8_t wait = waitChild->getParam("Wait", "0").to_int();
                        fStates[i]->fWaitToCmd[wait] = waitChild->getParam("Cmd", "0").to_int();
                        waitChild = waitChild->getNextSibling();
                    }
                } else {
                    throw pfPrcTagException(__FILE__, __LINE__, child->getName());
                }
                child = child->getNextSibling();
            }
            state = state->getNextSibling();
        }
    } else {
        plSingleModifier::IPrcParse(tag, mgr);
    }
}

void plResponderModifier::delState(size_t idx)
{
    delete fStates[idx];
    fStates.erase(fStates.begin() + idx);
}

void plResponderModifier::clearStates()
{
    for (auto state = fStates.begin(); state != fStates.end(); ++state)
        delete *state;
    fStates.clear();
}


/* plResponderEnableMsg */
void plResponderEnableMsg::read(hsStream* S, plResManager* mgr)
{
    plMessage::read(S, mgr);
    fEnable = S->readBool();
}

void plResponderEnableMsg::write(hsStream* S, plResManager* mgr)
{
    plMessage::write(S, mgr);
    S->writeBool(fEnable);
}

void plResponderEnableMsg::IPrcWrite(pfPrcHelper* prc)
{
    plMessage::IPrcWrite(prc);

    prc->startTag("ResponderParams");
    prc->writeParam("Enable", fEnable);
    prc->endTag(true);
}

void plResponderEnableMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr)
{
    if (tag->getName() == "ResponderParams") {
        fEnable = tag->getParam("Enable", "true").to_bool();
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}
