#include "pfGUIControlHandlers.h"
#include "pfGUIControlMod.h"

/* pfGUICtrlProcObject */
pfGUICtrlProcObject::pfGUICtrlProcObject() { }
pfGUICtrlProcObject::~pfGUICtrlProcObject() { }


/* pfGUIDialogProc */
pfGUIDialogProc::pfGUIDialogProc() : fDialog(NULL) { }
pfGUIDialogProc::~pfGUIDialogProc() { }


/* pfGUICtrlProcWriteableObject */
pfGUICtrlProcWriteableObject* pfGUICtrlProcWriteableObject::Read(hsStream* S) {
    pfGUICtrlProcWriteableObject* proc;

    switch (S->readInt()) {
    case kConsoleCmd:
        proc = new pfGUIConsoleCmdProc();
        proc->IRead(S);
        break;
    case kPythonScript:
        proc = new pfGUIPythonScriptProc();
        proc->IRead(S);
        break;
    case kCloseDlg:
        proc = new pfGUICloseDlgProc();
        proc->IRead(S);
        break;
    default:
        proc = NULL;
    }

    return proc;
}

void pfGUICtrlProcWriteableObject::Write(hsStream* S, pfGUICtrlProcWriteableObject* proc) {
    if (proc == NULL) {
        S->writeInt(kNull);
    } else {
        S->writeInt(proc->fType);
        proc->IWrite(S);
    }
}

void pfGUICtrlProcWriteableObject::PrcWrite(pfPrcHelper* prc, pfGUICtrlProcWriteableObject* proc) {
    if (proc == NULL) {
        prc->startTag("pfGUICtrlProcObject");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    } else {
        proc->IPrcWrite(prc);
    }
}


/* pfGUICloseDlgProc */
pfGUICloseDlgProc::pfGUICloseDlgProc() {
    fType = kCloseDlg;
}

void pfGUICloseDlgProc::IRead(hsStream* S) { }
void pfGUICloseDlgProc::IWrite(hsStream* S) { }

void pfGUICloseDlgProc::IPrcWrite(pfPrcHelper* prc) {
    prc->startTag("pfGUICloseDlgProc");
    prc->endTag(true);
}

void pfGUICloseDlgProc::DoSomething(pfGUIControlMod* ctrl) {
    //ctrl->getOwnerDlg()->hide();
}


/* pfGUIConsoleCmdProc */
pfGUIConsoleCmdProc::pfGUIConsoleCmdProc() {
    fType = kConsoleCmd;
}

void pfGUIConsoleCmdProc::IRead(hsStream* S) {
    int len = S->readInt();
    if (len >= 0) {
        char* cmd = new char[len+1];
        S->read(len, cmd);
        cmd[len] = 0;
        fCommand = cmd;
        delete[] cmd;
    } else {
        fCommand = "";
    }
}

void pfGUIConsoleCmdProc::IWrite(hsStream* S) {
    S->writeInt(fCommand.len());
    S->write(fCommand.len(), fCommand.cstr());
}

void pfGUIConsoleCmdProc::IPrcWrite(pfPrcHelper* prc) {
    prc->startTag("pfGUIConsoleCmdProc");
    prc->writeParam("Command", fCommand.cstr());
    prc->endTag(true);
}

void pfGUIConsoleCmdProc::DoSomething(pfGUIControlMod* ctrl) {
    if (!fCommand.empty()) {
        /* plConsoleMsg* msg = new plConsoleMsg(kExecuteLine, fCommand);
         * plgDispatch::Dispatch()->MsgSend(msg, 0);
         */
    }
}


/* pfGUIPythonScriptProc */
pfGUIPythonScriptProc::pfGUIPythonScriptProc() {
    fType = kPythonScript;
}

void pfGUIPythonScriptProc::IRead(hsStream* S) { }
void pfGUIPythonScriptProc::IWrite(hsStream* S) { }

void pfGUIPythonScriptProc::IPrcWrite(pfPrcHelper* prc) {
    prc->startTag("pfGUIPythonScriptProc");
    prc->endTag(true);
}

void pfGUIPythonScriptProc::DoSomething(pfGUIControlMod* ctrl) { }
