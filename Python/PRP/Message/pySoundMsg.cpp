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

PY_PLASMA_NEW(SoundMsg, plSoundMsg)

static PyObject* pySoundMsg_getCmd(pySoundMsg* self, PyObject* args) {
    int cmd;
    if (!PyArg_ParseTuple(args, "i", &cmd)) {
        PyErr_SetString(PyExc_TypeError, "getCmd expects an int");
        return NULL;
    }
    return pyPlasma_convert(self->fThis->getCmd(cmd));
}

static PyObject* pySoundMsg_setCmd(pySoundMsg* self, PyObject* args) {
    int cmd;
    int value = 1;
    if (!PyArg_ParseTuple(args, "i|i", &cmd, &value)) {
        PyErr_SetString(PyExc_TypeError, "setCmd expects an int and an optional int");
        return NULL;
    }
    self->fThis->setCmd(cmd, value != 0);
    Py_RETURN_NONE;
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

PY_PROPERTY(double, SoundMsg, begin, getBegin, setBegin)
PY_PROPERTY(double, SoundMsg, end, getEnd, setEnd)
PY_PROPERTY(bool, SoundMsg, loop, getLoop, setLoop)
PY_PROPERTY(bool, SoundMsg, playing, getPlaying, setPlaying)
PY_PROPERTY(float, SoundMsg, speed, getSpeed, setSpeed)
PY_PROPERTY(double, SoundMsg, time, getTime, setTime)
PY_PROPERTY(int, SoundMsg, index, getIndex, setIndex)
PY_PROPERTY(int, SoundMsg, repeats, getRepeats, setRepeats)
PY_PROPERTY(float, SoundMsg, volume, getVolume, setVolume)
PY_PROPERTY(plSoundMsg::FadeType, SoundMsg, fadeType, getFadeType, setFadeType)

static PyGetSetDef pySoundMsg_GetSet[] = {
    pySoundMsg_begin_getset,
    pySoundMsg_end_getset,
    pySoundMsg_loop_getset,
    pySoundMsg_playing_getset,
    pySoundMsg_speed_getset,
    pySoundMsg_time_getset,
    pySoundMsg_index_getset,
    pySoundMsg_repeats_getset,
    pySoundMsg_volume_getset,
    pySoundMsg_fadeType_getset,
    PY_GETSET_TERMINATOR
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

PY_PLASMA_IFC_METHODS(SoundMsg, plSoundMsg)

};
