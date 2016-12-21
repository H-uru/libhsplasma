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

#include "pyResponderModifier.h"

#include <PRP/Modifier/plResponderModifier.h>
#include "pyModifier.h"
#include "PRP/pyCreatable.h"

extern "C" {

static PyObject* pyResponderModifier_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyResponderModifier* self = (pyResponderModifier*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plResponderModifier();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyResponderModifier_addState(pyResponderModifier* self, PyObject* args) {
    pyResponderModifier_State* state;
    if (!PyArg_ParseTuple(args, "O", &state)) {
        PyErr_SetString(PyExc_TypeError, "addState expects a plResponderModifier_State");
        return NULL;
    }
    if (!pyResponderModifier_State_Check((PyObject*)state)) {
        PyErr_SetString(PyExc_TypeError, "addState expects a plResponderModifier_State");
        return NULL;
    }
    self->fThis->addState(state->fThis);
    state->fPyOwned = false;
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyResponderModifier_delState(pyResponderModifier* self, PyObject* args) {
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delState expects an int");
        return NULL;
    }
    self->fThis->delState(idx);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyResponderModifier_clearStates(pyResponderModifier* self) {
    self->fThis->clearStates();
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject* pyResponderModifier_getStates(pyResponderModifier* self, void*) {
    PyObject* list = PyList_New(self->fThis->getStates().size());
    for (size_t i=0; i<self->fThis->getStates().size(); i++)
        PyList_SET_ITEM(list, i, pyResponderModifier_State_FromResponderModifier_State(self->fThis->getStates()[i]));
    return list;
}

static PyObject* pyResponderModifier_getCurState(pyResponderModifier* self, void*) {
    return PyInt_FromLong(self->fThis->getCurState());
}

static PyObject* pyResponderModifier_getEnabled(pyResponderModifier* self, void*) {
    return PyBool_FromLong(self->fThis->isEnabled() ? 1 : 0);
}

static PyObject* pyResponderModifier_getFlags(pyResponderModifier* self, void*) {
    return PyInt_FromLong(self->fThis->getFlags());
}

static int pyResponderModifier_setStates(pyResponderModifier* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "to add states, use addState");
    return -1;
}

static int pyResponderModifier_setCurState(pyResponderModifier* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "curState should be an int");
        return -1;
    }
    self->fThis->setCurState(PyInt_AsLong(value));
    return 0;
}

static int pyResponderModifier_setEnabled(pyResponderModifier* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "enabled should be a bool");
        return -1;
    }
    self->fThis->setEnabled(PyInt_AsLong(value) != 0);
    return 0;
}

static int pyResponderModifier_setFlags(pyResponderModifier* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "flags should be an int");
        return -1;
    }
    self->fThis->setFlags(PyInt_AsLong(value));
    return 0;
}

static PyMethodDef pyResponderModifier_Methods[] = {
    { "addState", (PyCFunction)pyResponderModifier_addState, METH_VARARGS,
      "Params: state\n"
      "Add a responder state to the Responder" },
    { "delState", (PyCFunction)pyResponderModifier_delState, METH_VARARGS,
      "Params: idx\n"
      "Delete a state from the Responder" },
    { "clearStates", (PyCFunction)pyResponderModifier_clearStates, METH_NOARGS,
      "Delete all states from the Responder" },
    { NULL, NULL, 0, NULL }
};

static PyGetSetDef pyResponderModifier_GetSet[] = {
    { _pycs("states"), (getter)pyResponderModifier_getStates,
        (setter)pyResponderModifier_setStates, NULL, NULL },
    { _pycs("curState"), (getter)pyResponderModifier_getCurState,
        (setter)pyResponderModifier_setCurState, NULL, NULL },
    { _pycs("enabled"), (getter)pyResponderModifier_getEnabled,
        (setter)pyResponderModifier_setEnabled, NULL, NULL },
    { _pycs("flags"), (getter)pyResponderModifier_getFlags,
        (setter)pyResponderModifier_setFlags, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pyResponderModifier_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plResponderModifier",   /* tp_name */
    sizeof(pyResponderModifier),        /* tp_basicsize */
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
    "plResponderModifier wrapper",      /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyResponderModifier_Methods,        /* tp_methods */
    NULL,                               /* tp_members */
    pyResponderModifier_GetSet,         /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyResponderModifier_new,            /* tp_new */
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

PyObject* Init_pyResponderModifier_Type() {
    pyResponderModifier_Type.tp_base = &pySingleModifier_Type;
    if (PyType_Ready(&pyResponderModifier_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyResponderModifier_Type.tp_dict, "kDetectTrigger",
                         PyInt_FromLong(plResponderModifier::kDetectTrigger));
    PyDict_SetItemString(pyResponderModifier_Type.tp_dict, "kDetectUnTrigger",
                         PyInt_FromLong(plResponderModifier::kDetectUnTrigger));
    PyDict_SetItemString(pyResponderModifier_Type.tp_dict, "kSkipFFSound",
                         PyInt_FromLong(plResponderModifier::kSkipFFSound));

    Py_INCREF(&pyResponderModifier_Type);
    return (PyObject*)&pyResponderModifier_Type;
}

PY_PLASMA_IFC_METHODS(ResponderModifier, plResponderModifier)

}
