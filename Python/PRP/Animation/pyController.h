#ifndef _PYCONTROLLER_H
#define _PYCONTROLLER_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plController* fThis;
    bool fPyOwned;
} pyController;

typedef struct {
    PyObject_HEAD
    class plCompoundController* fThis;
    bool fPyOwned;
} pyCompoundController;

typedef struct {
    PyObject_HEAD
    class plTMController* fThis;
    bool fPyOwned;
} pyTMController;

extern PyTypeObject pyController_Type;
PyObject* Init_pyController_Type();
int pyController_Check(PyObject* obj);
PyObject* pyController_FromController(class plController* controller);

extern PyTypeObject pyCompoundController_Type;
PyObject* Init_pyCompoundController_Type();
int pyCompoundController_Check(PyObject* obj);
PyObject* pyCompoundController_FromCompoundController(class plCompoundController* controller);

extern PyTypeObject pyTMController_Type;
PyObject* Init_pyTMController_Type();
int pyTMController_Check(PyObject* obj);
PyObject* pyTMController_FromTMController(class plTMController* controller);

}

#endif
