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


/* pfGUIConsoleCmdProc */
pfGUIConsoleCmdProc::pfGUIConsoleCmdProc() {
    fType = kConsoleCmd;
}

void pfGUIConsoleCmdProc::IRead(hsStream* S) {
    int len = S->readInt();
    fCommand = S->readStr(len);
}

void pfGUIConsoleCmdProc::IWrite(hsStream* S) {
    S->writeInt(fCommand.len());
    S->write(fCommand.len(), fCommand.cstr());
}

void pfGUIConsoleCmdProc::IPrcWrite(pfPrcHelper* prc) {
    prc->startTag("pfGUIConsoleCmdProc");
    prc->writeParam("Command", fCommand);
    prc->endTag(true);
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
