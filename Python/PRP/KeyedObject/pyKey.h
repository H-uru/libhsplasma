#ifndef _PYKEY_H
#define _PYKEY_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plWeakKey* fThis;
} pyKey;

typedef struct {
    PyObject_HEAD
    class plLocation* fThis;
} pyLocation;

extern PyTypeObject pyKey_Type;
PyObject* Init_pyKey_Type();
int pyKey_Check(PyObject* obj);
PyObject* pyKey_FromKey(class plWeakKey key);

extern PyTypeObject pyLocation_Type;
PyObject* Init_pyLocation_Type();
int pyLocation_Check(PyObject* obj);
PyObject* pyLocation_FromLocation(const class plLocation& loc);

};

#endif
