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

PY_PLASMA_NEW(ResponderModifier, plResponderModifier)

PY_METHOD_VA(ResponderModifier, addState,
    "Params: state\n"
    "Add a responder state to the Responder")
{
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
    Py_RETURN_NONE;
}

PY_METHOD_VA(ResponderModifier, delState,
    "Params: idx\n"
    "Delete a state from the Responder")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delState expects an int");
        return NULL;
    }
    self->fThis->delState(idx);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(ResponderModifier, clearStates, "Delete all states from the Responder") {
    self->fThis->clearStates();
    Py_RETURN_NONE;
}

static PyObject* pyResponderModifier_getStates(pyResponderModifier* self, void*) {
    PyObject* list = PyList_New(self->fThis->getStates().size());
    for (size_t i=0; i<self->fThis->getStates().size(); i++)
        PyList_SET_ITEM(list, i, pyResponderModifier_State_FromResponderModifier_State(self->fThis->getStates()[i]));
    return list;
}

static int pyResponderModifier_setStates(pyResponderModifier* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "to add states, use addState");
    return -1;
}

static PyMethodDef pyResponderModifier_Methods[] = {
    pyResponderModifier_addState_method,
    pyResponderModifier_delState_method,
    pyResponderModifier_clearStates_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY(signed char, ResponderModifier, curState, getCurState, setCurState)
PY_PROPERTY(bool, ResponderModifier, enabled, isEnabled, setEnabled)
PY_PROPERTY(unsigned char, ResponderModifier, flags, getFlags, setFlags)

static PyGetSetDef pyResponderModifier_GetSet[] = {
    { _pycs("states"), (getter)pyResponderModifier_getStates,
        (setter)pyResponderModifier_setStates, NULL, NULL },
    pyResponderModifier_curState_getset,
    pyResponderModifier_enabled_getset,
    pyResponderModifier_flags_getset,
    PY_GETSET_TERMINATOR
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

    PY_TYPE_ADD_CONST(ResponderModifier, "kDetectTrigger",
                      plResponderModifier::kDetectTrigger);
    PY_TYPE_ADD_CONST(ResponderModifier, "kDetectUnTrigger",
                      plResponderModifier::kDetectUnTrigger);
    PY_TYPE_ADD_CONST(ResponderModifier, "kSkipFFSound",
                      plResponderModifier::kSkipFFSound);

    Py_INCREF(&pyResponderModifier_Type);
    return (PyObject*)&pyResponderModifier_Type;
}

PY_PLASMA_IFC_METHODS(ResponderModifier, plResponderModifier)

}
