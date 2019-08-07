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

PY_PLASMA_NEW(AnimCmdMsg, plAnimCmdMsg)

PY_PROPERTY(ST::string, AnimCmdMsg, animName, getAnimName, setAnimName)
PY_PROPERTY(ST::string, AnimCmdMsg, loopName, getLoopName, setLoopName)
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

PY_METHOD_VA(AnimCmdMsg, getCmd, "Params: cmd")
{
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "getCmd expects an int");
        return nullptr;
    }
    return pyPlasma_convert(self->fThis->getCmd((size_t)idx));
}

PY_METHOD_VA(AnimCmdMsg, setCmd, "Params: cmd, value")
{
    Py_ssize_t idx, value;
    if (!PyArg_ParseTuple(args, "nn", &idx, &value)) {
        PyErr_SetString(PyExc_TypeError, "setCmd expects int, bool");
        return nullptr;
    }
    self->fThis->setCmd(idx, value != 0);
    Py_RETURN_NONE;
}

static PyMethodDef pyAnimCmdMsg_Methods[] = {
    pyAnimCmdMsg_getCmd_method,
    pyAnimCmdMsg_setCmd_method,
    PY_METHOD_TERMINATOR
};

PY_PLASMA_TYPE(AnimCmdMsg, plAnimCmdMsg, "plAnimCmdMsg wrapper")

PY_PLASMA_TYPE_INIT(AnimCmdMsg)
{
    pyAnimCmdMsg_Type.tp_new = pyAnimCmdMsg_new;
    pyAnimCmdMsg_Type.tp_methods = pyAnimCmdMsg_Methods;
    pyAnimCmdMsg_Type.tp_getset = pyAnimCmdMsg_GetSet;
    pyAnimCmdMsg_Type.tp_base = &pyMessageWithCallbacks_Type;
    if (PyType_CheckAndReady(&pyAnimCmdMsg_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(AnimCmdMsg, "kContinue", plAnimCmdMsg::kContinue);
    PY_TYPE_ADD_CONST(AnimCmdMsg, "kStop", plAnimCmdMsg::kStop);
    PY_TYPE_ADD_CONST(AnimCmdMsg, "kSetLooping", plAnimCmdMsg::kSetLooping);
    PY_TYPE_ADD_CONST(AnimCmdMsg, "kUnSetLooping", plAnimCmdMsg::kUnSetLooping);
    PY_TYPE_ADD_CONST(AnimCmdMsg, "kSetBegin", plAnimCmdMsg::kSetBegin);
    PY_TYPE_ADD_CONST(AnimCmdMsg, "kSetEnd", plAnimCmdMsg::kSetEnd);
    PY_TYPE_ADD_CONST(AnimCmdMsg, "kSetLoopEnd", plAnimCmdMsg::kSetLoopEnd);
    PY_TYPE_ADD_CONST(AnimCmdMsg, "kSetLoopBegin", plAnimCmdMsg::kSetLoopBegin);
    PY_TYPE_ADD_CONST(AnimCmdMsg, "kSetSpeed", plAnimCmdMsg::kSetSpeed);
    PY_TYPE_ADD_CONST(AnimCmdMsg, "kGoToTime", plAnimCmdMsg::kGoToTime);
    PY_TYPE_ADD_CONST(AnimCmdMsg, "kSetBackwards", plAnimCmdMsg::kSetBackwards);
    PY_TYPE_ADD_CONST(AnimCmdMsg, "kSetForwards", plAnimCmdMsg::kSetForwards);
    PY_TYPE_ADD_CONST(AnimCmdMsg, "kToggleState", plAnimCmdMsg::kToggleState);
    PY_TYPE_ADD_CONST(AnimCmdMsg, "kAddCallbacks", plAnimCmdMsg::kAddCallbacks);
    PY_TYPE_ADD_CONST(AnimCmdMsg, "kRemoveCallbacks", plAnimCmdMsg::kRemoveCallbacks);
    PY_TYPE_ADD_CONST(AnimCmdMsg, "kGoToBegin", plAnimCmdMsg::kGoToBegin);
    PY_TYPE_ADD_CONST(AnimCmdMsg, "kGoToEnd", plAnimCmdMsg::kGoToEnd);
    PY_TYPE_ADD_CONST(AnimCmdMsg, "kGoToLoopBegin", plAnimCmdMsg::kGoToLoopBegin);
    PY_TYPE_ADD_CONST(AnimCmdMsg, "kGoToLoopEnd", plAnimCmdMsg::kGoToLoopEnd);
    PY_TYPE_ADD_CONST(AnimCmdMsg, "kIncrementForward", plAnimCmdMsg::kIncrementForward);
    PY_TYPE_ADD_CONST(AnimCmdMsg, "kIncrementBackward", plAnimCmdMsg::kIncrementBackward);
    PY_TYPE_ADD_CONST(AnimCmdMsg, "kRunForward", plAnimCmdMsg::kRunForward);
    PY_TYPE_ADD_CONST(AnimCmdMsg, "kRunBackward", plAnimCmdMsg::kRunBackward);
    PY_TYPE_ADD_CONST(AnimCmdMsg, "kPlayToTime", plAnimCmdMsg::kPlayToTime);
    PY_TYPE_ADD_CONST(AnimCmdMsg, "kPlayToPercentage", plAnimCmdMsg::kPlayToPercentage);
    PY_TYPE_ADD_CONST(AnimCmdMsg, "kFastForward", plAnimCmdMsg::kFastForward);
    PY_TYPE_ADD_CONST(AnimCmdMsg, "kGoToPercent", plAnimCmdMsg::kGoToPercent);
    PY_TYPE_ADD_CONST(AnimCmdMsg, "kNumCmds", plAnimCmdMsg::kNumCmds);


    Py_INCREF(&pyAnimCmdMsg_Type);
    return (PyObject*)&pyAnimCmdMsg_Type;
}

PY_PLASMA_IFC_METHODS(AnimCmdMsg, plAnimCmdMsg)
