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

#include "pyColor.h"

#include <Sys/hsColor.h>
#include "Stream/pyStream.h"
#include <string_theory/format>

PY_PLASMA_VALUE_DEALLOC(Color32)

PY_METHOD_KWARGS(Color32, set,
    "Params: red, green, blue, alpha (all optional)\n"
    "Params: color (32-bit value)\n"
    "Sets the color")
{
    int red = 0, green = 0, blue = 0, alpha = 255, color = 0xFF000000;

    static char* kwlist1[] = { _pycs("red"), _pycs("green"), _pycs("blue"),
                               _pycs("alpha"), nullptr };
    static char* kwlist2[] = { _pycs("color"), nullptr };

    if (PyArg_ParseTupleAndKeywords(args, kwds, "I", kwlist2, &color)) {
        self->fThis->color = color;
    } else if (PyErr_Clear(), PyArg_ParseTupleAndKeywords(args, kwds, "|iiii", kwlist1,
                                                          &red, &green, &blue, &alpha)) {
        self->fThis->r = red;
        self->fThis->g = green;
        self->fThis->b = blue;
        self->fThis->a = alpha;
    } else {
        PyErr_SetString(PyExc_TypeError, "set expects 0-4 ints");
        return nullptr;
    }

    Py_RETURN_NONE;
}

PY_PLASMA_INIT_DECL(Color32)
{
    PyObject* retn = pyColor32_set(self, args, kwds);
    if (retn == nullptr)
        return -1;
    Py_DECREF(retn);
    return 0;
}

PY_PLASMA_VALUE_NEW(Color32, hsColor32)

PY_PLASMA_REPR_DECL(Color32)
{
    ST::string repr = ST::format("hsColor32({}, {}, {}, {})",
        self->fThis->r, self->fThis->g, self->fThis->b, self->fThis->a);
    return pyPlasma_convert(repr);
}

PY_METHOD_VA(Color32, read32,
    "Params: stream\n"
    "Reads this object from `stream`")
{
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "read32 expects a hsStream");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "read32 expects a hsStream");
        return nullptr;
    }
    self->fThis->read32(stream->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(Color32, write32,
    "Params: stream\n"
    "Writes this object to `stream`")
{
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "write32 expects a hsStream");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "write32 expects a hsStream");
        return nullptr;
    }
    self->fThis->write32(stream->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(Color32, readRGBA8,
    "Params: stream\n"
    "Reads this object from `stream`")
{
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "readRGBA8 expects a hsStream");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "readRGBA8 expects a hsStream");
        return nullptr;
    }
    self->fThis->readRGBA8(stream->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(Color32, writeRGBA8,
    "Params: stream\n"
    "Writes this object to `stream`")
{
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "writeRGBA8 expects a hsStream");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "writeRGBA8 expects a hsStream");
        return nullptr;
    }
    self->fThis->writeRGBA8(stream->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(Color32, readRGB8,
    "Params: stream\n"
    "Same as readRGBA8(), but does not read alpha")
{
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "readRGB8 expects a hsStream");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "readRGB8 expects a hsStream");
        return nullptr;
    }
    self->fThis->readRGB8(stream->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(Color32, writeRGB8,
    "Params: stream\n"
    "Same as writeRGBA8(), but does not write alpha")
{
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "writeRGB8 expects a hsStream");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "writeRGB8 expects a hsStream");
        return nullptr;
    }
    self->fThis->writeRGB8(stream->fThis);
    Py_RETURN_NONE;
}

static PyMethodDef pyColor32_Methods[] = {
    pyColor32_set_method,
    pyColor32_read32_method,
    pyColor32_write32_method,
    pyColor32_readRGBA8_method,
    pyColor32_writeRGBA8_method,
    pyColor32_readRGB8_method,
    pyColor32_writeRGB8_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY_MEMBER(unsigned char, Color32, red, r)
PY_PROPERTY_MEMBER(unsigned char, Color32, green, g)
PY_PROPERTY_MEMBER(unsigned char, Color32, blue, b)
PY_PROPERTY_MEMBER(unsigned char, Color32, alpha, a)
PY_PROPERTY_MEMBER(unsigned int, Color32, color, color)

static PyGetSetDef pyColor32_GetSet[] = {
    pyColor32_red_getset,
    pyColor32_green_getset,
    pyColor32_blue_getset,
    pyColor32_alpha_getset,
    pyColor32_color_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(Color32, hsColor32, "hsColor32 wrapper")

PY_PLASMA_TYPE_INIT(Color32)
{
    pyColor32_Type.tp_dealloc = pyColor32_dealloc;
    pyColor32_Type.tp_init = pyColor32___init__;
    pyColor32_Type.tp_new = pyColor32_new;
    pyColor32_Type.tp_repr = pyColor32_repr;
    pyColor32_Type.tp_methods = pyColor32_Methods;
    pyColor32_Type.tp_getset = pyColor32_GetSet;
    if (PyType_CheckAndReady(&pyColor32_Type) < 0)
        return nullptr;

    Py_INCREF(&pyColor32_Type);
    return (PyObject*)&pyColor32_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(Color32, hsColor32)
