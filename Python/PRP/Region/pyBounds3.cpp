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

#include "pyBounds.h"

#include <PRP/Region/hsBounds.h>
#include "Math/pyGeometry3.h"

extern "C" {

static PyObject* pyBounds3_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyBounds3* self = (pyBounds3*)type->tp_alloc(type, 0);
    if (self != NULL)
        self->fThis = new hsBounds3();
    return (PyObject*)self;
}

PY_PROPERTY(hsVector3, Bounds3, mins, getMins, setMins)
PY_PROPERTY(hsVector3, Bounds3, maxs, getMaxs, setMaxs)
PY_PROPERTY(hsVector3, Bounds3, center, getCenter, setCenter)

static PyGetSetDef pyBounds3_GetSet[] = {
    pyBounds3_mins_getset,
    pyBounds3_maxs_getset,
    pyBounds3_center_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyBounds3_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.hsBounds3",             /* tp_name */
    sizeof(pyBounds3),                  /* tp_basicsize */
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
    "hsBounds3 wrapper",                /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyBounds3_GetSet,                   /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyBounds3_new,                      /* tp_new */
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

PyObject* Init_pyBounds3_Type() {
    pyBounds3_Type.tp_base = &pyBounds_Type;
    if (PyType_Ready(&pyBounds3_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyBounds3_Type.tp_dict, "kCenterValid",
                         PyInt_FromLong(hsBounds3::kCenterValid));
    PyDict_SetItemString(pyBounds3_Type.tp_dict, "kIsSphere",
                         PyInt_FromLong(hsBounds3::kIsSphere));

    Py_INCREF(&pyBounds3_Type);
    return (PyObject*)&pyBounds3_Type;
}

PY_PLASMA_VALUE_IFC_METHODS(Bounds3, hsBounds3)

}
