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

#include "pyObjectInVolumeDetector.h"

#include "PRP/pyCreatable.h"
#include "PRP/Message/pyCameraMsg.h"
#include <PRP/Physics/plObjectInVolumeDetector.h>

PY_PLASMA_NEW(CameraRegionDetector, plCameraRegionDetector)

PY_METHOD_VA(CameraRegionDetector, addMessage, "Params: msg")
{
    pyCameraMsg* msg;
    if (!PyArg_ParseTuple(args, "O", &msg) || !pyCameraMsg_Check((PyObject*)msg)) {
        PyErr_SetString(PyExc_TypeError, "addMessage expects a plCameraMsg");
        return nullptr;
    }
    msg->fPyOwned = false;
    self->fThis->addMessage(msg->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(CameraRegionDetector, delMessage, "Params: idx")
{
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delMessage expects an int");
        return nullptr;
    }
    if ((size_t)idx < self->fThis->getMessages().size()) {
        self->fThis->delMessage(idx);
        Py_RETURN_NONE;
    } else {
        PyErr_SetNone(PyExc_IndexError);
        return nullptr;
    }
}

PY_METHOD_NOARGS(CameraRegionDetector, clearMessages, "Clears the camera message vector")
{
    self->fThis->clearMessages();
    Py_RETURN_NONE;
}

static PyMethodDef pyCameraRegionDetector_Methods[] = {
    pyCameraRegionDetector_addMessage_method,
    pyCameraRegionDetector_delMessage_method,
    pyCameraRegionDetector_clearMessages_method,
    PY_METHOD_TERMINATOR
};

PY_GETSET_GETTER_DECL(CameraRegionDetector, messages)
{
    const std::vector<plCameraMsg*>& msgs = self->fThis->getMessages();
    PyObject* tup = PyTuple_New(msgs.size());
    for (size_t i = 0; i < msgs.size(); ++i)
        PyTuple_SET_ITEM(tup, i, ICreate(msgs[i]));
    return tup;
}
PY_PROPERTY_SETTER_MSG(CameraRegionDetector, messages, "To add messages, use addMessage()")
PY_PROPERTY_GETSET_DECL(CameraRegionDetector, messages)

static PyGetSetDef pyCameraRegionDetector_GetSet[] = {
    pyCameraRegionDetector_messages_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(CameraRegionDetector, plCameraRegionDetector, "plCameraRegionDetector wrapper")

PY_PLASMA_TYPE_INIT(CameraRegionDetector)
{
    pyCameraRegionDetector_Type.tp_new = pyCameraRegionDetector_new;
    pyCameraRegionDetector_Type.tp_methods = pyCameraRegionDetector_Methods;
    pyCameraRegionDetector_Type.tp_getset = pyCameraRegionDetector_GetSet;
    pyCameraRegionDetector_Type.tp_base = &pyObjectInVolumeDetector_Type;
    if (PyType_CheckAndReady(&pyCameraRegionDetector_Type) < 0)
        return nullptr;

    Py_INCREF(&pyCameraRegionDetector_Type);
    return (PyObject*)&pyCameraRegionDetector_Type;
}

PY_PLASMA_IFC_METHODS(CameraRegionDetector, plCameraRegionDetector)
