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

#include "pyDynaDecalMgr.h"

#include <PRP/Surface/plDynaDecalMgr.h>
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/Object/pySynchedObject.h"
#include "Math/pyGeometry3.h"

PY_PLASMA_NEW(DynaDecalMgr, plDynaDecalMgr)

PY_METHOD_VA(DynaDecalMgr, addTarget,
    "Params: key\n"
    "Adds the specified target key")
{
    PyObject* key;
    if (!PyArg_ParseTuple(args, "O", &key) || !pyPlasma_check<plKey>(key)) {
        PyErr_SetString(PyExc_TypeError, "addTarget expects a plKey");
        return nullptr;
    }

    self->fThis->addTarget(pyPlasma_get<plKey>(key));
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(DynaDecalMgr, clearTargets,
    "Clears the target keys")
{
    self->fThis->clearTargets();
    Py_RETURN_NONE;
}

PY_METHOD_VA(DynaDecalMgr, delTarget,
    "Params: idx\n"
    "Removes the specified target key by index")
{
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delTarget expects an int");
        return nullptr;
    }

    if (idx < 0 || size_t(idx) >= self->fThis->getNumTargets()) {
        PyErr_SetNone(PyExc_IndexError);
        return nullptr;
    }

    self->fThis->delTarget(idx);
    Py_RETURN_NONE;
}

PY_METHOD_VA(DynaDecalMgr, addPartyObject,
    "Params: key\n"
    "Adds the specified partyObject key")
{
    PyObject* key;
    if (!PyArg_ParseTuple(args, "O", &key) || !pyPlasma_check<plKey>(key)) {
        PyErr_SetString(PyExc_TypeError, "addPartyObject expects a plKey");
        return nullptr;
    }

    self->fThis->addPartyObject(pyPlasma_get<plKey>(key));
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(DynaDecalMgr, clearPartyObjects,
    "Clears the partyObject keys")
{
    self->fThis->clearPartyObjects();
    Py_RETURN_NONE;
}

PY_METHOD_VA(DynaDecalMgr, delPartyObject,
    "Params: idx\n"
    "Removes the specified partyObject key by index")
{
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delPartyObject expects an int");
        return nullptr;
    }

    if (idx < 0 || size_t(idx) >= self->fThis->getNumPartyObjects()) {
        PyErr_SetNone(PyExc_IndexError);
        return nullptr;
    }

    self->fThis->delPartyObject(idx);
    Py_RETURN_NONE;
}

PY_METHOD_VA(DynaDecalMgr, addNotify,
    "Params: key\n"
    "Adds the specified notify key")
{
    PyObject* key;
    if (!PyArg_ParseTuple(args, "O", &key) || !pyPlasma_check<plKey>(key)) {
        PyErr_SetString(PyExc_TypeError, "addNotify expects a plKey");
        return nullptr;
    }

    self->fThis->addNotify(pyPlasma_get<plKey>(key));
    Py_RETURN_NONE;
}

PY_METHOD_NOARGS(DynaDecalMgr, clearNotifies,
    "Clears the notify keys")
{
    self->fThis->clearNotifies();
    Py_RETURN_NONE;
}

PY_METHOD_VA(DynaDecalMgr, delNotify,
    "Params: idx\n"
    "Removes the specified notify key by index")
{
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delNotify expects an int");
        return nullptr;
    }

    if (idx < 0 || size_t(idx) >= self->fThis->getNumNotifies()) {
        PyErr_SetNone(PyExc_IndexError);
        return nullptr;
    }

    self->fThis->delNotify(idx);
    Py_RETURN_NONE;
}

