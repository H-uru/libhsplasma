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

#include "pyVisRegion.h"

#include <PRP/Region/plVisRegion.h>
#include "PRP/Object/pyObjInterface.h"
#include "PRP/KeyedObject/pyKey.h"

extern "C" {

static PyObject* pyVisRegion_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyVisRegion* self = (pyVisRegion*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plVisRegion();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

PY_PROPERTY(plKey, VisRegion, region, getRegion, setRegion)
PY_PROPERTY(plKey, VisRegion, visMgr, getVisMgr, setVisMgr)

PyGetSetDef pyVisRegion_GetSet[] = {
    pyVisRegion_region_getset,
    pyVisRegion_visMgr_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyVisRegion_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plVisRegion",           /* tp_name */
    sizeof(pyVisRegion),                /* tp_basicsize */
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
    "plVisRegion wrapper",             /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyVisRegion_GetSet,                 /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyVisRegion_new,                    /* tp_new */
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

PyObject* Init_pyVisRegion_Type() {
    pyVisRegion_Type.tp_base = &pyObjInterface_Type;
    if (PyType_Ready(&pyVisRegion_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyVisRegion_Type.tp_dict, "kDisable",
                         PyInt_FromLong(plVisRegion::kDisable));
    PyDict_SetItemString(pyVisRegion_Type.tp_dict, "kIsNot",
                         PyInt_FromLong(plVisRegion::kIsNot));
    PyDict_SetItemString(pyVisRegion_Type.tp_dict, "kReplaceNormal",
                         PyInt_FromLong(plVisRegion::kReplaceNormal));
    PyDict_SetItemString(pyVisRegion_Type.tp_dict, "kDisableNormal",
                         PyInt_FromLong(plVisRegion::kDisableNormal));

    Py_INCREF(&pyVisRegion_Type);
    return (PyObject*)&pyVisRegion_Type;
}

PY_PLASMA_IFC_METHODS(VisRegion, plVisRegion)

}
