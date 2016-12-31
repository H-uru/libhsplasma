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

#include "pySwimMsg.h"

#include "PRP/KeyedObject/pyKey.h"
#include <PRP/Message/plSwimMsg.h>
#include "pyMessage.h"

extern "C" {

static PyObject* pySwimMsg_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pySwimMsg* self = (pySwimMsg*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plSwimMsg();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pySwimMsg_getIsEntering(pySwimMsg* self, void*) {
    return PyBool_FromLong(self->fThis->getIsEntering());
}

static PyObject* pySwimMsg_getSwimRegion(pySwimMsg* self, void*) {
    return pyKey_FromKey(self->fThis->getSwimRegion());
}

static int pySwimMsg_setIsEntering(pySwimMsg* self, PyObject* value, void*) {
    if (PyBool_Check(value)) {
        self->fThis->setIsEntering(PyInt_AsLong(value));
        return 0;
    }
    PyErr_SetString(PyExc_TypeError, "isEntering should be a boolean");
    return -1;
}

static int pySwimMsg_setSwimRegion(pySwimMsg* self, PyObject* value, void*) {
    if (value == Py_None || value == NULL) {
        self->fThis->setSwimRegion(plKey());
        return 0;
    } else if (pyKey_Check(value)) {
        self->fThis->setSwimRegion(*((pyKey*)value)->fThis);
        return 0;
    }
    PyErr_SetString(PyExc_TypeError, "swimRegion should be a plKey");
    return -1;
}

static PyGetSetDef pySwimMsg_GetSet[] = {
    { _pycs("isEntering"), (getter)pySwimMsg_getIsEntering, (setter)pySwimMsg_setIsEntering, NULL, NULL },
    { _pycs("swimRegion"), (getter)pySwimMsg_getSwimRegion, (setter)pySwimMsg_setSwimRegion, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pySwimMsg_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plSwimMsg",             /* tp_name */
    sizeof(pySwimMsg),                  /* tp_basicsize */
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
    "plSwimMsg wrapper",                      /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pySwimMsg_GetSet,                   /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pySwimMsg_new,                      /* tp_new */
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

PyObject* Init_pySwimMsg_Type() {
    pySwimMsg_Type.tp_base = &pyMessage_Type;
    if (PyType_Ready(&pySwimMsg_Type) < 0)
        return NULL;

    Py_INCREF(&pySwimMsg_Type);
    return (PyObject*)&pySwimMsg_Type;
}

PY_PLASMA_IFC_METHODS(SwimMsg, plSwimMsg)

}
