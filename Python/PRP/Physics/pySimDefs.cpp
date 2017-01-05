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

#include "pyPhysical.h"

#include <PRP/Physics/plPhysical.h>

extern "C" {

PY_PLASMA_NEW_MSG(SimDefs, "Cannot construct plSimDefs objects")

PyTypeObject pySimDefs_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plSimDefs",             /* tp_name */
    sizeof(PyObject),                   /* tp_basicsize */
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

    Py_TPFLAGS_DEFAULT,                 /* tp_flags */
    "plSimDefs constants",              /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    NULL,                               /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pySimDefs_new,                      /* tp_new */
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

PyObject* Init_pySimDefs_Type() {
    if (PyType_Ready(&pySimDefs_Type) < 0)
        return NULL;

    /* Bounds */
    PY_TYPE_ADD_CONST(SimDefs, "kBoxBounds", plSimDefs::kBoxBounds);
    PY_TYPE_ADD_CONST(SimDefs, "kSphereBounds", plSimDefs::kSphereBounds);
    PY_TYPE_ADD_CONST(SimDefs, "kHullBounds", plSimDefs::kHullBounds);
    PY_TYPE_ADD_CONST(SimDefs, "kProxyBounds", plSimDefs::kProxyBounds);
    PY_TYPE_ADD_CONST(SimDefs, "kExplicitBounds", plSimDefs::kExplicitBounds);
    PY_TYPE_ADD_CONST(SimDefs, "kCylinderBounds", plSimDefs::kCylinderBounds);

    /* Group */
    PY_TYPE_ADD_CONST(SimDefs, "kGroupStatic", plSimDefs::kGroupStatic);
    PY_TYPE_ADD_CONST(SimDefs, "kGroupAvatar", plSimDefs::kGroupAvatar);
    PY_TYPE_ADD_CONST(SimDefs, "kGroupDynamic", plSimDefs::kGroupDynamic);
    PY_TYPE_ADD_CONST(SimDefs, "kGroupDetector", plSimDefs::kGroupDetector);
    PY_TYPE_ADD_CONST(SimDefs, "kGroupLOSOnly", plSimDefs::kGroupLOSOnly);

    /* LOSDBs */
    PY_TYPE_ADD_CONST(SimDefs, "kLOSDBNone", plSimDefs::kLOSDBNone);
    PY_TYPE_ADD_CONST(SimDefs, "kLOSDBUIBlockers", plSimDefs::kLOSDBUIBlockers);
    PY_TYPE_ADD_CONST(SimDefs, "kLOSDBUIItems", plSimDefs::kLOSDBUIItems);
    PY_TYPE_ADD_CONST(SimDefs, "kLOSDBCameraBlockers", plSimDefs::kLOSDBCameraBlockers);
    PY_TYPE_ADD_CONST(SimDefs, "kLOSDBCustom", plSimDefs::kLOSDBCustom);
    PY_TYPE_ADD_CONST(SimDefs, "kLOSDBLocalAvatar", plSimDefs::kLOSDBLocalAvatar);
    PY_TYPE_ADD_CONST(SimDefs, "kLOSDBShootableItems", plSimDefs::kLOSDBShootableItems);
    PY_TYPE_ADD_CONST(SimDefs, "kLOSDBAvatarWalkable", plSimDefs::kLOSDBAvatarWalkable);
    PY_TYPE_ADD_CONST(SimDefs, "kLOSDBSwimRegion", plSimDefs::kLOSDBSwimRegion);

    Py_INCREF(&pySimDefs_Type);
    return (PyObject*)&pySimDefs_Type;
}

}
