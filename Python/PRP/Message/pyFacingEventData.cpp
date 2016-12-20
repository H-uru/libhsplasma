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

#include "pyEventData.h"

#include <PRP/Message/proEventData.h>
#include "PRP/KeyedObject/pyKey.h"

extern "C" {

static PyObject* pyFacingEventData_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyFacingEventData* self = (pyFacingEventData*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new proFacingEventData();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

PY_PROPERTY(plKey, FacingEventData, facer, getFacer, setFacer)
PY_PROPERTY(plKey, FacingEventData, facee, getFacee, setFacee)
PY_PROPERTY(float, FacingEventData, dot, getDot, setDot)
PY_PROPERTY(bool, FacingEventData, enabled, isEnabled, setEnabled)

static PyGetSetDef pyFacingEventData_GetSet[] = {
    pyFacingEventData_facer_getset,
    pyFacingEventData_facee_getset,
    pyFacingEventData_dot_getset,
    pyFacingEventData_enabled_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyFacingEventData_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.proFacingEventData",    /* tp_name */
    sizeof(pyFacingEventData),          /* tp_basicsize */
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
    "proFacingEventData wrapper",       /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyFacingEventData_GetSet,           /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyFacingEventData_new,              /* tp_new */
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

PyObject* Init_pyFacingEventData_Type() {
    pyFacingEventData_Type.tp_base = &pyEventData_Type;
    if (PyType_Ready(&pyFacingEventData_Type) < 0)
        return NULL;

    Py_INCREF(&pyFacingEventData_Type);
    return (PyObject*)&pyFacingEventData_Type;
}

PY_PLASMA_IFC_METHODS(FacingEventData, proFacingEventData)

}
