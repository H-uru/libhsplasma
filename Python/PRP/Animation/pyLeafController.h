#ifndef _PYLEAFCONTROLLER_H
#define _PYLEAFCONTROLLER_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plLeafController* fThis;
    bool fPyOwned;
} pyLeafController;

typedef struct {
    PyObject_HEAD
    class plEaseController* fThis;
    bool fPyOwned;
} pyEaseController;

typedef struct {
    PyObject_HEAD
    class plMatrix33Controller* fThis;
    bool fPyOwned;
} pyMatrix33Controller;

typedef struct {
    PyObject_HEAD
    class plMatrix44Controller* fThis;
    bool fPyOwned;
} pyMatrix44Controller;

typedef struct {
    PyObject_HEAD
    class plPoint3Controller* fThis;
    bool fPyOwned;
} pyPoint3Controller;

typedef struct {
    PyObject_HEAD
    class plQuatController* fThis;
    bool fPyOwned;
} pyQuatController;

typedef struct {
    PyObject_HEAD
    class plScalarController* fThis;
    bool fPyOwned;
} pyScalarController;

typedef struct {
    PyObject_HEAD
    class plScaleValueController* fThis;
    bool fPyOwned;
} pyScaleValueController;

extern PyTypeObject pyLeafController_Type;
PyObject* Init_pyLeafController_Type();
int pyLeafController_Check(PyObject* obj);
PyObject* pyLeafController_FromLeafController(class plLeafController* controller);

extern PyTypeObject pyEaseController_Type;
PyObject* Init_pyEaseController_Type();
int pyEaseController_Check(PyObject* obj);
PyObject* pyEaseController_FromEaseController(class plEaseController* controller);

extern PyTypeObject pyMatrix33Controller_Type;
PyObject* Init_pyMatrix33Controller_Type();
int pyMatrix33Controller_Check(PyObject* obj);
PyObject* pyMatrix33Controller_FromMatrix33Controller(class plMatrix33Controller* controller);

extern PyTypeObject pyMatrix44Controller_Type;
PyObject* Init_pyMatrix44Controller_Type();
int pyMatrix44Controller_Check(PyObject* obj);
PyObject* pyMatrix44Controller_FromMatrix44Controller(class plMatrix44Controller* controller);

extern PyTypeObject pyPoint3Controller_Type;
PyObject* Init_pyPoint3Controller_Type();
int pyPoint3Controller_Check(PyObject* obj);
PyObject* pyPoint3Controller_FromPoint3Controller(class plPoint3Controller* controller);

extern PyTypeObject pyQuatController_Type;
PyObject* Init_pyQuatController_Type();
int pyQuatController_Check(PyObject* obj);
PyObject* pyQuatController_FromQuatController(class plQuatController* controller);

extern PyTypeObject pyScalarController_Type;
PyObject* Init_pyScalarController_Type();
int pyScalarController_Check(PyObject* obj);
PyObject* pyScalarController_FromScalarController(class plScalarController* controller);

extern PyTypeObject pyScaleValueController_Type;
PyObject* Init_pyScaleValueController_Type();
int pyScaleValueController_Check(PyObject* obj);
PyObject* pyScaleValueController_FromScaleValueController(class plScaleValueController* controller);

}

#endif
