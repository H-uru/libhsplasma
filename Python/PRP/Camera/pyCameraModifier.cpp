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

#include "pyCameraModifier.h"

#include "Math/pyGeometry3.h"
#include "PRP/pyCreatable.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/Message/pyCameraMsg.h"
#include "PRP/Message/pyMessage.h"
#include "PRP/Modifier/pyModifier.h"

/* pyCamTrans */

PY_PLASMA_NEW(CamTrans, plCameraModifier::CamTrans)

PY_PROPERTY(plKey, CamTrans, transTo, getTransTo, setTransTo)
PY_PROPERTY(bool, CamTrans, cutPos, getCutPos, setCutPos)
PY_PROPERTY(bool, CamTrans, cutPOA, getCutPOA, setCutPOA)
PY_PROPERTY(bool, CamTrans, ignore, getIgnore, setIgnore)
PY_PROPERTY(float, CamTrans, accel, getAccel, setAccel)
PY_PROPERTY(float, CamTrans, decel, getDecel, setDecel)
PY_PROPERTY(float, CamTrans, velocity, getVelocity, setVelocity)
PY_PROPERTY(float, CamTrans, poaAccel, getPOAAccel, setPOAAccel)
PY_PROPERTY(float, CamTrans, poaDecel, getPOADecel, setPOADecel)
PY_PROPERTY(float, CamTrans, poaVelocity, getPOAVelocity, setPOAVelocity)

