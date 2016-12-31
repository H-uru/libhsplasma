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

extern "C" {

PY_PLASMA_VALUE_DEALLOC(ShaderConst)

PY_PLASMA_INIT_DECL(ShaderConst) {
    float sc[4];
    PyObject* init = NULL;

    if (PyArg_ParseTuple(args, "ffff", &sc[0], &sc[1], &sc[2], &sc[3])) {
        self->fThis->fArray[0] = sc[0];
        self->fThis->fArray[1] = sc[1];
        self->fThis->fArray[2] = sc[2];
        self->fThis->fArray[3] = sc[3];
    } else if (PyErr_Clear(), PyArg_ParseTuple(args, "|O", &init)) {
        if (init == NULL)
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

static PyObject* pyShaderConst_Subscript(pyShaderConst* self, PyObject* key) {
    if (!PyInt_Check(key)) {
        PyErr_SetString(PyExc_IndexError, "subscript should be an int");
        return NULL;
    }
    return pyPlasma_convert(self->fThis->fArray[PyInt_AsLong(key)]);
}

static int pyShaderConst_AssSubscript(pyShaderConst* self, PyObject* key, PyObject* value) {
    if (!PyInt_Check(key)) {
        PyErr_SetString(PyExc_IndexError, "subscript should be an int");
        return -1;
    }
    if (!PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "Shader Const values should be floats");
        return -1;
    }
    self->fThis->fArray[PyInt_AsLong(key)] = PyFloat_AsDouble(value);
    return 0;
}

static PyObject* pyShaderConst_Repr(pyShaderConst* self) {
    plString repr = plString::Format("plShaderConst(%f, %f, %f, %f)",
        self->fThis->fX, self->fThis->fY, self->fThis->fZ, self->fThis->fW);
    return pyPlasma_convert(repr);
}

static PyObject* pyShaderConst_read(pyShaderConst* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects a hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "read expects a hsStream");
        return NULL;
    }
    self->fThis->read(stream->fThis);
    Py_RETURN_NONE;
}

static PyObject* pyShaderConst_write(pyShaderConst* self, PyObject* args) {
    pyStream* stream;
    if (!PyArg_ParseTuple(args, "O", &stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects a hsStream");
        return NULL;
    }
    if (!pyStream_Check((PyObject*)stream)) {
        PyErr_SetString(PyExc_TypeError, "write expects a hsStream");
        return NULL;
    }
    self->fThis->write(stream->fThis);
    Py_RETURN_NONE;
}

static PyObject* pyShaderConst_getItem(pyShaderConst* self, void* which) {
    return pyPlasma_convert(self->fThis->fArray[(size_t)which]);
}

static int pyShaderConst_setItem(pyShaderConst* self, PyObject* value, void* which) {
    if (!PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "shader const values should be floats");
        return -1;
    }
    self->fThis->fArray[(size_t)which] = PyFloat_AsDouble(value);
    return 0;
}

static PyMappingMethods pyShaderConst_As_Mapping = {
    NULL,                                       /* mp_length */
    (binaryfunc)pyShaderConst_Subscript,        /* mp_subscript */
    (objobjargproc)pyShaderConst_AssSubscript   /* mp_ass_subscript */
};

static PyMethodDef pyShaderConst_Methods[] = {
    { "read", (PyCFunction)pyShaderConst_read, METH_VARARGS,
      "Params: stream\n"
      "Reads this object from `stream`" },
    { "write", (PyCFunction)pyShaderConst_write, METH_VARARGS,
      "Params: stream\n"
      "Writes this object to `stream`" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyShaderConst_GetSet[] = {
    { _pycs("X"), (getter)pyShaderConst_getItem,
        (setter)pyShaderConst_setItem, NULL, (void*)0 },
    { _pycs("Y"), (getter)pyShaderConst_getItem,
        (setter)pyShaderConst_setItem, NULL, (void*)1 },
    { _pycs("Z"), (getter)pyShaderConst_getItem,
        (setter)pyShaderConst_setItem, NULL, (void*)2 },
    { _pycs("W"), (getter)pyShaderConst_getItem,
        (setter)pyShaderConst_setItem, NULL, (void*)3 },
    { _pycs("red"), (getter)pyShaderConst_getItem,
        (setter)pyShaderConst_setItem, NULL, (void*)0 },
    { _pycs("green"), (getter)pyShaderConst_getItem,
        (setter)pyShaderConst_setItem, NULL, (void*)1 },
    { _pycs("blue"), (getter)pyShaderConst_getItem,
        (setter)pyShaderConst_setItem, NULL, (void*)2 },
    { _pycs("alpha"), (getter)pyShaderConst_getItem,
        (setter)pyShaderConst_setItem, NULL, (void*)3 },
    PY_GETSET_TERMINATOR
};

PyTypeObject pyShaderConst_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plShaderConst",         /* tp_name */
    sizeof(pyShaderConst),              /* tp_basicsize */
    0,                                  /* tp_itemsize */

    pyShaderConst_dealloc,              /* tp_dealloc */
    NULL,                               /* tp_print */
    NULL,                               /* tp_getattr */
    NULL,                               /* tp_setattr */
    NULL,                               /* tp_compare */
    (reprfunc)pyShaderConst_Repr,       /* tp_repr */
    NULL,                               /* tp_as_number */
    NULL,                               /* tp_as_sequence */
    &pyShaderConst_As_Mapping,          /* tp_as_mapping */
    NULL,                               /* tp_hash */
    NULL,                               /* tp_call */
    NULL,                               /* tp_str */
    NULL,                               /* tp_getattro */
    NULL,                               /* tp_setattro */
    NULL,                               /* tp_as_buffer */

    Py_TPFLAGS_DEFAULT,                 /* tp_flags */
    "plShaderConst wrapper",            /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyShaderConst_Methods,              /* tp_methods */
    NULL,                               /* tp_members */
    pyShaderConst_GetSet,               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    pyShaderConst___init__,             /* tp_init */
    NULL,                               /* tp_alloc */
    pyShaderConst_new,                  /* tp_new */
    NULL,                               /* tp_free */
    NULL,                               /* tp_is_gc */

    NULL,                               /* tp_bases */
    NULL,                               /* tp_mro */
    NULL,                               /* tp_cache */
    NULL,                               /* tp_subclasses */
    NULL,                               /* tp_weaklist */

    NULL,                               /* tp_del */
    TP_VERSION_TAG_INIT                 /* tp_version_tag */
    TP_FINALIZE_INIT                    /* tp_finalize */
};

PyObject* Init_pyShaderConst_Type() {
    if (PyType_Ready(&pyShaderConst_Type) < 0)
        return NULL;

    Py_INCREF(&pyShaderConst_Type);
    return (PyObject*)&pyShaderConst_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(ShaderConst, plShaderConst)

}
