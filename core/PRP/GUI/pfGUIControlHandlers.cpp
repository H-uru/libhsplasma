#include "pfGUIControlHandlers.h"
#include "pfGUIControlMod.h"

/* pfGUICtrlProcObject */
pfGUICtrlProcObject::pfGUICtrlProcObject() { }
pfGUICtrlProcObject::~pfGUICtrlProcObject() { }


/* pfGUIDialogProc */
pfGUIDialogProc::pfGUIDialogProc() { }
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

pfGUICtrlProcWriteableObject* pfGUICtrlProcWriteableObject::PrcParse(const pfPrcTag* tag) {
    pfGUICtrlProcWriteableObject* proc;

    if (tag->getName() == "pfGUICtrlProcObject") {
        if (tag->getParam("NULL", "false").toBool())
            return NULL;
        throw pfPrcParseException(__FILE__, __LINE__, "Abstract class");
    } else if (tag->getName() == "pfGUICloseDlgProc") {
        proc = new pfGUICloseDlgProc();
        proc->IPrcParse(tag);
        return proc;
    } else if (tag->getName() == "pfGUIConsoleCmdProc") {
        proc = new pfGUIConsoleCmdProc();
        proc->IPrcParse(tag);
        return proc;
    } else if (tag->getName() == "pfGUIPythonScriptProc") {
        proc = new pfGUIPythonScriptProc();
        proc->IPrcParse(tag);
        return proc;
    } else {
        throw pfPrcTagException(__FILE__, __LINE__, tag->getName());
    }
}

unsigned int pfGUICtrlProcWriteableObject::getType() const { return fType; }


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

void pfGUICloseDlgProc::IPrcParse(const pfPrcTag* tag) { }


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
    S->writeStr(fCommand);
}

void pfGUIConsoleCmdProc::IPrcWrite(pfPrcHelper* prc) {
    prc->startTag("pfGUIConsoleCmdProc");
    prc->writeParam("Command", fCommand);
    prc->endTag(true);
}

void pfGUIConsoleCmdProc::IPrcParse(const pfPrcTag* tag) {
    fCommand = tag->getParam("Command", "");
}

plString pfGUIConsoleCmdProc::getCommand() const { return fCommand; }
void pfGUIConsoleCmdProc::setCommand(const plString& cmd) { fCommand = cmd; }


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

void pfGUIPythonScriptProc::IPrcParse(const pfPrcTag* tag) { }
