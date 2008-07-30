#ifndef _PYGEOMETRY3_H
#define _PYGEOMETRY3_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class hsVector3* fThis;
} pyVector3;

extern PyTypeObject pyVector3_Type;
PyObject* Init_pyVector3_Type();
int pyVector3_Check(PyObject* obj);
PyObject* pyVector3_FromVector3(const class hsVector3& vec);

}

#endif