static PyGetSetDef pyCamTrans_GetSet[] = {
    pyCamTrans_transTo_getset,
    pyCamTrans_cutPos_getset,
    pyCamTrans_cutPOA_getset,
    pyCamTrans_ignore_getset,
    pyCamTrans_accel_getset,
    pyCamTrans_decel_getset,
    pyCamTrans_velocity_getset,
    pyCamTrans_poaAccel_getset,
    pyCamTrans_poaDecel_getset,
    pyCamTrans_poaVelocity_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(CamTrans, plCameraModifier::CamTrans, "plCameraModifier::CamTrans wrapper")

PY_PLASMA_TYPE_INIT(CamTrans)
{
    pyCamTrans_Type.tp_new = pyCamTrans_new;
    pyCamTrans_Type.tp_getset = pyCamTrans_GetSet;
    if (PyType_CheckAndReady(&pyCamTrans_Type) < 0)
        return nullptr;

    Py_INCREF(&pyCamTrans_Type);
    return (PyObject*)&pyCamTrans_Type;
}

PY_PLASMA_IFC_METHODS(CamTrans, plCameraModifier::CamTrans)

/* pyCameraModifier */

PY_PLASMA_NEW(CameraModifier, plCameraModifier)

PY_METHOD_VA(CameraModifier, addTrans, "Params: trans")
{
    pyCamTrans* trans;
    if (!PyArg_ParseTuple(args, "O", &trans) || !pyCamTrans_Check((PyObject*)trans)) {
        PyErr_SetString(PyExc_TypeError, "addTrans expects a plCameraModifier.CamTrans");
        return nullptr;
    }
    trans->fPyOwned = false;
    self->fThis->addTrans(trans->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(CameraModifier, delTrans, "Params: idx")
{
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delTrans expects an int");
        return nullptr;
    }
    if ((size_t)idx < self->fThis->getTrans().size()) {
        self->fThis->delTrans(idx);
        Py_RETURN_NONE;
    } else {
        PyErr_SetNone(PyExc_IndexError);
        return nullptr;
    }
}

PY_METHOD_NOARGS(CameraModifier, clearTrans, "Clears all transitions")
{
    self->fThis->clearTrans();
    Py_RETURN_NONE;
}

PY_METHOD_VA(CameraModifier, addMessage, "Params: message, sender")
{
    pyMessage* message;
    pyKey* sender;
    if (!PyArg_ParseTuple(args, "O|O", &message, &sender) ||
            !pyMessage_Check((PyObject*)message) ||
            !(sender == nullptr || pyKey_Check((PyObject*)sender))) {
        PyErr_SetString(PyExc_TypeError, "addMessage expects a plMessage and an optional plKey");
        return nullptr;
    }
    message->fPyOwned = false;
    self->fThis->addMessage(message->fThis, sender ? *sender->fThis : plKey());
    Py_RETURN_NONE;
}

PY_METHOD_VA(CameraModifier, delMessage, "Params: idx")
{
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delMessage expects an int");
        return nullptr;
    }
    if ((size_t)idx < self->fThis->getMessageQueueSize()) {
        self->fThis->delMessage(idx);
        Py_RETURN_NONE;
    } else {
        PyErr_SetNone(PyExc_IndexError);
        return nullptr;
    }
}

PY_METHOD_NOARGS(CameraModifier, clearMessageQueue, "Clears the message queue")
{
    self->fThis->clearMessageQueue();
    Py_RETURN_NONE;
}

PY_METHOD_VA(CameraModifier, addFOVInstruction, "Params: msg")
{
    pyCameraMsg* msg;
    if (!PyArg_ParseTuple(args, "O", &msg) || !pyCameraMsg_Check((PyObject*)msg)) {
        PyErr_SetString(PyExc_TypeError, "addFOVInstruction expects a plCameraMsg");
        return nullptr;
    }
    msg->fPyOwned = false;
    self->fThis->addFOVInstruction(msg->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(CameraModifier, delFOVInstruction, "Params: idx")
{
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delFOVInstruction expects an int");
        return nullptr;
    }
    if ((size_t)idx < self->fThis->getFOVInstructions().size()) {
        self->fThis->delFOVInstruction(idx);
        Py_RETURN_NONE;
    } else {
        PyErr_SetNone(PyExc_IndexError);
        return nullptr;
    }
}

PY_METHOD_NOARGS(CameraModifier, clearFOVInstructions, "Clears all FOVInstructions")
{
    self->fThis->clearFOVInstructions();
    Py_RETURN_NONE;
}

static PyMethodDef pyCameraModifier_Methods[] = {
    pyCameraModifier_addTrans_method,
    pyCameraModifier_delTrans_method,
    pyCameraModifier_clearTrans_method,
    pyCameraModifier_addMessage_method,
    pyCameraModifier_delMessage_method,
    pyCameraModifier_clearMessageQueue_method,
    pyCameraModifier_addFOVInstruction_method,
    pyCameraModifier_delFOVInstruction_method,
    pyCameraModifier_clearFOVInstructions_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY(hsVector3, CameraModifier, from, getFrom, setFrom)
PY_PROPERTY(hsVector3, CameraModifier, at, getAt, setAt)
PY_PROPERTY(plKey, CameraModifier, brain, getBrain, setBrain)
PY_PROPERTY(float, CameraModifier, fovW, getFOVw, setFOVw)
PY_PROPERTY(float, CameraModifier, fovH, getFOVh, setFOVh)
PY_PROPERTY(bool, CameraModifier, animated, getAnimated, setAnimated)
PY_PROPERTY(bool, CameraModifier, startAnimOnPush, getStartAnimOnPush, setStartAnimOnPush)
PY_PROPERTY(bool, CameraModifier, stopAnimOnPop, getStopAnimOnPop, setStopAnimOnPop)
PY_PROPERTY(bool, CameraModifier, resetAnimOnPop, getResetAnimOnPop, setResetAnimOnPop)

PY_GETSET_GETTER_DECL(CameraModifier, trans)
{
    const std::vector<plCameraModifier::CamTrans*>& trans = self->fThis->getTrans();
    PyObject* tup = PyTuple_New(trans.size());
    for (size_t i = 0; i < trans.size(); ++i)
        PyTuple_SET_ITEM(tup, i, pyCamTrans_FromCamTrans(trans[i]));
    return tup;
}
PY_PROPERTY_SETTER_MSG(CameraModifier, trans, "To add transitions, use addTrans()")
PY_PROPERTY_GETSET_DECL(CameraModifier, trans)

PY_GETSET_GETTER_DECL(CameraModifier, messageQueue)
{
    PyObject* tup = PyTuple_New(self->fThis->getMessageQueueSize());
    for (size_t i = 0; i < self->fThis->getMessageQueueSize(); ++i) {
        auto msg = self->fThis->getMessage(i);
        PyObject* value = Py_BuildValue("OO", ICreate(std::get<0>(msg)),
                                              pyKey_FromKey(std::get<1>(msg)));
        PyTuple_SET_ITEM(tup, i, value);
    }
    return tup;
}
PY_PROPERTY_SETTER_MSG(CameraModifier, messageQueue, "To add messages, use addMessage()")
PY_PROPERTY_GETSET_DECL(CameraModifier, messageQueue)

PY_GETSET_GETTER_DECL(CameraModifier, fovInstructions)
{
    const std::vector<plCameraMsg*>& msgs = self->fThis->getFOVInstructions();
    PyObject* tup = PyTuple_New(msgs.size());
    for (size_t i = 0; i < msgs.size(); ++i)
        PyTuple_SET_ITEM(tup, i, ICreate(msgs[i]));
    return tup;
}
PY_PROPERTY_SETTER_MSG(CameraModifier, fovInstructions, "To add FOV Instructions, use addFOVInstruction()")
PY_PROPERTY_GETSET_DECL(CameraModifier, fovInstructions)

static PyGetSetDef pyCameraModifier_GetSet[] = {
    pyCameraModifier_from_getset,
    pyCameraModifier_at_getset,
    pyCameraModifier_brain_getset,
    pyCameraModifier_trans_getset,
    pyCameraModifier_fovW_getset,
    pyCameraModifier_fovH_getset,
    pyCameraModifier_messageQueue_getset,
    pyCameraModifier_fovInstructions_getset,
    pyCameraModifier_animated_getset,
    pyCameraModifier_startAnimOnPush_getset,
    pyCameraModifier_stopAnimOnPop_getset,
    pyCameraModifier_resetAnimOnPop_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(CameraModifier, plCameraModifier, "plCameraModifier wrapper")

PY_PLASMA_TYPE_INIT(CameraModifier)
{
    pyCameraModifier_Type.tp_new = pyCameraModifier_new;
    pyCameraModifier_Type.tp_methods = pyCameraModifier_Methods;
    pyCameraModifier_Type.tp_getset = pyCameraModifier_GetSet;
    pyCameraModifier_Type.tp_base = &pySingleModifier_Type;
    if (PyType_CheckAndReady(&pyCameraModifier_Type) < 0)
        return nullptr;

    /* CamTrans class */
    PyDict_SetItemString(pyCameraModifier_Type.tp_dict, "CamTrans",
                         Init_pyCamTrans_Type());

    Py_INCREF(&pyCameraModifier_Type);
    return (PyObject*)&pyCameraModifier_Type;
}

PY_PLASMA_IFC_METHODS(CameraModifier, plCameraModifier)
