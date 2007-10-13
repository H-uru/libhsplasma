#ifndef _PFGUICONTROLHANDLERS_H
#define _PFGUICONTROLHANDLERS_H

#include "../pfPRC/pfPrcHelper.h"

DllClass pfGUICtrlProcObject {
public:
    pfGUICtrlProcObject();
    virtual ~pfGUICtrlProcObject();
    
    virtual void DoSomething(class pfGUIControlMod* ctrl)=0;
};

DllClass pfGUIDialogProc : public pfGUICtrlProcObject {
public:
    enum ControlEvt { kExitMode };

protected:
    class pfGUIDialogMod* fDialog;

public:
    pfGUIDialogProc();
    virtual ~pfGUIDialogProc();
};

DllClass pfGUICtrlProcWriteableObject : public pfGUICtrlProcObject {
public:
    enum Types { kNull, kConsoleCmd, kPythonScript, kCloseDlg };

protected:
    unsigned int fType;

public:
    static pfGUICtrlProcWriteableObject* Read(hsStream* S);
    static void Write(hsStream* S, pfGUICtrlProcWriteableObject* proc);
    static void PrcWrite(pfPrcHelper* prc, pfGUICtrlProcWriteableObject* proc);

protected:
    virtual void IRead(hsStream* S)=0;
    virtual void IWrite(hsStream* S)=0;
    virtual void IPrcWrite(pfPrcHelper* prc)=0;
};

DllClass pfGUICloseDlgProc : public pfGUICtrlProcWriteableObject {
public:
    pfGUICloseDlgProc();

    virtual void DoSomething(class pfGUIControlMod* ctrl);

protected:
    virtual void IRead(hsStream* S);
    virtual void IWrite(hsStream* S);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

DllClass pfGUIConsoleCmdProc : public pfGUICtrlProcWriteableObject {
protected:
    plString fCommand;

public:
    pfGUIConsoleCmdProc();

    virtual void DoSomething(class pfGUIControlMod* ctrl);

protected:
    virtual void IRead(hsStream* S);
    virtual void IWrite(hsStream* S);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

DllClass pfGUIPythonScriptProc : public pfGUICtrlProcWriteableObject {
public:
     pfGUIPythonScriptProc();

     virtual void DoSomething(class pfGUIControlMod* ctrl);

protected:
    virtual void IRead(hsStream* S);
    virtual void IWrite(hsStream* S);
    virtual void IPrcWrite(pfPrcHelper* prc);
};

#endif
