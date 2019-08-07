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

#include "pyCameraMsg.h"

#include <Math/pyGeometry3.h>
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/Message/pyMessage.h"

/* plCameraConfig */

PY_PLASMA_NEW(CameraConfig, plCameraConfig)

PY_PROPERTY(hsVector3, CameraConfig, offset, getOffset, setOffset)
PY_PROPERTY(float, CameraConfig, accel, getAccel, setAccel)
PY_PROPERTY(float, CameraConfig, decel, getDecel, setDecel)
PY_PROPERTY(float, CameraConfig, vel, getVel, setVel)
PY_PROPERTY(float, CameraConfig, fpAccel, getFPAccel, setFPAccel)
PY_PROPERTY(float, CameraConfig, fpDecel, getFPDecel, setFPDecel)
PY_PROPERTY(float, CameraConfig, fpVel, getFPVel, setFPVel)
PY_PROPERTY(float, CameraConfig, fovW, getFOVw, setFOVw)
PY_PROPERTY(float, CameraConfig, fovH, getFOVh, setFOVh)
PY_PROPERTY(bool, CameraConfig, worldspace, getWorldspace, setWorldspace)

static PyGetSetDef pyCameraConfig_GetSet[] = {
    pyCameraConfig_offset_getset,
    pyCameraConfig_accel_getset,
    pyCameraConfig_decel_getset,
    pyCameraConfig_vel_getset,
    pyCameraConfig_fpAccel_getset,
    pyCameraConfig_fpDecel_getset,
    pyCameraConfig_fpVel_getset,
    pyCameraConfig_fovW_getset,
    pyCameraConfig_fovH_getset,
    pyCameraConfig_worldspace_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(CameraConfig, plCameraConfig, "plCameraConfig wrapper")

PY_PLASMA_TYPE_INIT(CameraConfig)
{
    pyCameraConfig_Type.tp_new = pyCameraConfig_new;
    pyCameraConfig_Type.tp_getset = pyCameraConfig_GetSet;
    if (PyType_CheckAndReady(&pyCameraConfig_Type) < 0)
        return nullptr;

    Py_INCREF(&pyCameraConfig_Type);
    return (PyObject*)&pyCameraConfig_Type;
}

PY_PLASMA_IFC_METHODS(CameraConfig, plCameraConfig)

/* plCameraMsg */

PY_PLASMA_NEW(CameraMsg, plCameraMsg)

PY_METHOD_VA(CameraMsg, getCmd, "Params: idx")
{
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "getCmd expects an int");
        return nullptr;
    }
    return pyPlasma_convert(self->fThis->getCmd((size_t)idx));
}

PY_METHOD_VA(CameraMsg, setCmd, "Params: cmd, value")
{
    Py_ssize_t idx;
    Py_ssize_t value = 1;
    if (!PyArg_ParseTuple(args, "n|n", &idx, &value)) {
        PyErr_SetString(PyExc_TypeError, "setCmd expects int, bool");
        return nullptr;
    }
    self->fThis->setCmd(idx, value != 0);
    Py_RETURN_NONE;
}

