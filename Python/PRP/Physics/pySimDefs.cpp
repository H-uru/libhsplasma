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

#include <PyPlasma.h>
#include <PRP/Physics/plPhysical.h>
#include "pyPhysical.h"

extern "C" {

static PyObject* pySimDefs_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    PyErr_SetString(PyExc_RuntimeError, "Cannot construct plSimDefs objects");
    return NULL;
}

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
    PyDict_SetItemString(pySimDefs_Type.tp_dict, "kBoxBounds",
                         PyInt_FromLong(plSimDefs::kBoxBounds));
    PyDict_SetItemString(pySimDefs_Type.tp_dict, "kSphereBounds",
                         PyInt_FromLong(plSimDefs::kSphereBounds));
    PyDict_SetItemString(pySimDefs_Type.tp_dict, "kHullBounds",
                         PyInt_FromLong(plSimDefs::kHullBounds));
    PyDict_SetItemString(pySimDefs_Type.tp_dict, "kProxyBounds",
                         PyInt_FromLong(plSimDefs::kProxyBounds));
    PyDict_SetItemString(pySimDefs_Type.tp_dict, "kExplicitBounds",
                         PyInt_FromLong(plSimDefs::kExplicitBounds));
    PyDict_SetItemString(pySimDefs_Type.tp_dict, "kCylinderBounds",
                         PyInt_FromLong(plSimDefs::kCylinderBounds));

    /* Group */
    PyDict_SetItemString(pySimDefs_Type.tp_dict, "kGroupStatic",
                         PyInt_FromLong(plSimDefs::kGroupStatic));
    PyDict_SetItemString(pySimDefs_Type.tp_dict, "kGroupAvatar",
                         PyInt_FromLong(plSimDefs::kGroupAvatar));
    PyDict_SetItemString(pySimDefs_Type.tp_dict, "kGroupDynamic",
                         PyInt_FromLong(plSimDefs::kGroupDynamic));
    PyDict_SetItemString(pySimDefs_Type.tp_dict, "kGroupDetector",
                         PyInt_FromLong(plSimDefs::kGroupDetector));
    PyDict_SetItemString(pySimDefs_Type.tp_dict, "kGroupLOSOnly",
                         PyInt_FromLong(plSimDefs::kGroupLOSOnly));

    /* LOSDBs */
    PyDict_SetItemString(pySimDefs_Type.tp_dict, "kLOSDBNone",
                         PyInt_FromLong(plSimDefs::kLOSDBNone));
    PyDict_SetItemString(pySimDefs_Type.tp_dict, "kLOSDBUIBlockers",
                         PyInt_FromLong(plSimDefs::kLOSDBUIBlockers));
    PyDict_SetItemString(pySimDefs_Type.tp_dict, "kLOSDBUIItems",
                         PyInt_FromLong(plSimDefs::kLOSDBUIItems));
    PyDict_SetItemString(pySimDefs_Type.tp_dict, "kLOSDBCameraBlockers",
                         PyInt_FromLong(plSimDefs::kLOSDBCameraBlockers));
    PyDict_SetItemString(pySimDefs_Type.tp_dict, "kLOSDBCustom",
                         PyInt_FromLong(plSimDefs::kLOSDBCustom));
    PyDict_SetItemString(pySimDefs_Type.tp_dict, "kLOSDBLocalAvatar",
                         PyInt_FromLong(plSimDefs::kLOSDBLocalAvatar));
    PyDict_SetItemString(pySimDefs_Type.tp_dict, "kLOSDBShootableItems",
                         PyInt_FromLong(plSimDefs::kLOSDBShootableItems));
    PyDict_SetItemString(pySimDefs_Type.tp_dict, "kLOSDBAvatarWalkable",
                         PyInt_FromLong(plSimDefs::kLOSDBAvatarWalkable));
    PyDict_SetItemString(pySimDefs_Type.tp_dict, "kLOSDBSwimRegion",
                         PyInt_FromLong(plSimDefs::kLOSDBSwimRegion));

    Py_INCREF(&pySimDefs_Type);
    return (PyObject*)&pySimDefs_Type;
}

}
