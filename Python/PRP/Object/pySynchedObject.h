#ifndef _PYSYNCHEDOBJECT_H
#define _PYSYNCHEDOBJECT_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plSynchedObject* fThis;
    bool fPyOwned;
} pySynchedObject;

extern PyTypeObject pySynchedObject_Type;
PyObject* Init_pySynchedObject_Type();
int pySynchedObject_Check(PyObject* obj);
PyObject* pySynchedObject_FromSynchedObject(class plSynchedObject* obj);

}

#endif
