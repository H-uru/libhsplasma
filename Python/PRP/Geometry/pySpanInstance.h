#ifndef _PYSPANINSTANCE_H
#define _PYSPANINSTANCE_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plSpanEncoding* fThis;
    bool fPyOwned;
} pySpanEncoding;

typedef struct {
    PyObject_HEAD
    class plSpanInstance* fThis;
    bool fPyOwned;
} pySpanInstance;

extern PyTypeObject pySpanEncoding_Type;
PyObject* Init_pySpanEncoding_Type();
int pySpanEncoding_Check(PyObject* obj);
PyObject* pySpanEncoding_FromSpanEncoding(class plSpanEncoding* encoding);

extern PyTypeObject pySpanInstance_Type;
PyObject* Init_pySpanInstance_Type();
int pySpanInstance_Check(PyObject* obj);
PyObject* pySpanInstance_FromSpanInstance(class plSpanInstance* instance);

}

#endif
