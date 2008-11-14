#ifndef _PYRESPONDERMODIFIER_H
#define _PYRESPONDERMODIFIER_H

#include <PRP/Modifier/plResponderModifier.h>

extern "C" {

typedef struct {
    PyObject_HEAD
    class plResponderModifier::plResponderCmd* fThis;
    bool fPyOwned;
} pyResponderModifier_Cmd;

typedef struct {
    PyObject_HEAD
    class plResponderModifier::plResponderState* fThis;
    bool fPyOwned;
} pyResponderModifier_State;

typedef struct {
    PyObject_HEAD
    class plResponderModifier* fThis;
    bool fPyOwned;
} pyResponderModifier;

typedef struct {
    PyObject_HEAD
    class plResponderEnableMsg* fThis;
    bool fPyOwned;
} pyResponderEnableMsg;

extern PyTypeObject pyResponderModifier_Cmd_Type;
PyObject* Init_pyResponderModifier_Cmd_Type();
int pyResponderModifier_Cmd_Check(PyObject* obj);
PyObject* pyResponderModifier_Cmd_FromResponderCmd(class plResponderModifier::plResponderCmd* cmd);

extern PyTypeObject pyResponderModifier_State_Type;
PyObject* Init_pyResponderModifier_State_Type();
int pyResponderModifier_State_Check(PyObject* obj);
PyObject* pyResponderModifier_State_FromResponderState(class plResponderModifier::plResponderState* state);

extern PyTypeObject pyResponderModifier_Type;
PyObject* Init_pyResponderModifier_Type();
int pyResponderModifier_Check(PyObject* obj);
PyObject* pyResponderModifier_FromResponderModifier(class plResponderModifier* mod);

extern PyTypeObject pyResponderEnableMsg_Type;
PyObject* Init_pyResponderEnableMsg_Type();
int pyResponderEnableMsg_Check(PyObject* obj);
PyObject* pyResponderEnableMsg_FromResponderEnableMsg(class plResponderEnableMsg* mod);

}

#endif
