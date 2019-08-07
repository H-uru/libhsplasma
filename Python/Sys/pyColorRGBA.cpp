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

PY_PLASMA_VALUE_DEALLOC(ColorRGBA)

PY_PLASMA_INIT_DECL(ColorRGBA)
{
    float red = 0.0f, green = 0.0f, blue = 0.0f, alpha = 1.0f;
    PyObject* init = nullptr;
    static char* kwlist[] = { _pycs("red"), _pycs("green"), _pycs("blue"),
                              _pycs("alpha"), nullptr };

    if (PyArg_ParseTupleAndKeywords(args, kwds, "fff|f", kwlist,
                                    &red, &green, &blue, &alpha)) {
        self->fThis->set(red, green, blue, alpha);
    } else if (PyErr_Clear(), PyArg_ParseTuple(args, "|O", &init)) {
        if (init == nullptr)
            return 0;
        if (pyColorRGBA_Check(init)) {
            self->fThis->set(*((pyColorRGBA*)init)->fThis);
        } else {
            return -1;
        }
    } else {
        return -1;
    }

    return 0;
}

PY_PLASMA_VALUE_NEW(ColorRGBA, hsColorRGBA)

PY_PLASMA_REPR_DECL(ColorRGBA)
{
    ST::string repr = ST::format("hsColorRGBA({f}, {f}, {f}, {f})",
        self->fThis->r, self->fThis->g, self->fThis->b, self->fThis->a);
    return pyPlasma_convert(repr);
}

PY_METHOD_KWARGS(ColorRGBA, set,
    "Params: red, green, blue, alpha (all optional)\n"
    "Sets the color")
{
    float red = 0.0f, green = 0.0f, blue = 0.0f, alpha = 1.0f;
    static char* kwlist[] = { _pycs("red"), _pycs("green"), _pycs("blue"),
                              _pycs("alpha"), nullptr };

    if (!PyArg_ParseTupleAndKeywords(args, kwds, "|ffff", kwlist,
                                     &red, &green, &blue, &alpha)) {
        PyErr_SetString(PyExc_TypeError, "set expects 0-4 floats");
        return nullptr;
    }

    self->fThis->set(red, green, blue, alpha);
    Py_RETURN_NONE;
}

PY_METHOD_VA(ColorRGBA, setFrom,
    "Params: color\n"
    "Sets the color")
{
    pyColorRGBA* from;
    if (!PyArg_ParseTuple(args, "O", &from)) {
        PyErr_SetString(PyExc_TypeError, "setFrom expects an hsColorRGBA");
        return nullptr;
    }
    if (!pyColorRGBA_Check((PyObject*)from)) {
        PyErr_SetString(PyExc_TypeError, "setFrom expects an hsColorRGBA");
        return nullptr;
    }
    self->fThis->set(*from->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(ColorRGBA, read,
    "Params: stream\n"
    "Reads this object from `stream`")
{
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects a hsStream");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects a hsStream");
        return nullptr;
    }
    self->fThis->read(stream->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(ColorRGBA, write,
    "Params: stream\n"
    "Writes this object to `stream`")
{
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects a hsStream");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects a hsStream");
        return nullptr;
    }
    self->fThis->write(stream->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(ColorRGBA, readRGB,
    "Params: stream\n"
    "Same as read(), but does not read alpha")
{
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "readRGB expects a hsStream");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "readRGB expects a hsStream");
        return nullptr;
    }
    self->fThis->readRGB(stream->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(ColorRGBA, writeRGB,
    "Params: stream\n"
    "Same as write(), but does not write alpha")
{
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "writeRGB expects a hsStream");
        return nullptr;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "writeRGB expects a hsStream");
        return nullptr;
    }
    self->fThis->writeRGB(stream->fThis);
    Py_RETURN_NONE;
}

static PyMethodDef pyColorRGBA_Methods[] = {
    pyColorRGBA_set_method,
    pyColorRGBA_setFrom_method,
    pyColorRGBA_read_method,
    pyColorRGBA_write_method,
    pyColorRGBA_readRGB_method,
    pyColorRGBA_writeRGB_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY_MEMBER(float, ColorRGBA, red, r)
PY_PROPERTY_MEMBER(float, ColorRGBA, green, g)
PY_PROPERTY_MEMBER(float, ColorRGBA, blue, b)
PY_PROPERTY_MEMBER(float, ColorRGBA, alpha, a)

static PyGetSetDef pyColorRGBA_GetSet[] = {
    pyColorRGBA_red_getset,
    pyColorRGBA_green_getset,
    pyColorRGBA_blue_getset,
    pyColorRGBA_alpha_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ColorRGBA, hsColorRGBA, "hsColorRGBA wrapper")

PY_PLASMA_TYPE_INIT(ColorRGBA)
{
    pyColorRGBA_Type.tp_dealloc = pyColorRGBA_dealloc;
    pyColorRGBA_Type.tp_init = pyColorRGBA___init__;
    pyColorRGBA_Type.tp_new = pyColorRGBA_new;
    pyColorRGBA_Type.tp_repr = pyColorRGBA_repr;
    pyColorRGBA_Type.tp_methods = pyColorRGBA_Methods;
    pyColorRGBA_Type.tp_getset = pyColorRGBA_GetSet;
    if (PyType_CheckAndReady(&pyColorRGBA_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(ColorRGBA, "kBlack", hsColorRGBA::kBlack);
    PY_TYPE_ADD_CONST(ColorRGBA, "kWhite", hsColorRGBA::kWhite);
    PY_TYPE_ADD_CONST(ColorRGBA, "kRed", hsColorRGBA::kRed);
    PY_TYPE_ADD_CONST(ColorRGBA, "kGreen", hsColorRGBA::kGreen);
    PY_TYPE_ADD_CONST(ColorRGBA, "kBlue", hsColorRGBA::kBlue);
    PY_TYPE_ADD_CONST(ColorRGBA, "kYellow", hsColorRGBA::kYellow);
    PY_TYPE_ADD_CONST(ColorRGBA, "kMagenta", hsColorRGBA::kMagenta);
    PY_TYPE_ADD_CONST(ColorRGBA, "kCyan", hsColorRGBA::kCyan);
    PY_TYPE_ADD_CONST(ColorRGBA, "kGray", hsColorRGBA::kGray);
    PY_TYPE_ADD_CONST(ColorRGBA, "kNone", hsColorRGBA::kNone);

    Py_INCREF(&pyColorRGBA_Type);
    return (PyObject*)&pyColorRGBA_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(ColorRGBA, hsColorRGBA)
