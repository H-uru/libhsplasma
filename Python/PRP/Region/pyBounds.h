#ifndef _PYBOUNDS_H
#define _PYBOUNDS_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class hsBounds* fThis;
    bool fPyOwned;
} pyBounds;

typedef struct {
    PyObject_HEAD
    class hsBounds3* fThis;
    bool fPyOwned;
} pyBounds3;

typedef struct {
    PyObject_HEAD
    class hsBounds3Ext* fThis;
    bool fPyOwned;
} pyBounds3Ext;

typedef struct {
    PyObject_HEAD
    class hsBoundsOriented* fThis;
    bool fPyOwned;
} pyBoundsOriented;

extern PyTypeObject pyBounds_Type;
PyObject* Init_pyBounds_Type();
int pyBounds_Check(PyObject* obj);
PyObject* pyBounds_FromBounds(class hsBounds* bound);

extern PyTypeObject pyBounds3_Type;
PyObject* Init_pyBounds3_Type();
int pyBounds3_Check(PyObject* obj);
PyObject* pyBounds3_FromBounds3(class hsBounds3* bound);

extern PyTypeObject pyBounds3Ext_Type;
PyObject* Init_pyBounds3Ext_Type();
int pyBounds3Ext_Check(PyObject* obj);
PyObject* pyBounds3Ext_FromBounds3Ext(class hsBounds3Ext* bound);

extern PyTypeObject pyBoundsOriented_Type;
PyObject* Init_pyBoundsOriented_Type();
int pyBoundsOriented_Check(PyObject* obj);
PyObject* pyBoundsOriented_FromBoundsOriented(class hsBoundsOriented* bound);

}

#endif
