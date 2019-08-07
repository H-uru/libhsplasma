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

#include "pyShader.h"

#include <PRP/Surface/plShader.h>
#include "Stream/pyStream.h"

PY_PLASMA_VALUE_DEALLOC(ShaderConst)

PY_PLASMA_INIT_DECL(ShaderConst)
{
    float sc[4];
    PyObject* init = nullptr;

    if (PyArg_ParseTuple(args, "ffff", &sc[0], &sc[1], &sc[2], &sc[3])) {
        self->fThis->fArray[0] = sc[0];
        self->fThis->fArray[1] = sc[1];
        self->fThis->fArray[2] = sc[2];
        self->fThis->fArray[3] = sc[3];
    } else if (PyErr_Clear(), PyArg_ParseTuple(args, "|O", &init)) {
        if (init == nullptr)
            return 0;
        if (pyShaderConst_Check(init)) {
            self->fThis->fArray[0] = ((pyShaderConst*)init)->fThis->fArray[0];
            self->fThis->fArray[1] = ((pyShaderConst*)init)->fThis->fArray[1];
            self->fThis->fArray[2] = ((pyShaderConst*)init)->fThis->fArray[2];
            self->fThis->fArray[3] = ((pyShaderConst*)init)->fThis->fArray[3];
        } else {
            return -1;
        }
    } else {
        return -1;
    }

    return 0;
}

PY_PLASMA_VALUE_NEW(ShaderConst, plShaderConst)

PY_PLASMA_SUBSCRIPT_DECL(ShaderConst)
{
    if (!pyPlasma_check<size_t>(key)) {
        PyErr_SetString(PyExc_IndexError, "subscript should be an int");
        return nullptr;
    }
    return pyPlasma_convert(self->fThis->fArray[pyPlasma_get<size_t>(key)]);
}

PY_PLASMA_ASS_SUBSCRIPT_DECL(ShaderConst)
{
    if (!pyPlasma_check<size_t>(key)) {
        PyErr_SetString(PyExc_IndexError, "subscript should be an int");
        return -1;
    }
    if (!pyPlasma_check<float>(value)) {
        PyErr_SetString(PyExc_TypeError, "Shader Const values should be floats");
        return -1;
    }
    self->fThis->fArray[pyPlasma_get<size_t>(key)] = pyPlasma_get<float>(value);
    return 0;
}

PY_PLASMA_REPR_DECL(ShaderConst)
{
    ST::string repr = ST::format("plShaderConst({f}, {f}, {f}, {f})",
        self->fThis->fX, self->fThis->fY, self->fThis->fZ, self->fThis->fW);
    return pyPlasma_convert(repr);
}

PY_METHOD_VA(ShaderConst, read,
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

PY_METHOD_VA(ShaderConst, write,
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

static PyMethodDef pyShaderConst_Methods[] = {
    pyShaderConst_read_method,
    pyShaderConst_write_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY_MEMBER(float, ShaderConst, X, fX)
PY_PROPERTY_MEMBER(float, ShaderConst, Y, fY)
PY_PROPERTY_MEMBER(float, ShaderConst, Z, fZ)
PY_PROPERTY_MEMBER(float, ShaderConst, W, fW)
PY_PROPERTY_MEMBER(float, ShaderConst, red, fR)
PY_PROPERTY_MEMBER(float, ShaderConst, green, fG)
PY_PROPERTY_MEMBER(float, ShaderConst, blue, fB)
PY_PROPERTY_MEMBER(float, ShaderConst, alpha, fA)

static PyGetSetDef pyShaderConst_GetSet[] = {
    pyShaderConst_X_getset,
    pyShaderConst_Y_getset,
    pyShaderConst_Z_getset,
    pyShaderConst_W_getset,
    pyShaderConst_red_getset,
    pyShaderConst_green_getset,
    pyShaderConst_blue_getset,
    pyShaderConst_alpha_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(ShaderConst, plShaderConst, "plShaderConst wrapper")
PY_PLASMA_TYPE_AS_MAPPING(ShaderConst)

PY_PLASMA_TYPE_INIT(ShaderConst)
{
    pyShaderConst_As_Mapping.mp_subscript = pyShaderConst_mp_subscript;
    pyShaderConst_As_Mapping.mp_ass_subscript = pyShaderConst_mp_ass_subscript;
    pyShaderConst_Type.tp_dealloc = pyShaderConst_dealloc;
    pyShaderConst_Type.tp_init = pyShaderConst___init__;
    pyShaderConst_Type.tp_new = pyShaderConst_new;
    pyShaderConst_Type.tp_repr = pyShaderConst_repr;
    pyShaderConst_Type.tp_as_mapping = &pyShaderConst_As_Mapping;
    pyShaderConst_Type.tp_methods = pyShaderConst_Methods;
    pyShaderConst_Type.tp_getset = pyShaderConst_GetSet;
    if (PyType_CheckAndReady(&pyShaderConst_Type) < 0)
        return nullptr;

    Py_INCREF(&pyShaderConst_Type);
    return (PyObject*)&pyShaderConst_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(ShaderConst, plShaderConst)