static PyMethodDef pyDynaDecalMgr_Methods[] = {
    pyDynaDecalMgr_addTarget_method,
    pyDynaDecalMgr_clearTargets_method,
    pyDynaDecalMgr_delTarget_method,
    pyDynaDecalMgr_addPartyObject_method,
    pyDynaDecalMgr_clearPartyObjects_method,
    pyDynaDecalMgr_delPartyObject_method,
    pyDynaDecalMgr_addNotify_method,
    pyDynaDecalMgr_clearNotifies_method,
    pyDynaDecalMgr_delNotify_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY(plKey, DynaDecalMgr, matPreShade, getMatPreShade, setMatPreShade)
PY_PROPERTY(plKey, DynaDecalMgr, matRTShade, getMatRTShade, setMatRTShade)

PY_GETSET_GETTER_DECL(DynaDecalMgr, targets)
{
    PyObject* tup = PyTuple_New(self->fThis->getNumTargets());
    for (size_t i = 0; i < self->fThis->getNumTargets(); ++i)
        PyTuple_SET_ITEM(tup, i, pyPlasma_convert(self->fThis->getTarget(i)));
    return tup;
}
PY_PROPERTY_SETTER_MSG(DynaDecalMgr, targets, "To add a target, use addTarget()")
PY_PROPERTY_GETSET_DECL(DynaDecalMgr, targets)

PY_GETSET_GETTER_DECL(DynaDecalMgr, partyObjects)
{
    PyObject* tup = PyTuple_New(self->fThis->getNumPartyObjects());
    for (size_t i = 0; i < self->fThis->getNumPartyObjects(); ++i)
        PyTuple_SET_ITEM(tup, i, pyPlasma_convert(self->fThis->getPartyObject(i)));
    return tup;
}
PY_PROPERTY_SETTER_MSG(DynaDecalMgr, partyObjects, "To add a partyObject, use addPartyObject()")
PY_PROPERTY_GETSET_DECL(DynaDecalMgr, partyObjects)

PY_PROPERTY(float, DynaDecalMgr, partyTime, getPartyTime, setPartyTime)
PY_PROPERTY(unsigned short, DynaDecalMgr, maxNumVerts, getMaxNumVerts, setMaxNumVerts)
PY_PROPERTY(unsigned short, DynaDecalMgr, maxNumIdx, getMaxNumIdx, setMaxNumIdx)
PY_PROPERTY(unsigned int, DynaDecalMgr, waitOnEnable, getWaitOnEnable, setWaitOnEnable)
PY_PROPERTY(float, DynaDecalMgr, wetLength, getWetLength, setWetLength)
PY_PROPERTY(float, DynaDecalMgr, rampEnd, getRampEnd, setRampEnd)
PY_PROPERTY(float, DynaDecalMgr, decayStart, getDecayStart, setDecayStart)
PY_PROPERTY(float, DynaDecalMgr, lifeSpan, getLifeSpan, setLifeSpan)
PY_PROPERTY(float, DynaDecalMgr, intensity, getIntensity, setIntensity)
PY_PROPERTY(float, DynaDecalMgr, gridSizeU, getGridSizeU, setGridSizeU)
PY_PROPERTY(float, DynaDecalMgr, gridSizeV, getGridSizeV, setGridSizeV)
PY_PROPERTY(hsVector3, DynaDecalMgr, scale, getScale, setScale)

PY_GETSET_GETTER_DECL(DynaDecalMgr, notifies)
{
    PyObject* tup = PyTuple_New(self->fThis->getNumNotifies());
    for (size_t i = 0; i < self->fThis->getNumNotifies(); ++i)
        PyTuple_SET_ITEM(tup, i, pyPlasma_convert(self->fThis->getNotify(i)));
    return tup;
}
PY_PROPERTY_SETTER_MSG(DynaDecalMgr, notifies, "To add a notify, use addNotify()")
PY_PROPERTY_GETSET_DECL(DynaDecalMgr, notifies)

static PyGetSetDef pyDynaDecalMgr_GetSet[] = {
    pyDynaDecalMgr_matPreShade_getset,
    pyDynaDecalMgr_matRTShade_getset,
    pyDynaDecalMgr_targets_getset,
    pyDynaDecalMgr_partyObjects_getset,
    pyDynaDecalMgr_partyTime_getset,
    pyDynaDecalMgr_maxNumVerts_getset,
    pyDynaDecalMgr_maxNumIdx_getset,
    pyDynaDecalMgr_waitOnEnable_getset,
    pyDynaDecalMgr_wetLength_getset,
    pyDynaDecalMgr_rampEnd_getset,
    pyDynaDecalMgr_decayStart_getset,
    pyDynaDecalMgr_lifeSpan_getset,
    pyDynaDecalMgr_intensity_getset,
    pyDynaDecalMgr_gridSizeU_getset,
    pyDynaDecalMgr_gridSizeV_getset,
    pyDynaDecalMgr_scale_getset,
    pyDynaDecalMgr_notifies_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(DynaDecalMgr, plDynaDecalMgr, "plDynaDecalMgr wrapper")

PY_PLASMA_TYPE_INIT(DynaDecalMgr)
{
    pyDynaDecalMgr_Type.tp_new = pyDynaDecalMgr_new;
    pyDynaDecalMgr_Type.tp_methods = pyDynaDecalMgr_Methods;
    pyDynaDecalMgr_Type.tp_getset = pyDynaDecalMgr_GetSet;
    pyDynaDecalMgr_Type.tp_base = &pySynchedObject_Type;
    if (PyType_CheckAndReady(&pyDynaDecalMgr_Type) < 0)
        return nullptr;

    Py_INCREF(&pyDynaDecalMgr_Type);
    return (PyObject*)&pyDynaDecalMgr_Type;
}

PY_PLASMA_IFC_METHODS(DynaDecalMgr, plDynaDecalMgr)
