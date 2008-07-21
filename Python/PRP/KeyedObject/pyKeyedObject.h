#ifndef _PYKEYEDOBJECT_H
#define _PYKEYEDOBJECT_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class hsKeyedObject* fThis;
    bool fPyOwned;
} pyKeyedObject;

extern PyTypeObject pyKeyedObject_Type;
PyObject* Init_pyKeyedObject_Type();
int pyKeyedObject_Check(PyObject* obj);
PyObject* pyKeyedObject_FromKeyedObject(class hsKeyedObject* obj);

}

#endif
