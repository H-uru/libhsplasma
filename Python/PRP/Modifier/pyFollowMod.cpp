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

#include "pyFollowMod.h"

#include <PRP/Modifier/plFollowMod.h>
#include "PRP/Modifier/pyModifier.h"
#include "PRP/KeyedObject/pyKey.h"

extern "C" {

PY_PLASMA_NEW(FollowMod, plFollowMod)

PY_PROPERTY(plFollowMod::FollowLeaderType, FollowMod, leaderType, getLeaderType,
            setLeaderType)
PY_PROPERTY(uint8_t, FollowMod, mode, getMode, setMode)
PY_PROPERTY(plKey, FollowMod, leader, getLeader, setLeader)

static PyGetSetDef pyFollowMod_GetSet [] = {
    pyFollowMod_leaderType_getset,
    pyFollowMod_mode_getset,
    pyFollowMod_leader_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyFollowMod_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plFollowMod",           /* tp_name */
    sizeof(pyFollowMod),                /* tp_basicsize */
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
    "plFollowMod wrapper",              /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyFollowMod_GetSet,                 /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyFollowMod_new,                    /* tp_new */
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

PyObject* Init_pyFollowMod_Type() {
    pyFollowMod_Type.tp_base = &pySingleModifier_Type;
    if (PyType_Ready(&pyFollowMod_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyFollowMod_Type.tp_dict, "kFollowPlayer",
        PyInt_FromLong(plFollowMod::kFollowPlayer));
    PyDict_SetItemString(pyFollowMod_Type.tp_dict, "kFollowObject",
        PyInt_FromLong(plFollowMod::kFollowObject));
    PyDict_SetItemString(pyFollowMod_Type.tp_dict, "kFollowCamera",
        PyInt_FromLong(plFollowMod::kFollowCamera));
    PyDict_SetItemString(pyFollowMod_Type.tp_dict, "kFollowListener",
        PyInt_FromLong(plFollowMod::kFollowListener));

    PyDict_SetItemString(pyFollowMod_Type.tp_dict, "kPositionX",
        PyInt_FromLong(plFollowMod::kPositionX));
    PyDict_SetItemString(pyFollowMod_Type.tp_dict, "kPositionY",
        PyInt_FromLong(plFollowMod::kPositionY));
    PyDict_SetItemString(pyFollowMod_Type.tp_dict, "kPositionZ",
        PyInt_FromLong(plFollowMod::kPositionZ));
    PyDict_SetItemString(pyFollowMod_Type.tp_dict, "kPosition",
        PyInt_FromLong(plFollowMod::kPosition));
    PyDict_SetItemString(pyFollowMod_Type.tp_dict, "kRotate",
        PyInt_FromLong(plFollowMod::kRotate));
    PyDict_SetItemString(pyFollowMod_Type.tp_dict, "kFullTransform",
        PyInt_FromLong(plFollowMod::kFullTransform));

    Py_INCREF(&pyFollowMod_Type);
    return (PyObject*) &pyFollowMod_Type;
}

PY_PLASMA_IFC_METHODS(FollowMod, plFollowMod)

}
