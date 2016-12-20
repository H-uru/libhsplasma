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

#include "pySwimRegion.h"

#include "PRP/KeyedObject/pyKey.h"
#include <PRP/Region/plSwimRegion.h>

extern "C" {

static PyObject* pySwimCircularCurrentRegion_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pySwimCircularCurrentRegion* self = (pySwimCircularCurrentRegion*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plSwimCircularCurrentRegion();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

PY_PROPERTY(float, SwimCircularCurrentRegion, rotation, getRotation, setRotation)
PY_PROPERTY(float, SwimCircularCurrentRegion, pullNearDistSq, getPullNearDistSq, setPullNearDistSq)
PY_PROPERTY(float, SwimCircularCurrentRegion, pullFarDistSq, getPullFarDistSq, setPullFarDistSq)
PY_PROPERTY(float, SwimCircularCurrentRegion, pullNearVel, getPullNearVel, setPullNearVel)
PY_PROPERTY(float, SwimCircularCurrentRegion, pullFarVel, getPullFarVel, setPullFarVel)
PY_PROPERTY(plKey, SwimCircularCurrentRegion, currentObj, getCurrentObj, setCurrentObj)

PyGetSetDef pySwimCircularCurrentRegion_GetSet[] = {
    pySwimCircularCurrentRegion_rotation_getset,
    pySwimCircularCurrentRegion_pullNearDistSq_getset,
    pySwimCircularCurrentRegion_pullFarDistSq_getset,
    pySwimCircularCurrentRegion_pullNearVel_getset,
    pySwimCircularCurrentRegion_pullFarVel_getset,
    pySwimCircularCurrentRegion_currentObj_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pySwimCircularCurrentRegion_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plSwimCircularCurrentRegion", /* tp_name */
    sizeof(pySwimCircularCurrentRegion),      /* tp_basicsize */
    0,                                        /* tp_itemsize */

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
    "plSwimCircularCurrentRegion wrapper",    /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pySwimCircularCurrentRegion_GetSet, /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pySwimCircularCurrentRegion_new,    /* tp_new */
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

PyObject* Init_pySwimCircularCurrentRegion_Type() {
    pySwimCircularCurrentRegion_Type.tp_base = &pySwimRegionInterface_Type;
    if (PyType_Ready(&pySwimCircularCurrentRegion_Type) < 0)
        return NULL;

    Py_INCREF(&pySwimCircularCurrentRegion_Type);
    return (PyObject*)&pySwimCircularCurrentRegion_Type;
}

PY_PLASMA_IFC_METHODS(SwimCircularCurrentRegion, plSwimCircularCurrentRegion);

}
