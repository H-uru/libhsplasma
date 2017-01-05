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

PY_PLASMA_EMPTY_INIT(CompressedQuatKey32)
PY_PLASMA_NEW(CompressedQuatKey32, hsCompressedQuatKey32)

PY_METHOD_VA(CompressedQuatKey32, setValue,
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

static PyMethodDef pyCompressedQuatKey32_Methods[] = {
    pyCompressedQuatKey32_setValue_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY_READ(CompressedQuatKey32, value, getQuat)
PY_PROPERTY_SETTER_MSG(CompressedQuatKey32, value,
                       "To set the compressed quat, use setValue()")
PY_PROPERTY_GETSET_DECL(CompressedQuatKey32, value)

static PyGetSetDef pyCompressedQuatKey32_GetSet[] = {
    pyCompressedQuatKey32_value_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyCompressedQuatKey32_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.hsCompressedQuatKey32", /* tp_name */
    sizeof(pyCompressedQuatKey32),      /* tp_basicsize */
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
    "hsCompressedQuatKey32 wrapper",    /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyCompressedQuatKey32_Methods,      /* tp_methods */
    NULL,                               /* tp_members */
    pyCompressedQuatKey32_GetSet,       /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    pyCompressedQuatKey32___init__,     /* tp_init */
    NULL,                               /* tp_alloc */
    pyCompressedQuatKey32_new,          /* tp_new */
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

PyObject* Init_pyCompressedQuatKey32_Type() {
    pyCompressedQuatKey32_Type.tp_base = &pyKeyFrame_Type;
    if (PyType_Ready(&pyCompressedQuatKey32_Type) < 0)
        return NULL;

    PY_TYPE_ADD_CONST(CompressedQuatKey32, "kCompQuatNukeX", hsCompressedQuatKey32::kCompQuatNukeX);
    PY_TYPE_ADD_CONST(CompressedQuatKey32, "kCompQuatNukeY", hsCompressedQuatKey32::kCompQuatNukeY);
    PY_TYPE_ADD_CONST(CompressedQuatKey32, "kCompQuatNukeZ", hsCompressedQuatKey32::kCompQuatNukeZ);
    PY_TYPE_ADD_CONST(CompressedQuatKey32, "kCompQuatNukeW", hsCompressedQuatKey32::kCompQuatNukeW);

    Py_INCREF(&pyCompressedQuatKey32_Type);
    return (PyObject*)&pyCompressedQuatKey32_Type;
}

PY_PLASMA_IFC_METHODS(CompressedQuatKey32, hsCompressedQuatKey32)

}
