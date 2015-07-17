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
#include <PRP/Message/plExcludeRegionMsg.h>
#include "pyExcludeRegionMsg.h"
#include "pyMessage.h"

extern "C" {

static PyObject* pyExcludeRegionMsg_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyExcludeRegionMsg* self = (pyExcludeRegionMsg*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plExcludeRegionMsg();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyExcludeRegionMsg_getCmd(pyExcludeRegionMsg* self, void*) {
    return PyInt_FromLong(self->fThis->getCmd());
}

static PyObject* pyExcludeRegionMsg_getSynchFlags(pyExcludeRegionMsg* self, void*) {
    return PyInt_FromLong(self->fThis->getSynchFlags());
}

static int pyExcludeRegionMsg_setCmd(pyExcludeRegionMsg* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "cmd should be an int");
        return -1;
    }
    self->fThis->setCmd((unsigned char)PyInt_AsLong(value));
    return 0;
}

static int pyExcludeRegionMsg_setSynchFlags(pyExcludeRegionMsg* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "synchFlags should be an int");
        return -1;
    }
    self->fThis->setSynchFlags(PyInt_AsLong(value));
    return 0;
}

static PyGetSetDef pyExcludeRegionMsg_GetSet[] = {
    { _pycs("cmd"), (getter)pyExcludeRegionMsg_getCmd, (setter)pyExcludeRegionMsg_setCmd, NULL, NULL },
    { _pycs("synchFlags"), (getter)pyExcludeRegionMsg_getSynchFlags, (setter)pyExcludeRegionMsg_setSynchFlags, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyExcludeRegionMsg_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plExcludeRegionMsg",    /* tp_name */
    sizeof(pyExcludeRegionMsg),         /* tp_basicsize */
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
    "plExcludeRegionMsg wrapper",             /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyExcludeRegionMsg_GetSet,          /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyExcludeRegionMsg_new,             /* tp_new */
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

PyObject* Init_pyExcludeRegionMsg_Type() {
    pyExcludeRegionMsg_Type.tp_base = &pyMessage_Type;
    if (PyType_Ready(&pyExcludeRegionMsg_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyExcludeRegionMsg_Type.tp_dict, "kClear",
                         PyInt_FromLong(plExcludeRegionMsg::kClear));
    PyDict_SetItemString(pyExcludeRegionMsg_Type.tp_dict, "kRelease",
                         PyInt_FromLong(plExcludeRegionMsg::kRelease));

    Py_INCREF(&pyExcludeRegionMsg_Type);
    return (PyObject*)&pyExcludeRegionMsg_Type;
}

int pyExcludeRegionMsg_Check(PyObject* obj) {
    if (obj->ob_type == &pyExcludeRegionMsg_Type
        || PyType_IsSubtype(obj->ob_type, &pyExcludeRegionMsg_Type))
        return 1;
    return 0;
}

PyObject* pyExcludeRegionMsg_FromExcludeRegionMsg(class plExcludeRegionMsg* atc) {
    if (atc == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyExcludeRegionMsg* pyobj = PyObject_New(pyExcludeRegionMsg, &pyExcludeRegionMsg_Type);
    pyobj->fThis = atc;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
