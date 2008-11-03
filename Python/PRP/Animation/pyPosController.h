#ifndef _PYPOSCONTROLLER_H
#define _PYPOSCONTROLLER_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plPosController* fThis;
    bool fPyOwned;
} pyPosController;

typedef struct {
    PyObject_HEAD
    class plSimplePosController* fThis;
    bool fPyOwned;
} pySimplePosController;

typedef struct {
    PyObject_HEAD
    class plCompoundPosController* fThis;
    bool fPyOwned;
} pyCompoundPosController;

extern PyTypeObject pyPosController_Type;
PyObject* Init_pyPosController_Type();
int pyPosController_Check(PyObject* obj);
PyObject* pyPosController_FromPosController(class plPosController* controller);

extern PyTypeObject pySimplePosController_Type;
PyObject* Init_pySimplePosController_Type();
int pySimplePosController_Check(PyObject* obj);
PyObject* pySimplePosController_FromSimplePosController(class plSimplePosController* controller);

extern PyTypeObject pyCompoundPosController_Type;
PyObject* Init_pyCompoundPosController_Type();
int pyCompoundPosController_Check(PyObject* obj);
PyObject* pyCompoundPosController_FromCompoundPosController(class plCompoundPosController* controller);

}

#endif
