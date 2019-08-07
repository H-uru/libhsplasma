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

#include "pfGUIControlHandlers.h"
#include "pfGUIControlMod.h"

/* pfGUICtrlProcWriteableObject */
pfGUICtrlProcWriteableObject* pfGUICtrlProcWriteableObject::Read(hsStream* S)
{
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
        proc = nullptr;
    }

    return proc;
}

void pfGUICtrlProcWriteableObject::Write(hsStream* S, pfGUICtrlProcWriteableObject* proc)
{
    if (proc == nullptr) {
        S->writeInt(kNull);
    } else {
        S->writeInt(proc->fType);
        proc->IWrite(S);
    }
}

void pfGUICtrlProcWriteableObject::PrcWrite(pfPrcHelper* prc, pfGUICtrlProcWriteableObject* proc)
{
    if (proc == nullptr) {
        prc->startTag("pfGUICtrlProcObject");
        prc->writeParam("NULL", true);
        prc->endTag(true);
    } else {
        proc->IPrcWrite(prc);
    }
}

pfGUICtrlProcWriteableObject* pfGUICtrlProcWriteableObject::PrcParse(const pfPrcTag* tag)
{
    pfGUICtrlProcWriteableObject* proc;

    if (tag->getName() == "pfGUICtrlProcObject") {
        if (tag->getParam("NULL", "false").to_bool())
            return nullptr;
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


/* pfGUICloseDlgProc */
void pfGUICloseDlgProc::IPrcWrite(pfPrcHelper* prc)
{
    prc->startTag("pfGUICloseDlgProc");
    prc->endTag(true);
}


/* pfGUIConsoleCmdProc */
void pfGUIConsoleCmdProc::IRead(hsStream* S)
{
    int len = S->readInt();
    fCommand = S->readStr(len);
}

void pfGUIConsoleCmdProc::IWrite(hsStream* S)
{
    S->writeInt(fCommand.size());
    S->writeStr(fCommand);
}

void pfGUIConsoleCmdProc::IPrcWrite(pfPrcHelper* prc)
{
    prc->startTag("pfGUIConsoleCmdProc");
    prc->writeParam("Command", fCommand);
    prc->endTag(true);
}

void pfGUIConsoleCmdProc::IPrcParse(const pfPrcTag* tag)
{
    fCommand = tag->getParam("Command", "");
}


/* pfGUIPythonScriptProc */
void pfGUIPythonScriptProc::IPrcWrite(pfPrcHelper* prc)
{
    prc->startTag("pfGUIPythonScriptProc");
    prc->endTag(true);
}
