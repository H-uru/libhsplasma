#ifndef _PYSCALECONTROLLER_H
#define _PYSCALECONTROLLER_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plScaleController* fThis;
    bool fPyOwned;
} pyScaleController;

typedef struct {
    PyObject_HEAD
    class plSimpleScaleController* fThis;
    bool fPyOwned;
} pySimpleScaleController;

extern PyTypeObject pyScaleController_Type;
PyObject* Init_pyScaleController_Type();
int pyScaleController_Check(PyObject* obj);
PyObject* pyScaleController_FromScaleController(class plScaleController* controller);

extern PyTypeObject pySimpleScaleController_Type;
PyObject* Init_pySimpleScaleController_Type();
int pySimpleScaleController_Check(PyObject* obj);
PyObject* pySimpleScaleController_FromSimpleScaleController(class plSimpleScaleController* controller);

}

#endif
