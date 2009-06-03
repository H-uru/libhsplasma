#include <Python.h>

// Python 3.x does things differently...  This should help to keep things
// under control with both 2.x and 3.0 somewhat seamlessly.
#if (PY_MAJOR_VERSION >= 3)
    // Int -> Long
    #define PyInt_Check(ob) PyLong_Check(ob)
    #define PyInt_FromLong PyLong_FromLong
    #define PyInt_AsLong PyLong_AsLong

    // String -> Unicode
    #define PyString_Check(ob) PyUnicode_Check(ob)
    #define PyString_FromString PyUnicode_FromString
    #define PyString_AsString PyUnicode_AS_DATA

    // Py_TPFLAGS_CHECKTYPES is no longer used in Py3k
    #define Py_TPFLAGS_CHECKTYPES 0

    // tp_compare is no longer used in Py3k
    #define cmpfunc void*
#elif (PY_MAJOR_VERSION == 2) && (PY_MINOR_VERSION > 5)
    #undef PyBytes_Check
    #undef PyBytes_FromStringAndSize
    #undef PyBytes_AsStringAndSize

    #define PyBytes_Check(ob) PyString_Check(ob)
    #define PyBytes_FromStringAndSize(v, len) PyString_FromStringAndSize(v, len)
    #define PyBytes_AsStringAndSize(obj, buf, len) PyString_AsStringAndSize(obj, buf, len)
#else
    #define PyBytes_Check(ob) PyString_Check(ob)
    #define PyBytes_FromStringAndSize(v, len) PyString_FromStringAndSize(v, len)
    #define PyBytes_AsStringAndSize(obj, buf, len) PyString_AsStringAndSize(obj, buf, len)

    #define Py_TYPE(ob) ob->ob_type
    #define PyVarObject_HEAD_INIT(name, size) PyObject_HEAD_INIT(name) 0,
#endif
