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

#include "pyAnimCmdMsg.h"

#include <PRP/Message/plAnimCmdMsg.h>
#include "pyMessageWithCallbacks.h"

extern "C" {

static PyObject* pyAnimCmdMsg_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pyAnimCmdMsg* self = (pyAnimCmdMsg*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plAnimCmdMsg();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pyAnimCmdMsg_getAnimName(pyAnimCmdMsg* self, void*) {
    return PlStr_To_PyStr(self->fThis->getAnimName());
}

static PyObject* pyAnimCmdMsg_getLoopName(pyAnimCmdMsg* self, void*) {
    return PlStr_To_PyStr(self->fThis->getLoopName());
}

static PyObject* pyAnimCmdMsg_getBegin(pyAnimCmdMsg* self, void*) {
    return PyFloat_FromDouble(self->fThis->getBegin());
}

static PyObject* pyAnimCmdMsg_getEnd(pyAnimCmdMsg* self, void*) {
    return PyFloat_FromDouble(self->fThis->getEnd());
}

static PyObject* pyAnimCmdMsg_getLoopBegin(pyAnimCmdMsg* self, void*) {
    return PyFloat_FromDouble(self->fThis->getLoopBegin());
}

static PyObject* pyAnimCmdMsg_getLoopEnd(pyAnimCmdMsg* self, void*) {
    return PyFloat_FromDouble(self->fThis->getLoopEnd());
}

static PyObject* pyAnimCmdMsg_getSpeed(pyAnimCmdMsg* self, void*) {
    return PyFloat_FromDouble(self->fThis->getSpeed());
}

static PyObject* pyAnimCmdMsg_getSpeedChangeRate(pyAnimCmdMsg* self, void*) {
    return PyFloat_FromDouble(self->fThis->getSpeedChangeRate());
}

static PyObject* pyAnimCmdMsg_getTime(pyAnimCmdMsg* self, void*) {
    return PyFloat_FromDouble(self->fThis->getTime());
}

static int pyAnimCmdMsg_setAnimName(pyAnimCmdMsg* self, PyObject* value, void*) {
    if (value == NULL || !PyAnyStr_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "animName expects a string");
        return -1;
    }
    self->fThis->setAnimName(PyStr_To_PlStr(value));
    return 0;
}

static int pyAnimCmdMsg_setLoopName(pyAnimCmdMsg* self, PyObject* value, void*) {
    if (value == NULL || !PyAnyStr_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "loopName expects a string");
        return -1;
    }
    self->fThis->setLoopName(PyStr_To_PlStr(value));
    return 0;
}

static int pyAnimCmdMsg_setBegin(pyAnimCmdMsg* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "begin should be a float");
        return -1;
    }
    self->fThis->setBegin((float)PyFloat_AsDouble(value));
    return 0;
}

static int pyAnimCmdMsg_setEnd(pyAnimCmdMsg* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "end should be a float");
        return -1;
    }
    self->fThis->setEnd((float)PyFloat_AsDouble(value));
    return 0;
}

static int pyAnimCmdMsg_setLoopBegin(pyAnimCmdMsg* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "loopBegin should be a float");
        return -1;
    }
    self->fThis->setLoopBegin((float)PyFloat_AsDouble(value));
    return 0;
}

static int pyAnimCmdMsg_setLoopEnd(pyAnimCmdMsg* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "loopEnd should be a float");
        return -1;
    }
    self->fThis->setLoopEnd((float)PyFloat_AsDouble(value));
    return 0;
}

static int pyAnimCmdMsg_setSpeed(pyAnimCmdMsg* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "speed should be a float");
        return -1;
    }
    self->fThis->setSpeed((float)PyFloat_AsDouble(value));
    return 0;
}

static int pyAnimCmdMsg_setSpeedChangeRate(pyAnimCmdMsg* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "speedChangeRate should be a float");
        return -1;
    }
    self->fThis->setSpeedChangeRate((float)PyFloat_AsDouble(value));
    return 0;
}

static int pyAnimCmdMsg_setTime(pyAnimCmdMsg* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "time should be a float");
        return -1;
    }
    self->fThis->setTime((float)PyFloat_AsDouble(value));
    return 0;
}

