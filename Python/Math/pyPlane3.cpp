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

#include "pyGeometry3.h"

#include <Math/hsGeometry3.h>
#include "Stream/pyStream.h"
#include <string_theory/format>

PY_PLASMA_VALUE_DEALLOC(Plane3)

PY_PLASMA_INIT_DECL(Plane3)
{
    float x = 0.0f, y = 0.0f, z = 0.0f, w = 0.0f;
    PyObject* init = nullptr;
    static char* kwlist[] = { _pycs("X"), _pycs("Y"), _pycs("Z"), _pycs("W"), nullptr };
    static char* kwlist2[] = { _pycs("Plane"), nullptr };

    if (PyArg_ParseTupleAndKeywords(args, kwds, "ffff", kwlist, &x, &y, &z, &w)) {
        (*self->fThis) = hsPlane3(hsVector3(x, y, z), w);
    } else if (PyErr_Clear(), PyArg_ParseTupleAndKeywords(args, kwds, "|O", kwlist2, &init)) {
        if (init == nullptr) {
            (*self->fThis) = hsPlane3();
            return 0;
        }
        if (pyPlane3_Check(init)) {
            (*self->fThis) = pyPlasma_get<hsPlane3>(init);
        } else {
            PyErr_SetString(PyExc_TypeError, "__init__ expects a Plane");
            return -1;
        }
    } else {
        return -1;
    }

    return 0;
}

PY_PLASMA_VALUE_NEW(Plane3, hsPlane3)

PY_PLASMA_REPR_DECL(Plane3)
{
    ST::string repr = ST::format("hsPlane3({f}, {f}, {f}, {f})",
             self->fThis->N.X, self->fThis->N.Y, self->fThis->N.Z, self->fThis->W);
    return pyPlasma_convert(repr);
}

PY_METHOD_VA(Plane3, read,
    "Params: stream\n"
    "Reads this Plane from `stream`")
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

PY_METHOD_VA(Plane3, write,
    "Params: stream\n"
    "Writes this Plane to `stream`")
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

PyMethodDef pyPlane3_Methods[] = {
    pyPlane3_read_method,
    pyPlane3_write_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY_MEMBER(float, Plane3, X, N.X)
PY_PROPERTY_MEMBER(float, Plane3, Y, N.Y)
PY_PROPERTY_MEMBER(float, Plane3, Z, N.Z)
PY_PROPERTY_MEMBER(float, Plane3, W, W)

PyGetSetDef pyPlane3_GetSet[] = {
    pyPlane3_X_getset,
    pyPlane3_Y_getset,
    pyPlane3_Z_getset,
    pyPlane3_W_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(Plane3, hsPlane3, "hsPlane3 wrapper")

PY_PLASMA_TYPE_INIT(Plane3)
{
    pyPlane3_Type.tp_dealloc = pyPlane3_dealloc;
    pyPlane3_Type.tp_init = pyPlane3___init__;
    pyPlane3_Type.tp_new = pyPlane3_new;
    pyPlane3_Type.tp_repr = pyPlane3_repr;
    pyPlane3_Type.tp_methods = pyPlane3_Methods;
    pyPlane3_Type.tp_getset = pyPlane3_GetSet;
    if (PyType_CheckAndReady(&pyPlane3_Type) < 0)
        return nullptr;

    Py_INCREF(&pyPlane3_Type);
    return (PyObject*)&pyPlane3_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(Plane3, hsPlane3)
