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

#include "pySoundMsg.h"

#include <PRP/Message/plSoundMsg.h>
#include "pyMessageWithCallbacks.h"

extern "C" {

static PyObject* pySoundMsg_new(PyTypeObject* type, PyObject* args, PyObject* kwds) {
    pySoundMsg* self = (pySoundMsg*)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->fThis = new plSoundMsg();
        self->fPyOwned = true;
    }
    return (PyObject*)self;
}

static PyObject* pySoundMsg_getCmd(pySoundMsg* self, PyObject* args) {
    int cmd;
    if (!PyArg_ParseTuple(args, "i", &cmd)) {
        PyErr_SetString(PyExc_TypeError, "getCmd expects an int");
        return NULL;
    }
    return PyBool_FromLong(self->fThis->getCmd(cmd) ? 1 : 0);
}

static PyObject* pySoundMsg_setCmd(pySoundMsg* self, PyObject* args) {
    int cmd;
    int value = 1;
    if (!PyArg_ParseTuple(args, "i|i", &cmd, &value)) {
        PyErr_SetString(PyExc_TypeError, "setCmd expects an int and an optional int");
        return NULL;
    }
    self->fThis->setCmd(cmd, value != 0);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyMethodDef pySoundMsg_Methods[] = {
    { "getCmd", (PyCFunction)pySoundMsg_getCmd, METH_VARARGS,
      "Params: cmd\n"
      "Returns whether or not the command is set" },
    { "setCmd", (PyCFunction)pySoundMsg_setCmd, METH_VARARGS,
      "Params: cmd, value\n"
      "Sets the specified command" },
    { NULL, NULL, 0, NULL }
};

static PyObject* pySoundMsg_getBegin(pySoundMsg* self, void*) {
    return PyFloat_FromDouble(self->fThis->getBegin());
}

static PyObject* pySoundMsg_getEnd(pySoundMsg* self, void*) {
    return PyFloat_FromDouble(self->fThis->getEnd());
}

static PyObject* pySoundMsg_getLoop(pySoundMsg* self, void*) {
    return PyBool_FromLong(self->fThis->getLoop() ? 1 : 0);
}

static PyObject* pySoundMsg_getPlaying(pySoundMsg* self, void*) {
    return PyBool_FromLong(self->fThis->getPlaying() ? 1 : 0);
}

static PyObject* pySoundMsg_getSpeed(pySoundMsg* self, void*) {
    return PyFloat_FromDouble(self->fThis->getSpeed());
}

static PyObject* pySoundMsg_getTime(pySoundMsg* self, void*) {
    return PyFloat_FromDouble(self->fThis->getTime());
}

static PyObject* pySoundMsg_getIndex(pySoundMsg* self, void*) {
    return PyInt_FromLong(self->fThis->getIndex());
}

static PyObject* pySoundMsg_getRepeats(pySoundMsg* self, void*) {
    return PyInt_FromLong(self->fThis->getRepeats());
}

static PyObject* pySoundMsg_getVolume(pySoundMsg* self, void*) {
    return PyFloat_FromDouble(self->fThis->getVolume());
}

static PyObject* pySoundMsg_getFadeType(pySoundMsg* self, void*) {
    return PyInt_FromLong((long)self->fThis->getFadeType());
}

static int pySoundMsg_setBegin(pySoundMsg* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "begin should be a float");
        return -1;
    }
    self->fThis->setBegin(PyFloat_AsDouble(value));
    return 0;
}

static int pySoundMsg_setEnd(pySoundMsg* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "end should be a float");
        return -1;
    }
    self->fThis->setEnd(PyFloat_AsDouble(value));
    return 0;
}

static int pySoundMsg_setLoop(pySoundMsg* self, PyObject* value, void*) {
    if (value == NULL || !PyBool_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "loop should be a boolean");
        return -1;
    }
    self->fThis->setLoop(PyInt_AsLong(value) != 0);
    return 0;
}

static int pySoundMsg_setPlaying(pySoundMsg* self, PyObject* value, void*) {
    if (value == NULL || !PyBool_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "playing should be a boolean");
        return -1;
    }
    self->fThis->setPlaying(PyInt_AsLong(value) != 0);
    return 0;
}

static int pySoundMsg_setSpeed(pySoundMsg* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "speed should be a float");
        return -1;
    }
    self->fThis->setSpeed((float)PyFloat_AsDouble(value));
    return 0;
}

