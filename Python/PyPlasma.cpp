#include "PyPlasma.h"

PyObject* PlasmaString_To_PyString(const plString& str) {
    return PyString_FromString(str.cstr());
}

PyObject* PlasmaString_To_PyUnicode(const plString& str) {
    return PyUnicode_DecodeUTF8(str.cstr(), str.len(), NULL);
}

plString PyString_To_PlasmaString(PyObject* str) {
    if (PyUnicode_Check(str)) {
        PyObject* utfStr = PyUnicode_AsUTF8String(str);
        plString plstr = PyBytes_AsString(utfStr);
        Py_XDECREF(utfStr);
        return plstr;
    } else {
        return PyBytes_AsString(str);
    }
}
