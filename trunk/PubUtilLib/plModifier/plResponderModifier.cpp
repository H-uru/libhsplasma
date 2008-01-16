#include "plResponderModifier.h"

// plResponderModifier::plResponderCmd //
plResponderModifier::plResponderCmd::plResponderCmd() : fMsg(NULL), fWaitOn(-1) { }

plResponderModifier::plResponderCmd::~plResponderCmd() {
    if (fMsg) delete fMsg;
}


// plResponderModifier //
plResponderModifier::plResponderModifier()
                   : fCurState(0), fCurCommand(-1), fNetRequest(false),
                     fEnabled(true), fEnter(false), fGotFirstLoad(false),
                     fFlags(0), fNotifyMsgFlags(0) { }

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
        fprintf(stderr, "Invalid state %d found, will default to 0\n", state);
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

void plResponderModifier::prcWrite(pfPrcHelper* prc) {
    plSingleModifier::prcWrite(prc);

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
            fStates[i].fCmds[j].fMsg->prcWrite(prc);
            prc->closeTag();

            prc->startTag("WaitOn");
            prc->writeParam("value", fStates[i].fCmds[j].fWaitOn);
            prc->endTag(true);
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
    prc->closeTag();
}
