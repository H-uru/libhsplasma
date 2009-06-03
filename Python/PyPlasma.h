#include <Python.h>

// Python 3.x does things differently...  This should help to keep things
// under control with both 2.x and 3.0 somewhat seamlessly.
#if PY_MAJOR_VERSION >= 3
    // Int -> Long
    #define PyInt_Check(op) PyLong_Check(op)
    #define PyInt_FromLong PyLong_FromLong
    #define PyInt_AsLong PyLong_AsLong

    // String -> Unicode
    #define PyString_Check(op) PyUnicode_Check(op)
    #define PyString_FromString PyUnicode_FromString
    #define PyString_AsString PyUnicode_AS_DATA

    // Py_TPFLAGS_CHECKTYPES is no longer used in Py3k
    #define Py_TPFLAGS_CHECKTYPES 0

    // tp_compare is no longer used in Py3k
    #define cmpfunc void*
#else
    #undef PyBytes_Check
    #undef PyBytes_FromStringAndSize
    #undef PyBytes_AsStringAndSize

    #define PyBytes_Check(op) PyString_Check(op)
    #define PyBytes_FromStringAndSize(v, len) PyString_FromStringAndSize(v, len)
    #define PyBytes_AsStringAndSize(obj, buf, len) PyString_AsStringAndSize(obj, buf, len)
#endif
