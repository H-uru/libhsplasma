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

#include "pyKeys.h"

#include <PRP/Animation/hsKeys.h>
#include "Math/pyGeometry3.h"

extern "C" {

PY_PLASMA_EMPTY_INIT(CompressedQuatKey64)
PY_PLASMA_NEW(CompressedQuatKey64, hsCompressedQuatKey64)

PY_METHOD_VA(CompressedQuatKey64, setValue,
    "Params: quat, type\n"
    "Set the hsQuat data.  Type is the compression nuking to use")
{
    pyQuat* value;
    int type;
    if (!PyArg_ParseTuple(args, "Oi", &value, &type)) {
        PyErr_SetString(PyExc_TypeError, "setValue expects hsQuat, int");
        return NULL;
    }
    if (!pyQuat_Check((PyObject*)value)) {
        PyErr_SetString(PyExc_TypeError, "setValue expects hsQuat, int");
        return NULL;
    }
    self->fThis->setQuat(*value->fThis, type);
    Py_RETURN_NONE;
}

static PyMethodDef pyCompressedQuatKey64_Methods[] = {
    pyCompressedQuatKey64_setValue_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY_READ(CompressedQuatKey64, value, getQuat)
PY_PROPERTY_SETTER_MSG(CompressedQuatKey64, value,
                       "To set the compressed quat, use setValue()")
PY_PROPERTY_GETSET_DECL(CompressedQuatKey64, value)

static PyGetSetDef pyCompressedQuatKey64_GetSet[] = {
    pyCompressedQuatKey64_value_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyCompressedQuatKey64_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.hsCompressedQuatKey64", /* tp_name */
    sizeof(pyCompressedQuatKey64),      /* tp_basicsize */
    0,                                  /* tp_itemsize */

    NULL,                               /* tp_dealloc */
    NULL,                               /* tp_print */
    NULL,                               /* tp_getattr */
    NULL,                               /* tp_setattr */
    NULL,                               /* tp_compare */
    NULL,                               /* tp_repr */
    NULL,                               /* tp_as_number */
    NULL,                               /* tp_as_sequence */
    NULL,                               /* tp_as_mapping */
    NULL,                               /* tp_hash */
    NULL,                               /* tp_call */
    NULL,                               /* tp_str */
    NULL,                               /* tp_getattro */
    NULL,                               /* tp_setattro */
    NULL,                               /* tp_as_buffer */

    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */
    "hsCompressedQuatKey64 wrapper",    /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyCompressedQuatKey64_Methods,      /* tp_methods */
    NULL,                               /* tp_members */
    pyCompressedQuatKey64_GetSet,       /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    pyCompressedQuatKey64___init__,     /* tp_init */
    NULL,                               /* tp_alloc */
    pyCompressedQuatKey64_new,          /* tp_new */
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

PyObject* Init_pyCompressedQuatKey64_Type() {
    pyCompressedQuatKey64_Type.tp_base = &pyKeyFrame_Type;
    if (PyType_Ready(&pyCompressedQuatKey64_Type) < 0)
        return NULL;

    PY_TYPE_ADD_CONST(CompressedQuatKey64, "kCompQuatNukeX", hsCompressedQuatKey64::kCompQuatNukeX);
    PY_TYPE_ADD_CONST(CompressedQuatKey64, "kCompQuatNukeY", hsCompressedQuatKey64::kCompQuatNukeY);
    PY_TYPE_ADD_CONST(CompressedQuatKey64, "kCompQuatNukeZ", hsCompressedQuatKey64::kCompQuatNukeZ);
    PY_TYPE_ADD_CONST(CompressedQuatKey64, "kCompQuatNukeW", hsCompressedQuatKey64::kCompQuatNukeW);

    Py_INCREF(&pyCompressedQuatKey64_Type);
    return (PyObject*)&pyCompressedQuatKey64_Type;
}

PY_PLASMA_IFC_METHODS(CompressedQuatKey64, hsCompressedQuatKey64)

}
