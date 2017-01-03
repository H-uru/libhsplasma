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

#include "PRP/Modifier/pyModifier.h"

#include <PRP/Surface/plDistOpacityMod.h>
#include "pyDistOpacityMod.h"

extern "C" {

PY_PLASMA_NEW(DistOpacityMod, plDistOpacityMod)

#define DOM_DISTANCE(propName, distEnum)                                \
    PY_GETSET_GETTER_DECL(DistOpacityMod, propName) {                   \
        return pyPlasma_convert(self->fThis->getDistance(plDistOpacityMod::distEnum)); \
    }                                                                   \
    PY_GETSET_SETTER_DECL(DistOpacityMod, propName) {                   \
        if (value == NULL) {                                            \
            PyErr_SetString(PyExc_RuntimeError, #propName " cannot be deleted"); \
            return -1;                                                  \
        } else if (!pyPlasma_check<float>(value)) {                     \
            PyErr_SetString(PyExc_TypeError, #propName " expected type float"); \
            return -1;                                                  \
        }                                                               \
        self->fThis->setDistance(plDistOpacityMod::distEnum, pyPlasma_get<float>(value)); \
        return 0;                                                       \
    }                                                                   \
    PY_PROPERTY_GETSET_DECL(DistOpacityMod, propName)

DOM_DISTANCE(nearTrans, kNearTrans)
DOM_DISTANCE(nearOpaq, kNearOpaq)
DOM_DISTANCE(farOpaq, kFarOpaq)
DOM_DISTANCE(farTrans, kFarTrans)

static PyGetSetDef pyDistOpacityMod_GetSet [] = {
    pyDistOpacityMod_nearTrans_getset,
    pyDistOpacityMod_nearOpaq_getset,
    pyDistOpacityMod_farOpaq_getset,
    pyDistOpacityMod_farTrans_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyDistOpacityMod_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plDistOpacityMod",      /* tp_name */
    sizeof(pyDistOpacityMod),           /* tp_basicsize */
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
    "plDistOpacityMod wrapper",         /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyDistOpacityMod_GetSet,            /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyDistOpacityMod_new,              /* tp_new */
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

PyObject* Init_pyDistOpacityMod_Type() {
    pyDistOpacityMod_Type.tp_base = &pySingleModifier_Type;
    if (PyType_Ready(&pyDistOpacityMod_Type) < 0)
        return NULL;

    Py_INCREF(&pyDistOpacityMod_Type);
    return (PyObject*) &pyDistOpacityMod_Type;
}

PY_PLASMA_IFC_METHODS(DistOpacityMod, plDistOpacityMod)

}
