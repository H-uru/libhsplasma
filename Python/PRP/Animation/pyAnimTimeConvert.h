#ifndef _PYANIMTIMECONVERT_H
#define _PYANIMTIMECONVERT_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plAnimTimeConvert* fThis;
    bool fPyOwned;
} pyAnimTimeConvert;

extern PyTypeObject pyAnimTimeConvert_Type;
PyObject* Init_pyAnimTimeConvert_Type();
int pyAnimTimeConvert_Check(PyObject* obj);
PyObject* pyAnimTimeConvert_FromAnimTimeConvert(class plAnimTimeConvert* atc);

}

#endif