static int pySoundMsg_setTime(pySoundMsg* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "time should be a float");
        return -1;
    }
    self->fThis->setTime(PyFloat_AsDouble(value));
    return 0;
}

static int pySoundMsg_setIndex(pySoundMsg* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "index should be an int");
        return -1;
    }
    self->fThis->setIndex(PyInt_AsLong(value));
    return 0;
}

static int pySoundMsg_setRepeats(pySoundMsg* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "repeats should be an int");
        return -1;
    }
    self->fThis->setRepeats(PyInt_AsLong(value));
    return 0;
}

static int pySoundMsg_setVolume(pySoundMsg* self, PyObject* value, void*) {
    if (value == NULL || !PyFloat_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "volume should be a float");
        return -1;
    }
    self->fThis->setVolume((float)PyFloat_AsDouble(value));
    return 0;
}

static int pySoundMsg_setFadeType(pySoundMsg* self, PyObject* value, void*) {
    if (value == NULL || !PyInt_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "fadeType should be an int");
        return -1;
    }
    self->fThis->setFadeType((plSoundMsg::FadeType)PyInt_AsLong(value));
    return 0;
}

static PyGetSetDef pySoundMsg_GetSet[] = {
    { _pycs("begin"), (getter)pySoundMsg_getBegin, (setter)pySoundMsg_setBegin, NULL, NULL },
    { _pycs("end"), (getter)pySoundMsg_getEnd, (setter)pySoundMsg_setEnd, NULL, NULL },
    { _pycs("loop"), (getter)pySoundMsg_getLoop, (setter)pySoundMsg_setLoop, NULL, NULL },
    { _pycs("playing"), (getter)pySoundMsg_getPlaying, (setter)pySoundMsg_setPlaying, NULL, NULL },
    { _pycs("speed"), (getter)pySoundMsg_getSpeed, (setter)pySoundMsg_setSpeed, NULL, NULL },
    { _pycs("time"), (getter)pySoundMsg_getTime, (setter)pySoundMsg_setTime, NULL, NULL },
    { _pycs("index"), (getter)pySoundMsg_getIndex, (setter)pySoundMsg_setIndex, NULL, NULL },
    { _pycs("repeats"), (getter)pySoundMsg_getRepeats, (setter)pySoundMsg_setRepeats, NULL, NULL },
    { _pycs("volume"), (getter)pySoundMsg_getVolume, (setter)pySoundMsg_setVolume, NULL, NULL },
    { _pycs("fadeType"), (getter)pySoundMsg_getFadeType, (setter)pySoundMsg_setFadeType, NULL, NULL },
    { NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pySoundMsg_Type = {
    PyVarObject_HEAD_INIT(NULL, 0)
    "PyHSPlasma.plSoundMsg",            /* tp_name */
    sizeof(pySoundMsg),                 /* tp_basicsize */
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
    "plSoundMsg wrapper",                     /* tp_doc */

    NULL,                               /* tp_traverse */
    NULL,                               /* tp_clear */
    NULL,                               /* tp_richcompare */
    0,                                  /* tp_weaklistoffset */
    NULL,                               /* tp_iter */
    NULL,                               /* tp_iternext */

    pySoundMsg_Methods,                 /* tp_methods */
    NULL,                               /* tp_members */
    pySoundMsg_GetSet,                  /* tp_getset */
    NULL,                               /* tp_base */
    NULL,                               /* tp_dict */
    NULL,                               /* tp_descr_get */
    NULL,                               /* tp_descr_set */
    0,                                  /* tp_dictoffset */

    NULL,                               /* tp_init */
    NULL,                               /* tp_alloc */
    pySoundMsg_new,                     /* tp_new */
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

PyObject* Init_pySoundMsg_Type() {
    pySoundMsg_Type.tp_base = &pyMessageWithCallbacks_Type;
    if (PyType_Ready(&pySoundMsg_Type) < 0)
        return NULL;

    PyDict_SetItemString(pySoundMsg_Type.tp_dict, "kPlay",
                         PyInt_FromLong(plSoundMsg::kPlay));
    PyDict_SetItemString(pySoundMsg_Type.tp_dict, "kStop",
                         PyInt_FromLong(plSoundMsg::kStop));
    PyDict_SetItemString(pySoundMsg_Type.tp_dict, "kSetLooping",
                         PyInt_FromLong(plSoundMsg::kSetLooping));
    PyDict_SetItemString(pySoundMsg_Type.tp_dict, "kUnSetLooping",
                         PyInt_FromLong(plSoundMsg::kUnSetLooping));
    PyDict_SetItemString(pySoundMsg_Type.tp_dict, "kSetBegin",
                         PyInt_FromLong(plSoundMsg::kSetBegin));
    PyDict_SetItemString(pySoundMsg_Type.tp_dict, "kToggleState",
                         PyInt_FromLong(plSoundMsg::kToggleState));
    PyDict_SetItemString(pySoundMsg_Type.tp_dict, "kAddCallbacks",
                         PyInt_FromLong(plSoundMsg::kAddCallbacks));
    PyDict_SetItemString(pySoundMsg_Type.tp_dict, "kRemoveCallbacks",
                         PyInt_FromLong(plSoundMsg::kRemoveCallbacks));
    PyDict_SetItemString(pySoundMsg_Type.tp_dict, "kGetStatus",
                         PyInt_FromLong(plSoundMsg::kGetStatus));
    PyDict_SetItemString(pySoundMsg_Type.tp_dict, "kNumSounds",
                         PyInt_FromLong(plSoundMsg::kNumSounds));
    PyDict_SetItemString(pySoundMsg_Type.tp_dict, "kStatusReply",
                         PyInt_FromLong(plSoundMsg::kStatusReply));
    PyDict_SetItemString(pySoundMsg_Type.tp_dict, "kGoToTime",
                         PyInt_FromLong(plSoundMsg::kGoToTime));
    PyDict_SetItemString(pySoundMsg_Type.tp_dict, "kSetVolume",
                         PyInt_FromLong(plSoundMsg::kSetVolume));
    PyDict_SetItemString(pySoundMsg_Type.tp_dict, "kSetTalkIcon",
                         PyInt_FromLong(plSoundMsg::kSetTalkIcon));
    PyDict_SetItemString(pySoundMsg_Type.tp_dict, "kClearTalkIcon",
                         PyInt_FromLong(plSoundMsg::kClearTalkIcon));
    PyDict_SetItemString(pySoundMsg_Type.tp_dict, "kSetFadeIn",
                         PyInt_FromLong(plSoundMsg::kSetFadeIn));
    PyDict_SetItemString(pySoundMsg_Type.tp_dict, "kSetFadeOut",
                         PyInt_FromLong(plSoundMsg::kSetFadeOut));
    PyDict_SetItemString(pySoundMsg_Type.tp_dict, "kIsLocalOnly",
                         PyInt_FromLong(plSoundMsg::kIsLocalOnly));
    PyDict_SetItemString(pySoundMsg_Type.tp_dict, "kSelectFromGroup",
                         PyInt_FromLong(plSoundMsg::kSelectFromGroup));
    PyDict_SetItemString(pySoundMsg_Type.tp_dict, "kNumCmds",
                         PyInt_FromLong(plSoundMsg::kNumCmds));
    PyDict_SetItemString(pySoundMsg_Type.tp_dict, "kFastForwardPlay",
                         PyInt_FromLong(plSoundMsg::kFastForwardPlay));
    PyDict_SetItemString(pySoundMsg_Type.tp_dict, "kFastForwardToggle",
                         PyInt_FromLong(plSoundMsg::kFastForwardToggle));

    PyDict_SetItemString(pySoundMsg_Type.tp_dict, "kLinear",
                         PyInt_FromLong(plSoundMsg::kLinear));
    PyDict_SetItemString(pySoundMsg_Type.tp_dict, "kLogarithmic",
                         PyInt_FromLong(plSoundMsg::kLogarithmic));
    PyDict_SetItemString(pySoundMsg_Type.tp_dict, "kExponential",
                         PyInt_FromLong(plSoundMsg::kExponential));

    Py_INCREF(&pySoundMsg_Type);
    return (PyObject*)&pySoundMsg_Type;
}

int pySoundMsg_Check(PyObject* obj) {
    if (obj->ob_type == &pySoundMsg_Type
        || PyType_IsSubtype(obj->ob_type, &pySoundMsg_Type))
        return 1;
    return 0;
}

PyObject* pySoundMsg_FromSoundMsg(class plSoundMsg* obj) {
    if (obj == NULL) {
        Py_INCREF(Py_None);
        return Py_None;
    }
    pySoundMsg* py = PyObject_New(pySoundMsg, &pySoundMsg_Type);
    py->fThis = obj;
    py->fPyOwned = false;
    return (PyObject*)py;
}

};