static PyGetSetDef pyAnimCmdMsg_GetSet[] = {
    { _pycs("animName"), (getter)pyAnimCmdMsg_getAnimName, (setter)pyAnimCmdMsg_setAnimName, NULL, NULL },
    { _pycs("loopName"), (getter)pyAnimCmdMsg_getLoopName, (setter)pyAnimCmdMsg_setLoopName, NULL, NULL },
    { _pycs("begin"), (getter)pyAnimCmdMsg_getBegin, (setter)pyAnimCmdMsg_setBegin, NULL, NULL },
    { _pycs("end"), (getter)pyAnimCmdMsg_getEnd, (setter)pyAnimCmdMsg_setEnd, NULL, NULL },
    { _pycs("loopBegin"), (getter)pyAnimCmdMsg_getLoopBegin, (setter)pyAnimCmdMsg_setLoopBegin, NULL, NULL },
    { _pycs("loopEnd"), (getter)pyAnimCmdMsg_getLoopEnd, (setter)pyAnimCmdMsg_setLoopEnd, NULL, NULL },
    { _pycs("speed"), (getter)pyAnimCmdMsg_getSpeed, (setter)pyAnimCmdMsg_setSpeed, NULL, NULL },
    { _pycs("speedChangeRate"), (getter)pyAnimCmdMsg_getSpeedChangeRate, (setter)pyAnimCmdMsg_setSpeedChangeRate, NULL, NULL },
    { _pycs("time"), (getter)pyAnimCmdMsg_getTime, (setter)pyAnimCmdMsg_setTime, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

static PyObject* pyAnimCmdMsg_getCmd(pyAnimCmdMsg* self, PyObject* args) {
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "getCmd expects an int");
        return NULL;
    }
    return PyBool_FromLong(self->fThis->getCmd((size_t)idx) ? 1 : 0);
}

