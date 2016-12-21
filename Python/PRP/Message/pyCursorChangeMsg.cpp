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

#include "pyCursorChangeMsg.h"

#include <PRP/Message/plCursorChangeMsg.h>
#include "pyMessage.h"

extern "C" {

static PyObject* pyCursorChangeMsg_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyCursorChangeMsg* self = (pyCursorChangeMsg*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plCursorChangeMsg();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyCursorChangeMsg_getType(pyCursorChangeMsg* self, void*) {
    return PyInt_FromLong(self->fThis->getType());
}

static PyObject* pyCursorChangeMsg_getPriority(pyCursorChangeMsg* self, void*) {
    return PyInt_FromLong(self->fThis->getPriority());
}

static int pyCursorChangeMsg_setType(pyCursorChangeMsg* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "type should be an int");
        return -1;
    }
    self->fThis->setType(PyInt_AsLong(value));
    return 0;
}

static int pyCursorChangeMsg_setPriority(pyCursorChangeMsg* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "priority should be an int");
        return -1;
    }
    self->fThis->setPriority(PyInt_AsLong(value));
    return 0;
}

static PyGetSetDef pyCursorChangeMsg_GetSet[] = {
    { _pycs("type"), (getter)pyCursorChangeMsg_getType, (setter)pyCursorChangeMsg_setType, NULL, NULL },
    { _pycs("priority"), (getter)pyCursorChangeMsg_getPriority, (setter)pyCursorChangeMsg_setPriority, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyCursorChangeMsg_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plCursorChangeMsg",     /* tp_name */
    sizeof(pyCursorChangeMsg),          /* tp_basicsize */
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
    "plCursorChangeMsg wrapper",              /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    NULL,                               /* tp_methods */
    NULL,                               /* tp_members */
    pyCursorChangeMsg_GetSet,           /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyCursorChangeMsg_new,              /* tp_new */
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

PyObject* Init_pyCursorChangeMsg_Type() {
    pyCursorChangeMsg_Type.tp_base = &pyMessage_Type;
    if (PyType_Ready(&pyCursorChangeMsg_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyCursorChangeMsg_Type.tp_dict, "kNoChange",
                         PyInt_FromLong(plCursorChangeMsg::kNoChange));
    PyDict_SetItemString(pyCursorChangeMsg_Type.tp_dict, "kCursorUp",
                         PyInt_FromLong(plCursorChangeMsg::kCursorUp));
    PyDict_SetItemString(pyCursorChangeMsg_Type.tp_dict, "kCursorLeft",
                         PyInt_FromLong(plCursorChangeMsg::kCursorLeft));
    PyDict_SetItemString(pyCursorChangeMsg_Type.tp_dict, "kCursorRight",
                         PyInt_FromLong(plCursorChangeMsg::kCursorRight));
    PyDict_SetItemString(pyCursorChangeMsg_Type.tp_dict, "kCursorDown",
                         PyInt_FromLong(plCursorChangeMsg::kCursorDown));
    PyDict_SetItemString(pyCursorChangeMsg_Type.tp_dict, "kCursorPoised",
                         PyInt_FromLong(plCursorChangeMsg::kCursorPoised));
    PyDict_SetItemString(pyCursorChangeMsg_Type.tp_dict, "kCursorClicked",
                         PyInt_FromLong(plCursorChangeMsg::kCursorClicked));
    PyDict_SetItemString(pyCursorChangeMsg_Type.tp_dict, "kCursorUnClicked",
                         PyInt_FromLong(plCursorChangeMsg::kCursorUnClicked));
    PyDict_SetItemString(pyCursorChangeMsg_Type.tp_dict, "kCursorHidden",
                         PyInt_FromLong(plCursorChangeMsg::kCursorHidden));
    PyDict_SetItemString(pyCursorChangeMsg_Type.tp_dict, "kCursorOpen",
                         PyInt_FromLong(plCursorChangeMsg::kCursorOpen));
    PyDict_SetItemString(pyCursorChangeMsg_Type.tp_dict, "kCursorGrab",
                         PyInt_FromLong(plCursorChangeMsg::kCursorGrab));
    PyDict_SetItemString(pyCursorChangeMsg_Type.tp_dict, "kCursorArrow",
                         PyInt_FromLong(plCursorChangeMsg::kCursorArrow));
    PyDict_SetItemString(pyCursorChangeMsg_Type.tp_dict, "kNullCursor",
                         PyInt_FromLong(plCursorChangeMsg::kNullCursor));

    Py_INCREF(&pyCursorChangeMsg_Type);
    return (PyObject*)&pyCursorChangeMsg_Type;
}

PY_PLASMA_IFC_METHODS(CursorChangeMsg, plCursorChangeMsg)

}
