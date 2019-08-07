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

#include "pyCameraBrain.h"

#include <PRP/Camera/plCameraBrain.h>
#include <Math/pyGeometry3.h>
#include <Util/pyBitVector.h>
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/KeyedObject/pyKeyedObject.h"
#include "PRP/pyCreatable.h"

/* pyCameraBrain */

PY_PLASMA_NEW(CameraBrain, plCameraBrain)

PY_PLASMA_TYPE(CameraBrain, plCameraBrain, "plCameraBrain wrapper")

PY_PLASMA_TYPE_INIT(CameraBrain)
{
    pyCameraBrain_Type.tp_new = pyCameraBrain_new;
    pyCameraBrain_Type.tp_base = &pyKeyedObject_Type;
    if (PyType_CheckAndReady(&pyCameraBrain_Type) < 0)
        return nullptr;

    Py_INCREF(&pyCameraBrain_Type);
    return (PyObject*)&pyCameraBrain_Type;
}

PY_PLASMA_IFC_METHODS(CameraBrain, plCameraBrain)


/* pyCameraBrain1 */

PY_PLASMA_NEW(CameraBrain1, plCameraBrain1)

PY_METHOD_VA(CameraBrain1, getFlags, "Params: flag")
{
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "getFlag expects an int");
        return nullptr;
    }
    return pyPlasma_convert(self->fThis->getFlags().get((size_t)idx));
}

PY_METHOD_VA(CameraBrain1, getEoAFlags, "Params: flag")
{
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "getEoAFlags expects an int");
        return nullptr;
    }
    return pyPlasma_convert(self->fThis->getEoAFlags().get((size_t)idx));
}

PY_METHOD_VA(CameraBrain1, setFlags, "Params: flag, value")
{
    Py_ssize_t idx, value;
    if (!PyArg_ParseTuple(args, "nn", &idx, &value)) {
        PyErr_SetString(PyExc_TypeError, "setFlags expects int, bool");
        return nullptr;
    }
    self->fThis->getFlags().set(idx, value != 0);
    Py_RETURN_NONE;
}

PY_METHOD_VA(CameraBrain1, setEoAFlags, "Params: flag, value")
{
    Py_ssize_t idx, value;
    if (!PyArg_ParseTuple(args, "nn", &idx, &value)) {
        PyErr_SetString(PyExc_TypeError, "setEoAFlags expects int, bool");
        return nullptr;
    }
    self->fThis->getEoAFlags().set(idx, value != 0);
    Py_RETURN_NONE;
}

