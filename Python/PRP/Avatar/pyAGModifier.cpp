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

#include "pyAGModifier.h"

#include <PRP/Avatar/plAGModifier.h>
#include "PRP/Modifier/pyModifier.h"

extern "C" {

static PyObject* pyAGModifier_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyAGModifier* self = (pyAGModifier*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plAGModifier();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

PY_PROPERTY(plString, AGModifier, channelName, getChannelName, setChannelName)
PY_PROPERTY(bool, AGModifier, autoApply, getAutoApply, setAutoApply)
PY_PROPERTY(bool, AGModifier, enabled, getEnabled, setEnabled)

static PyGetSetDef pyAGModifier_GetSet[] = {
    pyAGModifier_channelName_getset,
    pyAGModifier_autoApply_getset,
    pyAGModifier_enabled_getset,
    PY_GETSET_TERMINATOR
};

PyTypeObject pyAGModifier_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plAGModifier",          /* tp_name */
    sizeof(pyAGModifier),               /* tp_basicsize */
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
    "plAGModifier wrapper",                   /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyAGModifier_GetSet,                /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyAGModifier_new,                   /* tp_new */
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

PyObject* Init_pyAGModifier_Type() {
    pyAGModifier_Type.tp_base = &pyModifier_Type;
    if (PyType_Ready(&pyAGModifier_Type) < 0)
        return NULL;

    Py_INCREF(&pyAGModifier_Type);
    return (PyObject*)&pyAGModifier_Type;
}

PY_PLASMA_IFC_METHODS(AGModifier, plAGModifier)

};