static PyMethodDef pyCameraMsg_Methods[] = {
    pyCameraMsg_getCmd_method,
    pyCameraMsg_setCmd_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY(plKey, CameraMsg, newCam, getNewCam, setNewCam)
PY_PROPERTY(plKey, CameraMsg, triggerer, getTriggerer, setTriggerer)
PY_PROPERTY(double, CameraMsg, transTime, getTransTime, setTransTime)
PY_PROPERTY_PROXY(plCameraConfig, CameraMsg, config, getConfig)
PY_PROPERTY(bool, CameraMsg, activated, getActivated, setActivated)

static PyGetSetDef pyCameraMsg_GetSet[] = {
    pyCameraMsg_newCam_getset,
    pyCameraMsg_triggerer_getset,
    pyCameraMsg_transTime_getset,
    pyCameraMsg_config_getset,
    pyCameraMsg_activated_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(CameraMsg, plCameraMsg, "plCameraMsg wrapper")

PY_PLASMA_TYPE_INIT(CameraMsg)
{
    pyCameraMsg_Type.tp_new = pyCameraMsg_new;
    pyCameraMsg_Type.tp_methods = pyCameraMsg_Methods;
    pyCameraMsg_Type.tp_getset = pyCameraMsg_GetSet;
    pyCameraMsg_Type.tp_base = &pyMessage_Type;
    if (PyType_CheckAndReady(&pyCameraMsg_Type) < 0)
        return nullptr;

    /* Konstants */
    PY_TYPE_ADD_CONST(CameraMsg, "kSetSubject", plCameraMsg::kSetSubject);
    PY_TYPE_ADD_CONST(CameraMsg, "kCameraMod", plCameraMsg::kCameraMod);
    PY_TYPE_ADD_CONST(CameraMsg, "kSetAsPrimary", plCameraMsg::kSetAsPrimary);
    PY_TYPE_ADD_CONST(CameraMsg, "kTransitionTo", plCameraMsg::kTransitionTo);
    PY_TYPE_ADD_CONST(CameraMsg, "kPush", plCameraMsg::kPush);
    PY_TYPE_ADD_CONST(CameraMsg, "kPopt", plCameraMsg::kPop);
    PY_TYPE_ADD_CONST(CameraMsg, "kEntering", plCameraMsg::kEntering);
    PY_TYPE_ADD_CONST(CameraMsg, "kCut", plCameraMsg::kCut);
    PY_TYPE_ADD_CONST(CameraMsg, "kResetOnEnter", plCameraMsg::kResetOnEnter);
    PY_TYPE_ADD_CONST(CameraMsg, "kResetOnExit", plCameraMsg::kResetOnExit);
    PY_TYPE_ADD_CONST(CameraMsg, "kChangeParams", plCameraMsg::kChangeParams);
    PY_TYPE_ADD_CONST(CameraMsg, "kWorldspace", plCameraMsg::kWorldspace);
    PY_TYPE_ADD_CONST(CameraMsg, "kCreateNewDefaultCam", plCameraMsg::kCreateNewDefaultCam);
    PY_TYPE_ADD_CONST(CameraMsg, "kRegionPushCamera", plCameraMsg::kRegionPushCamera);
    PY_TYPE_ADD_CONST(CameraMsg, "kRegionPopCamera", plCameraMsg::kRegionPopCamera);
    PY_TYPE_ADD_CONST(CameraMsg, "kRegionPushPOA", plCameraMsg::kRegionPushPOA);
    PY_TYPE_ADD_CONST(CameraMsg, "kRegionPopPOA", plCameraMsg::kRegionPopPOA);
    PY_TYPE_ADD_CONST(CameraMsg, "kFollowLocalPlayer", plCameraMsg::kFollowLocalPlayer);
    PY_TYPE_ADD_CONST(CameraMsg, "kResponderTrigger", plCameraMsg::kResponderTrigger);
    PY_TYPE_ADD_CONST(CameraMsg, "kSetFOV", plCameraMsg::kSetFOV);
    PY_TYPE_ADD_CONST(CameraMsg, "kAddFOVKeyFrame", plCameraMsg::kAddFOVKeyFrame);
    PY_TYPE_ADD_CONST(CameraMsg, "kStartZoomIn", plCameraMsg::kStartZoomIn);
    PY_TYPE_ADD_CONST(CameraMsg, "kStartZoomOut", plCameraMsg::kStartZoomOut);
    PY_TYPE_ADD_CONST(CameraMsg, "kStopZoom", plCameraMsg::kStopZoom);
    PY_TYPE_ADD_CONST(CameraMsg, "kSetAnimated", plCameraMsg::kSetAnimated);
    PY_TYPE_ADD_CONST(CameraMsg, "kPythonOverridePush", plCameraMsg::kPythonOverridePush);
    PY_TYPE_ADD_CONST(CameraMsg, "kPythonOverridePop", plCameraMsg::kPythonOverridePop);
    PY_TYPE_ADD_CONST(CameraMsg, "kPythonOverridePushCut",
                      plCameraMsg::kPythonOverridePushCut);
    PY_TYPE_ADD_CONST(CameraMsg, "kPythonSetFirstPersonOverrideEnable",
                      plCameraMsg::kPythonSetFirstPersonOverrideEnable);
    PY_TYPE_ADD_CONST(CameraMsg, "kPythonUndoFirstPerson",
                      plCameraMsg::kPythonUndoFirstPerson);
    PY_TYPE_ADD_CONST(CameraMsg, "kUpdateCameras", plCameraMsg::kUpdateCameras);
    PY_TYPE_ADD_CONST(CameraMsg, "kResponderSetThirdPerson",
                     plCameraMsg::kResponderSetThirdPerson);
    PY_TYPE_ADD_CONST(CameraMsg, "kResponderUndoThirdPerson",
                     plCameraMsg::kResponderUndoThirdPerson);
    PY_TYPE_ADD_CONST(CameraMsg, "kNonPhysOn", plCameraMsg::kNonPhysOn);
    PY_TYPE_ADD_CONST(CameraMsg, "kNonPhysOff", plCameraMsg::kNonPhysOff);
    PY_TYPE_ADD_CONST(CameraMsg, "kResetPanning", plCameraMsg::kResetPanning);
    PY_TYPE_ADD_CONST(CameraMsg, "kNumCmds", plCameraMsg::kNumCmds);

    Py_INCREF(&pyCameraMsg_Type);
    return (PyObject*)&pyCameraMsg_Type;
}

PY_PLASMA_IFC_METHODS(CameraMsg, plCameraMsg)
