#ifndef _PYBOUNDS_H
#define _PYBOUNDS_H

typedef struct {
    PyObject_HEAD
    class hsBounds* fThis;
} pyBounds;

typedef struct {
    PyObject_HEAD
    class hsBounds3* fThis;
} pyBounds3;

typedef struct {
    PyObject_HEAD
    class hsBounds3Ext* fThis;
} pyBounds3Ext;

typedef struct {
    PyObject_HEAD
    class hsBoundsOriented* fThis;
} pyBoundsOriented;

extern PyTypeObject pyBounds_Type;
PyObject* Init_pyBounds_Type();
PyObject* pyBounds_FromBounds(class hsBounds* bound);

extern PyTypeObject pyBounds3_Type;
PyObject* Init_pyBounds3_Type();
PyObject* pyBounds3_FromBounds3(class hsBounds3* bound);

extern PyTypeObject pyBounds3Ext_Type;
PyObject* Init_pyBounds3Ext_Type();
PyObject* pyBounds3Ext_FromBounds3Ext(class hsBounds3Ext* bound);

extern PyTypeObject pyBoundsOriented_Type;
PyObject* Init_pyBoundsOriented_Type();
PyObject* pyBoundsOriented_FromBoundsOriented(class hsBoundsOriented* bound);

#endif
