#ifndef _PYPYTHONFILEMOD_H
#define _PYPYTHONFILEMOD_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plPythonParameter* fThis;
} pyPythonParameter;

typedef struct {
    PyObject_HEAD
    class plPythonFileMod* fThis;
    bool fPyOwned;
} pyPythonFileMod;

extern PyTypeObject pyPythonParameter_Type;
PyObject* Init_pyPythonParameter_Type();
int pyPythonParameter_Check(PyObject* obj);
PyObject* pyPythonParameter_FromPythonParameter(const class plPythonParameter& param);

extern PyTypeObject pyPythonFileMod_Type;
PyObject* Init_pyPythonFileMod_Type();
int pyPythonFileMod_Check(PyObject* obj);
PyObject* pyPythonFileMod_FromPythonFileMod(class plPythonFileMod* mod);

}

#endif
