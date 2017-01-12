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

#include "pyAnimTimeConvert.h"

#include <PRP/Animation/plAnimTimeConvert.h>
#include "pyATCEaseCurves.h"
#include "PRP/Message/pyEventCallbackMsg.h"
#include "PRP/pyCreatable.h"

extern "C" {

PY_PLASMA_NEW(AnimTimeConvert, plAnimTimeConvert)

PY_METHOD_VA(AnimTimeConvert, addCallback,
    "Params: callback\n"
    "Add a callback message to the object")
{
    pyEventCallbackMsg* msg;
    if (!PyArg_ParseTuple(args, "O", &msg)) {
        PyErr_SetString(PyExc_TypeError, "addCallback expects a plEventCallbackMsg");
        return NULL;
    }
    if (!pyEventCallbackMsg_Check((PyObject*)msg)) {
        PyErr_SetString(PyExc_TypeError, "addCallback expects a plEventCallbackMsg");
        return NULL;
    }
    msg->fPyOwned = false;
    self->fThis->addCallback(msg->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(AnimTimeConvert, delCallback,
    "Params: idx\n"
    "Delete a callback message from the object")
{
    int idx;
    if (!PyArg_ParseTuple(args, "i", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delCallback expects an int");
        return NULL;
    }
    self->fThis->delCallback(idx);
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(AnimTimeConvert, clearCallbacks, "Delete all callbacks from the object") {
    self->fThis->clearCallbacks();
    Py_RETURN_NONE;
}

static PyObject* pyAnimTimeConvert_getStops(pyAnimTimeConvert* self, void*) {
    PyObject* list = PyList_New(self->fThis->getStopPoints().size());
    for (size_t i=0; i<self->fThis->getStopPoints().size(); i++)
        PyList_SET_ITEM(list, i, pyPlasma_convert(self->fThis->getStopPoints()[i]));
    return list;
}

static PyObject* pyAnimTimeConvert_getCallbacks(pyAnimTimeConvert* self, void*) {
    PyObject* list = PyList_New(self->fThis->getCallbacks().size());
    for (size_t i=0; i<self->fThis->getCallbacks().size(); i++)
        PyList_SET_ITEM(list, i, ICreate(self->fThis->getCallbacks()[i]));
    return list;
}

static int pyAnimTimeConvert_setStops(pyAnimTimeConvert* self, PyObject* value, void*) {
    if (value == NULL || value == Py_None) {
        Py_XDECREF(value);
        self->fThis->setStopPoints(std::vector<float>());
        return 0;
    }
    if (!PyList_Check(value)) {
        PyErr_SetString(PyExc_TypeError, "stopPoints should be a list of floats");
        return -1;
    }
    std::vector<float> stops(PyList_Size(value));
    for (size_t i=0; i<stops.size(); i++) {
        PyObject* itm = PyList_GetItem(value, i);
        if (!pyPlasma_check<float>(itm)) {
            PyErr_SetString(PyExc_TypeError, "stopPoints should be a list of floats");
            return -1;
        }
        stops[i] = pyPlasma_get<float>(itm);
    }
    self->fThis->setStopPoints(stops);
    return 0;
}

static int pyAnimTimeConvert_setCallbacks(pyAnimTimeConvert* self, PyObject* value, void*) {
    PyErr_SetString(PyExc_RuntimeError, "To add callbacks, use addCallback()");
    return -1;
}

static PyMethodDef pyAnimTimeConvert_Methods[] = {
    pyAnimTimeConvert_addCallback_method,
    pyAnimTimeConvert_delCallback_method,
    pyAnimTimeConvert_clearCallbacks_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY(unsigned int, AnimTimeConvert, flags, getFlags, setFlags)
PY_PROPERTY(float, AnimTimeConvert, begin, getBegin, setBegin)
PY_PROPERTY(float, AnimTimeConvert, end, getEnd, setEnd)
PY_PROPERTY(float, AnimTimeConvert, loopBegin, getLoopBegin, setLoopBegin)
PY_PROPERTY(float, AnimTimeConvert, loopEnd, getLoopEnd, setLoopEnd)
PY_PROPERTY(float, AnimTimeConvert, speed, getSpeed, setSpeed)
PY_PROPERTY(float, AnimTimeConvert, currentAnimTime, getCurrentAnimTime,
            setCurrentAnimTime)
PY_PROPERTY(double, AnimTimeConvert, lastEvalWorldTime, getLastEvalWorldTime,
            setLastEvalWorldTime)

PY_PROPERTY_CREATABLE(plATCEaseCurve, ATCEaseCurve, AnimTimeConvert,
                      easeInCurve, getEaseInCurve, setEaseInCurve)
PY_PROPERTY_CREATABLE(plATCEaseCurve, ATCEaseCurve, AnimTimeConvert,
                      easeOutCurve, getEaseOutCurve, setEaseOutCurve)
PY_PROPERTY_CREATABLE(plATCEaseCurve, ATCEaseCurve, AnimTimeConvert,
                      speedEaseCurve, getSpeedEaseCurve, setSpeedEaseCurve)

static PyGetSetDef pyAnimTimeConvert_GetSet[] = {
    pyAnimTimeConvert_flags_getset,
    pyAnimTimeConvert_begin_getset,
    pyAnimTimeConvert_end_getset,
    pyAnimTimeConvert_loopBegin_getset,
    pyAnimTimeConvert_loopEnd_getset,
    pyAnimTimeConvert_speed_getset,
    pyAnimTimeConvert_currentAnimTime_getset,
    pyAnimTimeConvert_lastEvalWorldTime_getset,
    pyAnimTimeConvert_easeInCurve_getset,
    pyAnimTimeConvert_easeOutCurve_getset,
    pyAnimTimeConvert_speedEaseCurve_getset,
    { _pycs("stopPoints"), (getter)pyAnimTimeConvert_getStops,
        (setter)pyAnimTimeConvert_setStops, NULL, NULL },
    { _pycs("callbacks"), (getter)pyAnimTimeConvert_getCallbacks,
        (setter)pyAnimTimeConvert_setCallbacks, NULL, NULL },
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(AnimTimeConvert, plAnimTimeConvert, "plAnimTimeConvert wrapper")

PY_PLASMA_TYPE_INIT(AnimTimeConvert) {
    pyAnimTimeConvert_Type.tp_new = pyAnimTimeConvert_new;
    pyAnimTimeConvert_Type.tp_methods = pyAnimTimeConvert_Methods;
    pyAnimTimeConvert_Type.tp_getset = pyAnimTimeConvert_GetSet;
    pyAnimTimeConvert_Type.tp_base = &pyCreatable_Type;
    if (PyType_CheckAndReady(&pyAnimTimeConvert_Type) < 0)
        return NULL;

    PY_TYPE_ADD_CONST(AnimTimeConvert, "kNone", plAnimTimeConvert::kNone);
    PY_TYPE_ADD_CONST(AnimTimeConvert, "kStopped",plAnimTimeConvert::kStopped);
    PY_TYPE_ADD_CONST(AnimTimeConvert, "kLoop",plAnimTimeConvert::kLoop);
    PY_TYPE_ADD_CONST(AnimTimeConvert, "kBackwards",plAnimTimeConvert::kBackwards);
    PY_TYPE_ADD_CONST(AnimTimeConvert, "kWrap",plAnimTimeConvert::kWrap);
    PY_TYPE_ADD_CONST(AnimTimeConvert, "kNeedsReset",plAnimTimeConvert::kNeedsReset);
    PY_TYPE_ADD_CONST(AnimTimeConvert, "kEasingIn",plAnimTimeConvert::kEasingIn);
    PY_TYPE_ADD_CONST(AnimTimeConvert, "kForcedMove",plAnimTimeConvert::kForcedMove);
    PY_TYPE_ADD_CONST(AnimTimeConvert, "kNoCallbacks",plAnimTimeConvert::kNoCallbacks);
    PY_TYPE_ADD_CONST(AnimTimeConvert, "kFlagsMask",plAnimTimeConvert::kFlagsMask);

    Py_INCREF(&pyAnimTimeConvert_Type);
    return (PyObject*)&pyAnimTimeConvert_Type;
}

PY_PLASMA_IFC_METHODS(AnimTimeConvert, plAnimTimeConvert)

}
