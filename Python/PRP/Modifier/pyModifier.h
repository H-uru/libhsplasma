#ifndef _PYMODIFIER_H
#define _PYMODIFIER_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plModifier* fThis;
    bool fPyOwned;
} pyModifier;

typedef struct {
    PyObject_HEAD
    class plSingleModifier* fThis;
    bool fPyOwned;
} pySingleModifier;

typedef struct {
    PyObject_HEAD
    class plMultiModifier* fThis;
    bool fPyOwned;
} pyMultiModifier;

extern PyTypeObject pyModifier_Type;
PyObject* Init_pyModifier_Type();
int pyModifier_Check(PyObject* obj);
PyObject* pyModifier_FromModifier(class plModifier* mod);

extern PyTypeObject pySingleModifier_Type;
PyObject* Init_pySingleModifier_Type();
int pySingleModifier_Check(PyObject* obj);
PyObject* pySingleModifier_FromSingleModifier(class plSingleModifier* mod);

extern PyTypeObject pyMultiModifier_Type;
PyObject* Init_pyMultiModifier_Type();
int pyMultiModifier_Check(PyObject* obj);
PyObject* pyMultiModifier_FromMultiModifier(class plMultiModifier* mod);

}

#endif
