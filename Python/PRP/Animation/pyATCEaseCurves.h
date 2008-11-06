#ifndef _PYATCEASECURVES_H
#define _PYATCEASECURVES_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plATCEaseCurve* fThis;
    bool fPyOwned;
} pyATCEaseCurve;

typedef struct {
    PyObject_HEAD
    class plSplineEaseCurve* fThis;
    bool fPyOwned;
} pySplineEaseCurve;

typedef struct {
    PyObject_HEAD
    class plConstAccelEaseCurve* fThis;
    bool fPyOwned;
} pyConstAccelEaseCurve;

extern PyTypeObject pyATCEaseCurve_Type;
PyObject* Init_pyATCEaseCurve_Type();
int pyATCEaseCurve_Check(PyObject* obj);
PyObject* pyATCEaseCurve_FromATCEaseCurve(class plATCEaseCurve* curve);

extern PyTypeObject pySplineEaseCurve_Type;
PyObject* Init_pySplineEaseCurve_Type();
int pySplineEaseCurve_Check(PyObject* obj);
PyObject* pySplineEaseCurve_FromSplineEaseCurve(class plSplineEaseCurve* curve);

extern PyTypeObject pyConstAccelEaseCurve_Type;
PyObject* Init_pyConstAccelEaseCurve_Type();
int pyConstAccelEaseCurve_Check(PyObject* obj);
PyObject* pyConstAccelEaseCurve_FromConstAccelEaseCurve(class plConstAccelEaseCurve* curve);

}

#endif
