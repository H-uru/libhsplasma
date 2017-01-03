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

#include "pyCubicEnvironmap.h"

#include <PRP/Surface/plCubicEnvironmap.h>
#include "PRP/pyCreatable.h"
#include "pyBitmap.h"

extern "C" {

PY_PLASMA_NEW(CubicEnvironmap, plCubicEnvironmap)

#define CEM_FACE(propName, faceName)                                    \
    PY_GETSET_GETTER_DECL(CubicEnvironmap, propName) {                  \
        return ICreate(self->fThis->getFace(plCubicEnvironmap::Faces::k##faceName##Face)); \
    }                                                                   \
    PY_GETSET_SETTER_DECL(CubicEnvironmap, propName) {                  \
        if (value == NULL) {                                            \
            PyErr_SetString(PyExc_RuntimeError, #propName " cannot be deleted"); \
            return -1;                                                  \
        } else if (!pyMipmap_Check(value)) {                            \
            PyErr_SetString(PyExc_TypeError, #propName " should be a plMipmap"); \
            return -1;                                                  \
        }                                                               \
        self->fThis->setFace(plCubicEnvironmap::Faces::k##faceName##Face, \
                             ((pyMipmap*)value)->fThis);                \
        return 0;                                                       \
    }                                                                   \
    PY_PROPERTY_GETSET_DECL(CubicEnvironmap, propName)

CEM_FACE(leftFace, Left)
CEM_FACE(rightFace, Right)
CEM_FACE(frontFace, Front)
CEM_FACE(backFace, Back)
CEM_FACE(topFace, Top)
CEM_FACE(bottomFace, Bottom)

static PyGetSetDef pyCubicEnvironmap_GetSet[] = {
    pyCubicEnvironmap_leftFace_getset,
    pyCubicEnvironmap_rightFace_getset,
    pyCubicEnvironmap_frontFace_getset,
    pyCubicEnvironmap_backFace_getset,
    pyCubicEnvironmap_topFace_getset,
    pyCubicEnvironmap_bottomFace_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyCubicEnvironmap_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plCubicEnvironmap",     /* tp_name */
    sizeof(pyCubicEnvironmap),          /* tp_basicsize */
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
    "plCubicEnvironmap wrapper",        /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyCubicEnvironmap_GetSet,           /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyCubicEnvironmap_new,              /* tp_new */
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

PyObject* Init_pyCubicEnvironmap_Type() {
    pyCubicEnvironmap_Type.tp_base = &pyBitmap_Type;
    if (PyType_Ready(&pyCubicEnvironmap_Type) < 0)
        return NULL;

    Py_INCREF(&pyCubicEnvironmap_Type);
    return (PyObject*)&pyCubicEnvironmap_Type;
}

PY_PLASMA_IFC_METHODS(CubicEnvironmap, plCubicEnvironmap)

}
