#ifndef _PYUTIL_H
#define _PYUTIL_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class hsBitVector* fThis;
} pyBitVector;

extern PyTypeObject pyBitVector_Type;
PyObject* Init_pyBitVector_Type();
int pyBitVector_Check(PyObject* obj);

}

#endif
