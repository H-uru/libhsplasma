#include "plResponderModifier.h"
#include "Debug/plDebug.h"

// plResponderModifier::plResponderCmd //
plResponderModifier::plResponderCmd::plResponderCmd() : fMsg(NULL), fWaitOn(-1) { }

plResponderModifier::plResponderCmd::~plResponderCmd() {
    if (fMsg != NULL)
        delete fMsg;
}


// plResponderModifier //
plResponderModifier::plResponderModifier()
                   : fCurState(0), fEnabled(true), fFlags(0) { }

plResponderModifier::~plResponderModifier() { }

IMPLEMENT_CREATABLE(plResponderModifier, kResponderModifier, plSingleModifier)

void plResponderModifier::read(hsStream* S, plResManager* mgr) {
    plSingleModifier::read(S, mgr);

    fStates.setSize(S->readByte());
    for (size_t i=0; i<fStates.getSize(); i++) {
        fStates[i].fNumCallbacks = S->readByte();
        fStates[i].fSwitchToState = S->readByte();
        fStates[i].fCmds.setSize(S->readByte());
        for (size_t j=0; j<fStates[i].fCmds.getSize(); j++) {
            fStates[i].fCmds[j].fMsg = plMessage::Convert(mgr->ReadCreatable(S));
            fStates[i].fCmds[j].fWaitOn = S->readByte();
            if (fStates[i].fCmds[j].fMsg == NULL)
                throw hsNotImplementedException(__FILE__, __LINE__, "Responder Message");
        }
        fStates[i].fWaitToCmd.clear();
        size_t count = S->readByte();
        for (size_t j=0; j<count; j++) {
            hsByte wait = S->readByte();
            fStates[i].fWaitToCmd[wait] = S->readByte();
        }
    }

    hsByte state = S->readByte();
    if (state >= 0 && (size_t)state < fStates.getSize()) {
        fCurState = state;
    } else {
        plDebug::Warning("Invalid state %d found, will default to 0", state);
        fCurState = 0;
    }
    fEnabled = S->readBool();
    fFlags = S->readByte();
}

void plResponderModifier::write(hsStream* S, plResManager* mgr) {
    plSingleModifier::write(S, mgr);

    S->writeByte(fStates.getSize());
    for (size_t i=0; i<fStates.getSize(); i++) {
        S->writeByte(fStates[i].fNumCallbacks);
        S->writeByte(fStates[i].fSwitchToState);
        S->writeByte(fStates[i].fCmds.getSize());
        for (size_t j=0; j<fStates[i].fCmds.getSize(); j++) {
            mgr->WriteCreatable(S, fStates[i].fCmds[j].fMsg);
            S->writeByte(fStates[i].fCmds[j].fWaitOn);
        }
        S->writeByte(fStates[i].fWaitToCmd.size());
        std::map<hsByte, hsByte>::iterator wp = fStates[i].fWaitToCmd.begin();
        for ( ; wp != fStates[i].fWaitToCmd.end(); wp++) {
            S->writeByte(wp->first);    // key
            S->writeByte(wp->second);   // value
        }
    }

    S->writeByte(fCurState);
    S->writeBool(fEnabled);
    S->writeByte(fFlags);
}