static PyMethodDef pyCameraBrain1_Methods[] = {
    pyCameraBrain1_getFlags_method,
    pyCameraBrain1_getEoAFlags_method,
    pyCameraBrain1_setFlags_method,
    pyCameraBrain1_setEoAFlags_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY(plKey, CameraBrain1, subject, getSubject, setSubject)
PY_PROPERTY(plKey, CameraBrain1, rail, getRail, setRail)
PY_PROPERTY(float, CameraBrain1, velocity, getVelocity, setVelocity)
PY_PROPERTY(float, CameraBrain1, acceleration, getAcceleration, setAcceleration)
PY_PROPERTY(float, CameraBrain1, deceleration, getDeceleration, setDeceleration)
PY_PROPERTY(float, CameraBrain1, poaVelocity, getPOAVelocity, setPOAVelocity)
PY_PROPERTY(float, CameraBrain1, poaAcceleration, getPOAAcceleration, setPOAAcceleration)
PY_PROPERTY(float, CameraBrain1, poaDeceleration, getPOADeceleration, setPOADeceleration)
PY_PROPERTY(hsVector3, CameraBrain1, poaOffset, getPOAOffset, setPOAOffset)
PY_PROPERTY(float, CameraBrain1, xPanLimit, getXPanLimit, setXPanLimit)
PY_PROPERTY(float, CameraBrain1, zPanLimit, getZPanLimit, setZPanLimit)
PY_PROPERTY(float, CameraBrain1, panSpeed, getPanSpeed, setPanSpeed)
PY_PROPERTY(float, CameraBrain1, zoomRate, getZoomRate, setZoomRate)
PY_PROPERTY(float, CameraBrain1, zoomMax, getZoomMax, setZoomMax)
PY_PROPERTY(float, CameraBrain1, zoomMin, getZoomMin, setZoomMin)


static PyGetSetDef pyCameraBrain1_GetSet[] = {
    pyCameraBrain1_subject_getset,
    pyCameraBrain1_rail_getset,
    pyCameraBrain1_velocity_getset,
    pyCameraBrain1_acceleration_getset,
    pyCameraBrain1_deceleration_getset,
    pyCameraBrain1_poaVelocity_getset,
    pyCameraBrain1_poaAcceleration_getset,
    pyCameraBrain1_poaDeceleration_getset,
    pyCameraBrain1_poaOffset_getset,
    pyCameraBrain1_xPanLimit_getset,
    pyCameraBrain1_zPanLimit_getset,
    pyCameraBrain1_panSpeed_getset,
    pyCameraBrain1_zoomRate_getset,
    pyCameraBrain1_zoomMax_getset,
    pyCameraBrain1_zoomMin_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(CameraBrain1, plCameraBrain1, "plCameraBrain1 wrapper")

PY_PLASMA_TYPE_INIT(CameraBrain1)
{
    pyCameraBrain1_Type.tp_new = pyCameraBrain1_new;
    pyCameraBrain1_Type.tp_methods = pyCameraBrain1_Methods;
    pyCameraBrain1_Type.tp_getset = pyCameraBrain1_GetSet;
    pyCameraBrain1_Type.tp_base = &pyCameraBrain_Type;
    if (PyType_CheckAndReady(&pyCameraBrain1_Type) < 0)
        return nullptr;

    /* Konstants */
    PY_TYPE_ADD_CONST(CameraBrain1, "kCutPos", plCameraBrain1::kCutPos);
    PY_TYPE_ADD_CONST(CameraBrain1, "kCutPosOnce", plCameraBrain1::kCutPosOnce);
    PY_TYPE_ADD_CONST(CameraBrain1, "kCutPOA", plCameraBrain1::kCutPOA);
    PY_TYPE_ADD_CONST(CameraBrain1, "kCutPOAOnce", plCameraBrain1::kCutPOAOnce);
    PY_TYPE_ADD_CONST(CameraBrain1, "kAnimateFOV", plCameraBrain1::kAnimateFOV);
    PY_TYPE_ADD_CONST(CameraBrain1, "kFollowLocalAvatar", plCameraBrain1::kFollowLocalAvatar);
    PY_TYPE_ADD_CONST(CameraBrain1, "kPanicVelocity", plCameraBrain1::kPanicVelocity);
    PY_TYPE_ADD_CONST(CameraBrain1, "kRailComponent", plCameraBrain1::kRailComponent);
    PY_TYPE_ADD_CONST(CameraBrain1, "kSubject", plCameraBrain1::kSubject);
    PY_TYPE_ADD_CONST(CameraBrain1, "kCircleTarget", plCameraBrain1::kCircleTarget);
    PY_TYPE_ADD_CONST(CameraBrain1, "kMaintainLOS", plCameraBrain1::kMaintainLOS);
    PY_TYPE_ADD_CONST(CameraBrain1, "kZoomEnabled", plCameraBrain1::kZoomEnabled);
    PY_TYPE_ADD_CONST(CameraBrain1, "kIsTransitionCamera", plCameraBrain1::kIsTransitionCamera);
    PY_TYPE_ADD_CONST(CameraBrain1, "kWorldspacePOA", plCameraBrain1::kWorldspacePOA);
    PY_TYPE_ADD_CONST(CameraBrain1, "kWorldspacePos", plCameraBrain1::kWorldspacePos);
    PY_TYPE_ADD_CONST(CameraBrain1, "kCutPosWhilePan", plCameraBrain1::kCutPosWhilePan);
    PY_TYPE_ADD_CONST(CameraBrain1, "kCutPOAWhilePan", plCameraBrain1::kCutPOAWhilePan);
    PY_TYPE_ADD_CONST(CameraBrain1, "kNonPhys", plCameraBrain1::kNonPhys);
    PY_TYPE_ADD_CONST(CameraBrain1, "kNeverAnimateFOV", plCameraBrain1::kNeverAnimateFOV);
    PY_TYPE_ADD_CONST(CameraBrain1, "kIgnoreSubworldMovement", plCameraBrain1::kIgnoreSubworldMovement);
    PY_TYPE_ADD_CONST(CameraBrain1, "kFalling", plCameraBrain1::kFalling);
    PY_TYPE_ADD_CONST(CameraBrain1, "kRunning", plCameraBrain1::kRunning);
    PY_TYPE_ADD_CONST(CameraBrain1, "kVerticalWhenFalling", plCameraBrain1::kVerticalWhenFalling);
    PY_TYPE_ADD_CONST(CameraBrain1, "kSpeedUpWhenRunning", plCameraBrain1::kSpeedUpWhenRunning);
    PY_TYPE_ADD_CONST(CameraBrain1, "kFallingStopped", plCameraBrain1::kFallingStopped);
    PY_TYPE_ADD_CONST(CameraBrain1, "kBeginFalling", plCameraBrain1::kBeginFalling);

    Py_INCREF(&pyCameraBrain1_Type);
    return (PyObject*)&pyCameraBrain1_Type;
}

PY_PLASMA_IFC_METHODS(CameraBrain1, plCameraBrain1)

/* pyCameraBrain1_Avatar */

PY_PLASMA_NEW(CameraBrain1_Avatar, plCameraBrain1_Avatar)

PY_PROPERTY(hsVector3, CameraBrain1_Avatar, offset, getOffset, setOffset)

static PyGetSetDef pyCameraBrain1_Avatar_GetSet[] = {
    pyCameraBrain1_Avatar_offset_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(CameraBrain1_Avatar, plCameraBrain1_Avatar, "plCameraBrain1_Avatar wrapper")

PY_PLASMA_TYPE_INIT(CameraBrain1_Avatar)
{
    pyCameraBrain1_Avatar_Type.tp_new = pyCameraBrain1_Avatar_new;
    pyCameraBrain1_Avatar_Type.tp_getset = pyCameraBrain1_Avatar_GetSet;
    pyCameraBrain1_Avatar_Type.tp_base = &pyCameraBrain1_Type;
    if (PyType_CheckAndReady(&pyCameraBrain1_Avatar_Type) < 0)
        return nullptr;

    Py_INCREF(&pyCameraBrain1_Avatar_Type);
    return (PyObject*)&pyCameraBrain1_Avatar_Type;
}

PY_PLASMA_IFC_METHODS(CameraBrain1_Avatar, plCameraBrain1_Avatar)

/* pyCameraBrain1_FirstPerson */

PY_PLASMA_NEW(CameraBrain1_FirstPerson, plCameraBrain1_FirstPerson)

PY_PLASMA_TYPE(CameraBrain1_FirstPerson, plCameraBrain1_FirstPerson,
               "plCameraBrain1_FirstPerson wrapper")

PY_PLASMA_TYPE_INIT(CameraBrain1_FirstPerson)
{
    pyCameraBrain1_FirstPerson_Type.tp_new = pyCameraBrain1_FirstPerson_new;
    pyCameraBrain1_FirstPerson_Type.tp_base = &pyCameraBrain1_Avatar_Type;
    if (PyType_CheckAndReady(&pyCameraBrain1_FirstPerson_Type) < 0)
        return nullptr;

    Py_INCREF(&pyCameraBrain1_FirstPerson_Type);
    return (PyObject*)&pyCameraBrain1_FirstPerson_Type;
}

PY_PLASMA_IFC_METHODS(CameraBrain1_FirstPerson, plCameraBrain1_FirstPerson)

/* pyCameraBrain1_Fixed */

PY_PLASMA_NEW(CameraBrain1_Fixed, plCameraBrain1_Fixed)

PY_PROPERTY(plKey, CameraBrain1_Fixed, targetPoint, getTargetPoint, setTargetPoint)

static PyGetSetDef pyCameraBrain1_Fixed_GetSet[] = {
    pyCameraBrain1_Fixed_targetPoint_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(CameraBrain1_Fixed, plCameraBrain1_Fixed, "plCameraBrain1_Fixed wrapper")

PY_PLASMA_TYPE_INIT(CameraBrain1_Fixed)
{
    pyCameraBrain1_Fixed_Type.tp_new = pyCameraBrain1_Fixed_new;
    pyCameraBrain1_Fixed_Type.tp_getset = pyCameraBrain1_Fixed_GetSet;
    pyCameraBrain1_Fixed_Type.tp_base = &pyCameraBrain1_Type;
    if (PyType_CheckAndReady(&pyCameraBrain1_Fixed_Type) < 0)
        return nullptr;

    Py_INCREF(&pyCameraBrain1_Fixed_Type);
    return (PyObject*)&pyCameraBrain1_Fixed_Type;
}

PY_PLASMA_IFC_METHODS(CameraBrain1_Fixed, plCameraBrain1_Fixed)

/* pyCameraBrain1_Circle */

PY_PLASMA_NEW(CameraBrain1_Circle, plCameraBrain1_Circle)

PY_PROPERTY(unsigned int, CameraBrain1_Circle, circleFlags, getCircleFlags, setCircleFlags)
PY_PROPERTY(hsVector3, CameraBrain1_Circle, center, getCenter, setCenter)
PY_PROPERTY(float, CameraBrain1_Circle, radius, getRadius, setRadius)
PY_PROPERTY(plKey, CameraBrain1_Circle, centerObject, getCenterObject, setCenterObject)
PY_PROPERTY(plKey, CameraBrain1_Circle, poaObject, getPOAObject, setPOAObject)
PY_PROPERTY(float, CameraBrain1_Circle, cirPerSec, getCirPerSec, setCirPerSec)

static PyGetSetDef pyCameraBrain1_Circle_GetSet[] = {
    pyCameraBrain1_Circle_circleFlags_getset,
    pyCameraBrain1_Circle_center_getset,
    pyCameraBrain1_Circle_radius_getset,
    pyCameraBrain1_Circle_centerObject_getset,
    pyCameraBrain1_Circle_poaObject_getset,
    pyCameraBrain1_Circle_cirPerSec_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(CameraBrain1_Circle, plCameraBrain1_Circle, "plCameraBrain1_Circle wrapper")

PY_PLASMA_TYPE_INIT(CameraBrain1_Circle)
{
    pyCameraBrain1_Circle_Type.tp_new = pyCameraBrain1_Circle_new;
    pyCameraBrain1_Circle_Type.tp_getset = pyCameraBrain1_Circle_GetSet;
    pyCameraBrain1_Circle_Type.tp_base = &pyCameraBrain1_Fixed_Type;
    if (PyType_CheckAndReady(&pyCameraBrain1_Circle_Type) < 0)
        return nullptr;

    PY_TYPE_ADD_CONST(CameraBrain1_Circle, "kLagged", plCameraBrain1_Circle::kLagged);
    PY_TYPE_ADD_CONST(CameraBrain1_Circle, "kAbsoluteLag", plCameraBrain1_Circle::kAbsoluteLag);
    PY_TYPE_ADD_CONST(CameraBrain1_Circle, "kFarthest", plCameraBrain1_Circle::kFarthest);
    PY_TYPE_ADD_CONST(CameraBrain1_Circle, "kTargetted", plCameraBrain1_Circle::kTargetted);
    PY_TYPE_ADD_CONST(CameraBrain1_Circle, "kHasCenterObject", plCameraBrain1_Circle::kHasCenterObject);
    PY_TYPE_ADD_CONST(CameraBrain1_Circle, "kPOAObject", plCameraBrain1_Circle::kPOAObject);
    PY_TYPE_ADD_CONST(CameraBrain1_Circle, "kCircleLocalAvatar", plCameraBrain1_Circle::kCircleLocalAvatar);

    Py_INCREF(&pyCameraBrain1_Circle_Type);
    return (PyObject*)&pyCameraBrain1_Circle_Type;
}

PY_PLASMA_IFC_METHODS(CameraBrain1_Circle, plCameraBrain1_Circle)