static PyObject* pyAnimCmdMsg_setCmd(pyAnimCmdMsg* self, PyObject* args) {
    Py_ssize_t idx, value;
    if (!PyArg_ParseTuple(args, "nn", &idx, &value)) {
        PyErr_SetString(PyExc_TypeError, "setCmd expects int, bool");
        return NULL;
    }
    self->fThis->setCmd(idx, value != 0);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef pyAnimCmdMsg_Methods[] = {
    { "getCmd", (PyCFunction)pyAnimCmdMsg_getCmd, METH_VARARGS,
      "Params: cmd" },
    { "setCmd", (PyCFunction)pyAnimCmdMsg_setCmd, METH_VARARGS,
      "Params: cmd, value" },
    { NULL, NULL, 0, NULL }
};

PyTypeObject pyAnimCmdMsg_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plAnimCmdMsg",          /* tp_name */
    sizeof(pyAnimCmdMsg),               /* tp_basicsize */
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
    "plAnimCmdMsg wrapper",                   /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pyAnimCmdMsg_Methods,               /* tp_methods */
    NULL,                               /* tp_members */
    pyAnimCmdMsg_GetSet,                /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pyAnimCmdMsg_new,                   /* tp_new */
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

PyObject* Init_pyAnimCmdMsg_Type() {
    pyAnimCmdMsg_Type.tp_base = &pyMessageWithCallbacks_Type;
    if (PyType_Ready(&pyAnimCmdMsg_Type) < 0)
        return NULL;

    PyDict_SetItemString(pyAnimCmdMsg_Type.tp_dict, "kContinue",
                         PyInt_FromLong(plAnimCmdMsg::kContinue));
    PyDict_SetItemString(pyAnimCmdMsg_Type.tp_dict, "kStop",
                         PyInt_FromLong(plAnimCmdMsg::kStop));
    PyDict_SetItemString(pyAnimCmdMsg_Type.tp_dict, "kSetLooping",
                         PyInt_FromLong(plAnimCmdMsg::kSetLooping));
    PyDict_SetItemString(pyAnimCmdMsg_Type.tp_dict, "kUnSetLooping",
                         PyInt_FromLong(plAnimCmdMsg::kUnSetLooping));
    PyDict_SetItemString(pyAnimCmdMsg_Type.tp_dict, "kSetBegin",
                         PyInt_FromLong(plAnimCmdMsg::kSetBegin));
    PyDict_SetItemString(pyAnimCmdMsg_Type.tp_dict, "kSetEnd",
                         PyInt_FromLong(plAnimCmdMsg::kSetEnd));
    PyDict_SetItemString(pyAnimCmdMsg_Type.tp_dict, "kSetLoopEnd",
                         PyInt_FromLong(plAnimCmdMsg::kSetLoopEnd));
    PyDict_SetItemString(pyAnimCmdMsg_Type.tp_dict, "kSetLoopBegin",
                         PyInt_FromLong(plAnimCmdMsg::kSetLoopBegin));
    PyDict_SetItemString(pyAnimCmdMsg_Type.tp_dict, "kSetSpeed",
                         PyInt_FromLong(plAnimCmdMsg::kSetSpeed));
    PyDict_SetItemString(pyAnimCmdMsg_Type.tp_dict, "kGoToTime",
                         PyInt_FromLong(plAnimCmdMsg::kGoToTime));
    PyDict_SetItemString(pyAnimCmdMsg_Type.tp_dict, "kSetBackwards",
                         PyInt_FromLong(plAnimCmdMsg::kSetBackwards));
    PyDict_SetItemString(pyAnimCmdMsg_Type.tp_dict, "kSetForwards",
                         PyInt_FromLong(plAnimCmdMsg::kSetForwards));
    PyDict_SetItemString(pyAnimCmdMsg_Type.tp_dict, "kToggleState",
                         PyInt_FromLong(plAnimCmdMsg::kToggleState));
    PyDict_SetItemString(pyAnimCmdMsg_Type.tp_dict, "kAddCallbacks",
                         PyInt_FromLong(plAnimCmdMsg::kAddCallbacks));
    PyDict_SetItemString(pyAnimCmdMsg_Type.tp_dict, "kRemoveCallbacks",
                         PyInt_FromLong(plAnimCmdMsg::kRemoveCallbacks));
    PyDict_SetItemString(pyAnimCmdMsg_Type.tp_dict, "kGoToBegin",
                         PyInt_FromLong(plAnimCmdMsg::kGoToBegin));
    PyDict_SetItemString(pyAnimCmdMsg_Type.tp_dict, "kGoToEnd",
                         PyInt_FromLong(plAnimCmdMsg::kGoToEnd));
    PyDict_SetItemString(pyAnimCmdMsg_Type.tp_dict, "kGoToLoopBegin",
                         PyInt_FromLong(plAnimCmdMsg::kGoToLoopBegin));
    PyDict_SetItemString(pyAnimCmdMsg_Type.tp_dict, "kGoToLoopEnd",
                         PyInt_FromLong(plAnimCmdMsg::kGoToLoopEnd));
    PyDict_SetItemString(pyAnimCmdMsg_Type.tp_dict, "kIncrementForward",
                         PyInt_FromLong(plAnimCmdMsg::kIncrementForward));
    PyDict_SetItemString(pyAnimCmdMsg_Type.tp_dict, "kIncrementBackward",
                         PyInt_FromLong(plAnimCmdMsg::kIncrementBackward));
    PyDict_SetItemString(pyAnimCmdMsg_Type.tp_dict, "kRunForward",
                         PyInt_FromLong(plAnimCmdMsg::kRunForward));
    PyDict_SetItemString(pyAnimCmdMsg_Type.tp_dict, "kRunBackward",
                         PyInt_FromLong(plAnimCmdMsg::kRunBackward));
    PyDict_SetItemString(pyAnimCmdMsg_Type.tp_dict, "kPlayToTime",
                         PyInt_FromLong(plAnimCmdMsg::kPlayToTime));
    PyDict_SetItemString(pyAnimCmdMsg_Type.tp_dict, "kPlayToPercentage",
                         PyInt_FromLong(plAnimCmdMsg::kPlayToPercentage));
    PyDict_SetItemString(pyAnimCmdMsg_Type.tp_dict, "kFastForward",
                         PyInt_FromLong(plAnimCmdMsg::kFastForward));
    PyDict_SetItemString(pyAnimCmdMsg_Type.tp_dict, "kGoToPercent",
                         PyInt_FromLong(plAnimCmdMsg::kGoToPercent));
    PyDict_SetItemString(pyAnimCmdMsg_Type.tp_dict, "kNumCmds",
                         PyInt_FromLong(plAnimCmdMsg::kNumCmds));


    Py_INCREF(&pyAnimCmdMsg_Type);
    return (PyObject*)&pyAnimCmdMsg_Type;
}

int pyAnimCmdMsg_Check(PyObject* obj) {
    if (obj->ob_type == &pyAnimCmdMsg_Type
        || PyType_IsSubtype(obj->ob_type, &pyAnimCmdMsg_Type))
        return 1;
    return 0;
}

PyObject* pyAnimCmdMsg_FromAnimCmdMsg(class plAnimCmdMsg* obj) {
    if (obj == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pyAnimCmdMsg* py = PyObject_New(pyAnimCmdMsg, &pyAnimCmdMsg_Type);
    py->fThis = obj;
    py->fPyOwned = false;
    return (PyObject*)py;
}

};
