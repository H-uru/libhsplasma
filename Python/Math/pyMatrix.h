#ifndef _PYMATRIX_H
#define _PYMATRIX_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class hsMatrix33* fThis;
} pyMatrix33;

typedef struct {
    PyObject_HEAD
    class hsMatrix44* fThis;
} pyMatrix44;

extern PyTypeObject pyMatrix33_Type;
PyObject* Init_pyMatrix33_Type();
int pyMatrix33_Check(PyObject* obj);
PyObject* pyMatrix33_FromMatrix33(const class hsMatrix33& mat);

extern PyTypeObject pyMatrix44_Type;
PyObject* Init_pyMatrix44_Type();
int pyMatrix44_Check(PyObject* obj);
PyObject* pyMatrix44_FromMatrix44(const class hsMatrix44& mat);

}

#endif
