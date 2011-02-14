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

#ifndef _PFGUICONTROLHANDLERS_H
#define _PFGUICONTROLHANDLERS_H

#include "Stream/pfPrcHelper.h"
#include "Stream/pfPrcParser.h"

class PLASMA_DLL pfGUICtrlProcObject {
public:
    pfGUICtrlProcObject() { }
    virtual ~pfGUICtrlProcObject() { }
};


class PLASMA_DLL pfGUIDialogProc : public pfGUICtrlProcObject { };


class PLASMA_DLL pfGUICtrlProcWriteableObject : public pfGUICtrlProcObject {
public:
    enum Types { kNull, kConsoleCmd, kPythonScript, kCloseDlg };

protected:
    unsigned int fType;

public:
    static pfGUICtrlProcWriteableObject* Read(hsStream* S);
    static void Write(hsStream* S, pfGUICtrlProcWriteableObject* proc);
    static void PrcWrite(pfPrcHelper* prc, pfGUICtrlProcWriteableObject* proc);
    static pfGUICtrlProcWriteableObject* PrcParse(const pfPrcTag* tag);

protected:
    virtual void IRead(hsStream* S)=0;
    virtual void IWrite(hsStream* S)=0;
    virtual void IPrcWrite(pfPrcHelper* prc)=0;
    virtual void IPrcParse(const pfPrcTag* tag)=0;

public:
    unsigned int getType() const { return fType; }
};


class PLASMA_DLL pfGUICloseDlgProc : public pfGUICtrlProcWriteableObject {
public:
    pfGUICloseDlgProc();

protected:
    virtual void IRead(hsStream* S);
    virtual void IWrite(hsStream* S);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag);
};


class PLASMA_DLL pfGUIConsoleCmdProc : public pfGUICtrlProcWriteableObject {
protected:
    plString fCommand;

public:
    pfGUIConsoleCmdProc();

protected:
    virtual void IRead(hsStream* S);
    virtual void IWrite(hsStream* S);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag);

public:
    plString getCommand() const { return fCommand; }
    void setCommand(const plString& cmd) { fCommand = cmd; }
};


class PLASMA_DLL pfGUIPythonScriptProc : public pfGUICtrlProcWriteableObject {
public:
     pfGUIPythonScriptProc();

protected:
    virtual void IRead(hsStream* S);
    virtual void IWrite(hsStream* S);
    virtual void IPrcWrite(pfPrcHelper* prc);
    virtual void IPrcParse(const pfPrcTag* tag);
};

#endif
