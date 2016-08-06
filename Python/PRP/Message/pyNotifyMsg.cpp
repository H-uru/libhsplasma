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

#include "pyNotifyMsg.h"

#include <PRP/Message/plNotifyMsg.h>
#include "pyMessage.h"
#include "pyEventData.h"
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyNotifyMsg_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyNotifyMsg* self = (pyNotifyMsg*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plNotifyMsg();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyNotifyMsg_clearEvents(pyNotifyMsg* self) {
    self->fThis->clearEvents();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyNotifyMsg_addEvent(pyNotifyMsg* self, PyObject* args) {
    pyEventData* evt;
    if (!PyArg_ParseTuple(args, "O", &evt)) {
        PyErr_SetString(PyExc_TypeError, "addEvent expects a proEventData");
        return NULL;
    }
    if (!pyEventData_Check((PyObject*)evt)) {
        PyErr_SetString(PyExc_TypeError, "addEvent expects a proEventData");
        return NULL;
    }
    self->fThis->addEvent(evt->fThis);
    evt->fPyOwned = false;
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyNotifyMsg_delEvent(pyNotifyMsg* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delEvent expects an int");
        return NULL;
    }
    self->fThis->delEvent(idx);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyNotifyMsg_getEvents(pyNotifyMsg* self, void*) {
    PyObject* list = PyList_New(self->fThis->getEvents().size());
    for (size_t i=0; i<self->fThis->getEvents().size(); i++)
        PyList_SET_ITEM(list, i, pyEventData_FromEventData(self->fThis->getEvents()[i]));
    return list;
}

static PyObject* pyNotifyMsg_getType(pyNotifyMsg* self, void*) {
    return PyInt_FromLong(self->fThis->getType());
}

static PyObject* pyNotifyMsg_getState(pyNotifyMsg* self, void*) {
    return PyFloat_FromDouble(self->fThis->getState());
}

static PyObject* pyNotifyMsg_getID(pyNotifyMsg* self, void*) {
    return PyInt_FromLong(self->fThis->getID());
}

static int pyNotifyMsg_setEvents(pyNotifyMsg* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "to add events, use addEvent");
    return -1;
}

static int pyNotifyMsg_setType(pyNotifyMsg* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "type should be an int");
        return -1;
    }
    self->fThis->setType(PyInt_AsLong(value));
    return 0;
}

static int pyNotifyMsg_setState(pyNotifyMsg* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "state should be an int");
        return -1;
    }
    self->fThis->setState(PyFloat_AsDouble(value));
    return 0;
}

static int pyNotifyMsg_setID(pyNotifyMsg* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "id should be an int");
        return -1;
    }
    self->fThis->setID(PyInt_AsLong(value));
    return 0;
}

static PyMethodDef pyNotifyMsg_Methods[] = {
    { "clearEvents", (PyCFunction)pyNotifyMsg_clearEvents, METH_NOARGS,
      "Remove all event objects" },
    { "addEvent", (PyCFunction)pyNotifyMsg_addEvent, METH_VARARGS,
      "Params: event\n"
      "Add an event" },
    { "delEvent", (PyCFunction)pyNotifyMsg_delEvent, METH_NOARGS,
      "Params: idx\n"
      "Remove an event" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyNotifyMsg_GetSet[] = {
    { _pycs("events"), (getter)pyNotifyMsg_getEvents,
        (setter)pyNotifyMsg_setEvents, NULL, NULL },
    { _pycs("type"), (getter)pyNotifyMsg_getType,
        (setter)pyNotifyMsg_setType, NULL, NULL },
    { _pycs("state"), (getter)pyNotifyMsg_getState,
        (setter)pyNotifyMsg_setState, NULL, NULL },
    { _pycs("id"), (getter)pyNotifyMsg_getID, (setter)pyNotifyMsg_setID, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyNotifyMsg_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plNotifyMsg",           /* tp_name */
    sizeof(pyNotifyMsg),                /* tp_basicsize */
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
    "plNotifyMsg wrapper",              /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyNotifyMsg_Methods,                /* tp_methods */
    NULL,                               /* tp_members */
    pyNotifyMsg_GetSet,                 /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyNotifyMsg_new,                    /* tp_new */
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

PyObject* Init_pyNotifyMsg_Type() {
    pyNotifyMsg_Type.tp_base = &pyMessage_Type;
    if (PyType_Ready(&pyNotifyMsg_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyNotifyMsg_Type.tp_dict, "kActivator",
                         PyInt_FromLong(plNotifyMsg::kActivator));
    PyDict_SetItemString(pyNotifyMsg_Type.tp_dict, "kVarNotification",
                         PyInt_FromLong(plNotifyMsg::kVarNotification));
    PyDict_SetItemString(pyNotifyMsg_Type.tp_dict, "kNotifySelf",
                         PyInt_FromLong(plNotifyMsg::kNotifySelf));
    PyDict_SetItemString(pyNotifyMsg_Type.tp_dict, "kResponderFF",
                         PyInt_FromLong(plNotifyMsg::kResponderFF));
    PyDict_SetItemString(pyNotifyMsg_Type.tp_dict, "kResponderChangeState",
                         PyInt_FromLong(plNotifyMsg::kResponderChangeState));

    Py_INCREF(&pyNotifyMsg_Type);
    return (PyObject*)&pyNotifyMsg_Type;
}

int pyNotifyMsg_Check(PyObject* obj) {
    if (obj->ob_type == &pyNotifyMsg_Type
        || PyType_IsSubtype(obj->ob_type, &pyNotifyMsg_Type))
        return 1;
    return 0;
}

PyObject* pyNotifyMsg_FromNotifyMsg(plNotifyMsg* msg) {
    if (msg == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyNotifyMsg* pyobj = PyObject_New(pyNotifyMsg, &pyNotifyMsg_Type);
    pyobj->fThis = msg;
    pyobj->fPyOwned = false;
    return (PyObject*)pyobj;
}

}
