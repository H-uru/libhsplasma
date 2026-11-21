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

PyObject* PyUnicode_FromSTString(const ST::string& str)
{
    return PyUnicode_DecodeUTF8(str.c_str(), str.size(), nullptr);
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

int PyAnyString_PathDecoder(PyObject* obj, void* str)
{
    PyObject* fsConvert;
    if (PyUnicode_FSDecoder(obj, &fsConvert)) {
        *((ST::string*)str) = PyAnyString_AsSTString(fsConvert);
        Py_DECREF(fsConvert);
        return 1;
    }
    return 0;
}
