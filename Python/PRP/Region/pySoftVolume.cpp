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

#include "pySoftVolume.h"

#include <PRP/Region/plSoftVolume.h>
#include "PRP/Object/pyObjInterface.h"
#include "PRP/pyCreatable.h"

extern "C" {

PY_PLASMA_NEW_MSG(SoftVolume, "plSoftVolume is abstract")

PY_PROPERTY(unsigned int, SoftVolume, listenState, getListenState, setListenState)
PY_PROPERTY(float, SoftVolume, insideStrength, getInsideStrength, setInsideStrength)
PY_PROPERTY(float, SoftVolume, outsideStrength, getOutsideStrength, setOutsideStrength)

PyGetSetDef pySoftVolume_GetSet[] = {
    pySoftVolume_listenState_getset,
    pySoftVolume_insideStrength_getset,
    pySoftVolume_outsideStrength_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pySoftVolume_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plSoftVolume",          /* tp_name */
    sizeof(pySoftVolume),               /* tp_basicsize */
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
    "plSoftVolume wrapper",                   /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pySoftVolume_GetSet,                /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pySoftVolume_new,                   /* tp_new */
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

PyObject* Init_pySoftVolume_Type() {
    pySoftVolume_Type.tp_base = &pyObjInterface_Type;
    if (PyType_Ready(&pySoftVolume_Type) < 0)
        return NULL;

    PyDict_SetItemString(pySoftVolume_Type.tp_dict, "kListenNone",
                         PyInt_FromLong(plSoftVolume::kListenNone));
    PyDict_SetItemString(pySoftVolume_Type.tp_dict, "kListenCheck",
                         PyInt_FromLong(plSoftVolume::kListenCheck));
    PyDict_SetItemString(pySoftVolume_Type.tp_dict, "kListenPosSet",
                         PyInt_FromLong(plSoftVolume::kListenPosSet));
    PyDict_SetItemString(pySoftVolume_Type.tp_dict, "kListenDirty",
                         PyInt_FromLong(plSoftVolume::kListenDirty));
    PyDict_SetItemString(pySoftVolume_Type.tp_dict, "kListenRegistered",
                         PyInt_FromLong(plSoftVolume::kListenRegistered));

    Py_INCREF(&pySoftVolume_Type);
    return (PyObject*)&pySoftVolume_Type;
}

PY_PLASMA_IFC_METHODS(SoftVolume, plSoftVolume)

}