void plResponderModifier::IPrcWrite(pfPrcHelper* prc) {
    plSingleModifier::IPrcWrite(prc);

    prc->startTag("ResponderModParams");
    prc->writeParam("CurState", fCurState);
    prc->writeParam("Enabled", fEnabled);
    prc->writeParam("Flags", fFlags);
    prc->endTag(true);

    prc->writeSimpleTag("States");
    for (size_t i=0; i<fStates.getSize(); i++) {
        prc->startTag("plResponderState");
        prc->writeParam("NumCallbacks", fStates[i].fNumCallbacks);
        prc->writeParam("SwitchToState", fStates[i].fSwitchToState);
        prc->endTag();
        
        prc->writeSimpleTag("Commands");
        for (size_t j=0; j<fStates[i].fCmds.getSize(); j++) {
            prc->writeSimpleTag("Command");
            fStates[i].fCmds[j].fMsg->prcWrite(prc);
            prc->startTag("WaitOn");
            prc->writeParam("value", fStates[i].fCmds[j].fWaitOn);
            prc->endTag(true);
            prc->closeTag();
        }
        prc->closeTag();    // Commands

        prc->writeSimpleTag("WaitToCmdTable");
        std::map<hsByte, hsByte>::iterator wp = fStates[i].fWaitToCmd.begin();
        for ( ; wp != fStates[i].fWaitToCmd.end(); wp++) {
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

void plResponderModifier::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "ResponderModParams") {
        fCurState = tag->getParam("CurState", "0").toInt();
        fEnabled = tag->getParam("Enabled", "false").toBool();
        fFlags = tag->getParam("Flags", "0").toUint();
    } else if (tag->getName() == "States") {
        fStates.setSize(tag->countChildren());
        const pfPrcTag* state = tag->getFirstChild();
        for (size_t i=0; i<fStates.getSize(); i++) {
            if (state->getName() != "plResponderState")
                throw pfPrcTagException(__FILE__, __LINE__, state->getName());
            fStates[i].fNumCallbacks = state->getParam("NumCallbacks", "0").toInt();
            fStates[i].fSwitchToState = state->getParam("SwitchToState", "-1").toInt();

            const pfPrcTag* child = state->getFirstChild();
            while (child != NULL) {
                if (child->getName() == "Commands") {
                    fStates[i].fCmds.setSize(child->countChildren());
                    const pfPrcTag* cmdChild = child->getFirstChild();
                    for (size_t j=0; j<fStates[i].fCmds.getSize(); j++) {
                        if (cmdChild->getName() != "Command")
                            throw pfPrcTagException(__FILE__, __LINE__, cmdChild->getName());
                        const pfPrcTag* subChild = cmdChild->getFirstChild();
                        while (subChild != NULL) {
                            if (subChild->getName() == "WaitOn") {
                                fStates[i].fCmds[j].fWaitOn = subChild->getParam("value", "-1").toInt();
                            } else {
                                fStates[i].fCmds[j].fMsg = plMessage::Convert(mgr->prcParseCreatable(subChild));
                            }
                            subChild = subChild->getNextSibling();
                        }
                        cmdChild = cmdChild->getNextSibling();
                    }
                } else if (child->getName() == "WaitToCmdTable") {
                    size_t nWaits = child->countChildren();
                    const pfPrcTag* waitChild = child->getFirstChild();
                    for (size_t j=0; j<nWaits; j++) {
                        if (waitChild->getName() != "Item")
                            throw pfPrcTagException(__FILE__, __LINE__, waitChild->getName());
                        hsByte wait = waitChild->getParam("Wait", "0").toInt();
                        fStates[i].fWaitToCmd[wait] = waitChild->getParam("Cmd", "0").toInt();
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


// plResponderEnableMsg //
plResponderEnableMsg::plResponderEnableMsg() { }
plResponderEnableMsg::~plResponderEnableMsg() { }

IMPLEMENT_CREATABLE(plResponderEnableMsg, kResponderEnableMsg, plMessage)

void plResponderEnableMsg::read(hsStream* S, plResManager* mgr) {
    plMessage::read(S, mgr);
    fEnable = S->readBool();
}

void plResponderEnableMsg::write(hsStream* S, plResManager* mgr) {
    plMessage::write(S, mgr);
    S->writeBool(fEnable);
}

void plResponderEnableMsg::IPrcWrite(pfPrcHelper* prc) {
    plMessage::IPrcWrite(prc);
    
    prc->startTag("ResponderParams");
    prc->writeParam("Enable", fEnable);
    prc->endTag(true);
}

void plResponderEnableMsg::IPrcParse(const pfPrcTag* tag, plResManager* mgr) {
    if (tag->getName() == "ResponderParams") {
        fEnable = tag->getParam("Enable", "true").toBool();
    } else {
        plMessage::IPrcParse(tag, mgr);
    }
}
