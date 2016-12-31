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

PY_PLASMA_NEW(AnimCmdMsg, plAnimCmdMsg)

PY_PROPERTY(plString, AnimCmdMsg, animName, getAnimName, setAnimName)
PY_PROPERTY(plString, AnimCmdMsg, loopName, getLoopName, setLoopName)
PY_PROPERTY(float, AnimCmdMsg, begin, getBegin, setBegin)
PY_PROPERTY(float, AnimCmdMsg, end, getEnd, setEnd)
PY_PROPERTY(float, AnimCmdMsg, loopBegin, getLoopBegin, setLoopBegin)
PY_PROPERTY(float, AnimCmdMsg, loopEnd, getLoopEnd, setLoopEnd)
PY_PROPERTY(float, AnimCmdMsg, speed, getSpeed, setSpeed)
PY_PROPERTY(float, AnimCmdMsg, speedChangeRate, getSpeedChangeRate, setSpeedChangeRate)
PY_PROPERTY(float, AnimCmdMsg, time, getTime, setTime)

static PyGetSetDef pyAnimCmdMsg_GetSet[] = {
    pyAnimCmdMsg_animName_getset,
    pyAnimCmdMsg_loopName_getset,
    pyAnimCmdMsg_begin_getset,
    pyAnimCmdMsg_end_getset,
    pyAnimCmdMsg_loopBegin_getset,
    pyAnimCmdMsg_loopEnd_getset,
    pyAnimCmdMsg_speed_getset,
    pyAnimCmdMsg_speedChangeRate_getset,
    pyAnimCmdMsg_time_getset,
    PY_GETSET_TERMINATOR
};

static PyObject* pyAnimCmdMsg_getCmd(pyAnimCmdMsg* self, PyObject* args) {
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "getCmd expects an int");
        return NULL;
    }
    return pyPlasma_convert(self->fThis->getCmd((size_t)idx));
}

static PyObject* pyAnimCmdMsg_setCmd(pyAnimCmdMsg* self, PyObject* args) {
    Py_ssize_t idx, value;
    if (!PyArg_ParseTuple(args, "nn", &idx, &value)) {
        PyErr_SetString(PyExc_TypeError, "setCmd expects int, bool");
        return NULL;
    }
    self->fThis->setCmd(idx, value != 0);
    Py_RETURN_NONE;
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

PY_PLASMA_IFC_METHODS(AnimCmdMsg, plAnimCmdMsg)

};
