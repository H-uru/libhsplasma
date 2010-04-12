/* This file is part of HSPlasma.
 *
 * HSPlasma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * HSPlasma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with HSPlasma.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <Python.h>
#include <Util/plString.h>

PyObject* PlasmaString_To_PyString(const plString& str);
PyObject* PlasmaString_To_PyUnicode(const plString& str);
plString PyString_To_PlasmaString(PyObject* str);

// Python 3.x does things differently...  This should help to keep things
// under control with both 2.x and 3.0 somewhat seamlessly.
#if (PY_MAJOR_VERSION >= 3)
    // Int -> Long
    #define PyInt_Check(ob) PyLong_Check(ob)
    #define PyInt_FromLong PyLong_FromLong
    #define PyInt_AsLong PyLong_AsLong

    // String -> Unicode
    #define PyAnyStr_Check(ob) (PyUnicode_Check(ob) || PyBytes_Check(ob))
    #define PyString_FromString(str) PyUnicode_DecodeUTF8((str), strlen((str)), NULL)
    #define PlStr_To_PyStr PlasmaString_To_PyUnicode

    // Py_TPFLAGS_CHECKTYPES is no longer used in Py3k
    #define Py_TPFLAGS_CHECKTYPES 0

    // tp_compare is no longer used in Py3k
    #define cmpfunc void*
#elif (PY_MAJOR_VERSION == 2) && (PY_MINOR_VERSION > 5)
    #undef PyBytes_Check
    #undef PyBytes_FromStringAndSize
    #undef PyBytes_AsStringAndSize
    #undef PyBytes_AsString

    #define PlStr_To_PyStr PlasmaString_To_PyString
    #define PyBytes_Check(ob) PyString_Check(ob)
    #define PyBytes_FromStringAndSize(v, len) PyString_FromStringAndSize(v, len)
    #define PyBytes_AsStringAndSize(obj, buf, len) PyString_AsStringAndSize(obj, buf, len)
    #define PyBytes_AsString PyString_AsString
    #define PyAnyStr_Check(ob) (PyUnicode_Check(ob) || PyBytes_Check(ob))
#else
    #define PlStr_To_PyStr PlasmaString_To_PyString
    #define PyBytes_Check(ob) PyString_Check(ob)
    #define PyBytes_FromStringAndSize(v, len) PyString_FromStringAndSize(v, len)
    #define PyBytes_AsStringAndSize(obj, buf, len) PyString_AsStringAndSize(obj, buf, len)
    #define PyBytes_AsString PyString_AsString
    #define PyAnyStr_Check(ob) (PyUnicode_Check(ob) || PyBytes_Check(ob))

    #define Py_TYPE(ob) ob->ob_type
    #define PyVarObject_HEAD_INIT(name, size) PyObject_HEAD_INIT(name) 0,
#endif

// This should work the same for all versions
#define PyStr_To_PlStr PyString_To_PlasmaString
