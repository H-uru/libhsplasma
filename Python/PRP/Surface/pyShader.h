#ifndef _PYSHADER_H
#define _PYSHADER_H

extern "C" {

typedef struct {
    PyObject_HEAD
    class plShaderConst* fThis;
} pyShaderConst;

typedef struct {
    PyObject_HEAD
    class plShader* fThis;
    bool fPyOwned;
} pyShader;

extern PyTypeObject pyShaderConst_Type;
PyObject* Init_pyShaderConst_Type();
int pyShaderConst_Check(PyObject* obj);
PyObject* pyShaderConst_FromShaderConst(const class plShaderConst& sc);

extern PyTypeObject pyShader_Type;
PyObject* Init_pyShader_Type();
int pyShader_Check(PyObject* obj);
PyObject* pyShader_FromShader(class plShader* shader);

}

#endif
