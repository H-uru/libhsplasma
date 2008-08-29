#ifndef _PYMATRIX44_H
#define _PYMATRIX44_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class hsMatrix44* fThis;
} pyMatrix44;

extern PyTypeObject pyMatrix44_Type;
PyObject* Init_pyMatrix44_Type();
int pyMatrix44_Check(PyObject* obj);
PyObject* pyMatrix44_FromMatrix44(const class hsMatrix44& mat);

}

#endif
