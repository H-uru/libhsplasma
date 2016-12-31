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

PY_PLASMA_EMPTY_INIT(ScaleKey)
PY_PLASMA_NEW(ScaleKey, hsScaleKey)

PY_PROPERTY_MEMBER(hsVector3, ScaleKey, inTan, fInTan)
PY_PROPERTY_MEMBER(hsVector3, ScaleKey, outTan, fOutTan)

PY_GETSET_GETTER_DECL(ScaleKey, value) {
    return Py_BuildValue("OO",
                         pyPlasma_convert(self->fThis->fS),
                         pyPlasma_convert(self->fThis->fQ));
}

PY_GETSET_SETTER_DECL(ScaleKey, value) {
    if (value == NULL) {
        PyErr_SetString(PyExc_RuntimeError, "value cannot be deleted");
        return -1;
    } else if (!PyTuple_Check(value) || PyTuple_Size(value) != 2) {
        PyErr_SetString(PyExc_TypeError, "value should be a tuple (hsVector3, hsQuat)");
        return -1;
    }
    PyObject* s = PyTuple_GetItem(value, 0);
    PyObject* q = PyTuple_GetItem(value, 1);
    if (!pyVector3_Check(s) || !pyQuat_Check(q)) {
        PyErr_SetString(PyExc_TypeError, "value should be a tuple (hsVector3, hsQuat)");
        return -1;
    }
    self->fThis->fS = pyPlasma_get<hsVector3>(s);
    self->fThis->fQ = pyPlasma_get<hsQuat>(q);
    return 0;
}

PY_PROPERTY_GETSET_DECL(ScaleKey, value)

static PyGetSetDef pyScaleKey_GetSet[] = {
    pyScaleKey_inTan_getset,
    pyScaleKey_outTan_getset,
    pyScaleKey_value_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyScaleKey_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.hsScaleKey",            /* tp_name */
    sizeof(pyScaleKey),                 /* tp_basicsize */
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
    "hsScaleKey wrapper",               /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyScaleKey_GetSet,                  /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    pyScaleKey___init__,                /* tp_init */
    NULL,                               /* tp_alloc */
    pyScaleKey_new,                     /* tp_new */
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

PyObject* Init_pyScaleKey_Type() {
    pyScaleKey_Type.tp_base = &pyKeyFrame_Type;
    if (PyType_Ready(&pyScaleKey_Type) < 0)
        return NULL;

    Py_INCREF(&pyScaleKey_Type);
    return (PyObject*)&pyScaleKey_Type;
}

PY_PLASMA_IFC_METHODS(ScaleKey, hsScaleKey)

}
