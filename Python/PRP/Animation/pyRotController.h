#ifndef _PYROTCONTROLLER_H
#define _PYROTCONTROLLER_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plRotController* fThis;
    bool fPyOwned;
} pyRotController;

typedef struct {
    PyObject_HEAD
    class plSimpleRotController* fThis;
    bool fPyOwned;
} pySimpleRotController;

typedef struct {
    PyObject_HEAD
    class plCompoundRotController* fThis;
    bool fPyOwned;
} pyCompoundRotController;

extern PyTypeObject pyRotController_Type;
PyObject* Init_pyRotController_Type();
int pyRotController_Check(PyObject* obj);
PyObject* pyRotController_FromRotController(class plRotController* controller);

extern PyTypeObject pySimpleRotController_Type;
PyObject* Init_pySimpleRotController_Type();
int pySimpleRotController_Check(PyObject* obj);
PyObject* pySimpleRotController_FromSimpleRotController(class plSimpleRotController* controller);

extern PyTypeObject pyCompoundRotController_Type;
PyObject* Init_pyCompoundRotController_Type();
int pyCompoundRotController_Check(PyObject* obj);
PyObject* pyCompoundRotController_FromCompoundRotController(class plCompoundRotController* controller);

}

#endif
