#ifndef _PYCREATABLE_H
#define _PYCREATABLE_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plCreatable* fThis;
    bool fPyOwned;
} pyCreatable;

typedef struct {
    PyObject_HEAD
    class plCreatableStub* fThis;
    bool fPyOwned;
} pyCreatableStub;

extern PyTypeObject pyCreatable_Type;
PyObject* Init_pyCreatable_Type();
int pyCreatable_Check(PyObject* obj);
PyObject* pyCreatable_FromCreatable(class plCreatable* pCre);

extern PyTypeObject pyCreatableStub_Type;
PyObject* Init_pyCreatableStub_Type();
int pyCreatableStub_Check(PyObject* obj);

};

#endif
