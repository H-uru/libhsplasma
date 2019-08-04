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

#include "PyPlasma.h"
#include <string_theory/stdio>
#include <unordered_set>

PyObject* PyString_FromSTString(const ST::string& str)
{
    return PyString_FromStringAndSize(str.c_str(), str.size());
}

PyObject* PyUnicode_FromSTString(const ST::string& str)
{
    return PyUnicode_DecodeUTF8(str.c_str(), str.size(), NULL);
}

ST::string PyAnyString_AsSTString(PyObject* str)
{
    char *buffer;
    Py_ssize_t size;
    if (PyUnicode_Check(str)) {
        PyObject* utfStr = PyUnicode_AsUTF8String(str);
        PyBytes_AsStringAndSize(utfStr, &buffer, &size);
        ST::string plstr(buffer, size, ST::assume_valid);
        Py_XDECREF(utfStr);
        return plstr;
    } else {
        PyBytes_AsStringAndSize(str, &buffer, &size);
        return ST::string(buffer, size);
    }
}

int PyType_CheckAndReady(PyTypeObject* type)
{
    static std::unordered_set<PyTypeObject*> init_bases;
    if (type->tp_base != NULL && init_bases.find(type->tp_base) == init_bases.end()) {
        ST::printf(stderr, "ERROR: Base {} for type {} is not initialized\n",
                   type->tp_base->tp_name, type->tp_name);
        ST::printf(stderr, "Classes derived from {} WILL NOT WORK CORRECTLY\n",
                   type->tp_base->tp_name);
    }
    int result = PyType_Ready(type);
    if (result == 0)
        init_bases.insert(type);
    else
        ST::printf(stderr, "WARN: Failed to ready {}\n", type->tp_name);
    return result;
}
