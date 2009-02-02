#ifndef _PYLOGICMODIFIER_H
#define _PYLOGICMODIFIER_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plLogicModBase* fThis;
    bool fPyOwned;
} pyLogicModBase;

typedef struct {
    PyObject_HEAD
    class plLogicModifier* fThis;
    bool fPyOwned;
} pyLogicModifier;

extern PyTypeObject pyLogicModBase_Type;
PyObject* Init_pyLogicModBase_Type();
int pyLogicModBase_Check(PyObject* obj);
PyObject* pyLogicModBase_FromLogicModBase(class plLogicModBase* mod);

extern PyTypeObject pyLogicModifier_Type;
PyObject* Init_pyLogicModifier_Type();
int pyLogicModifier_Check(PyObject* obj);
PyObject* pyLogicModifier_FromLogicModifier(class plLogicModifier* mod);

}

#endif
