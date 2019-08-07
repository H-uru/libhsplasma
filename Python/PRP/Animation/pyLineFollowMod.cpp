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

#include "pyLineFollowMod.h"

#include "pyAnimPath.h"
#include "PRP/pyCreatable.h"
#include "PRP/KeyedObject/pyKey.h"
#include "PRP/Modifier/pyModifier.h"

/* pyLineFollowMod */

PY_PLASMA_NEW(LineFollowMod, plLineFollowMod)

PY_METHOD_VA(LineFollowMod, addStereizer, "Params: stereizer")
{
    pyKey* stereizer;
    if (!PyArg_ParseTuple(args, "O", &stereizer) || !pyKey_Check((PyObject*)stereizer)) {
        PyErr_SetString(PyExc_TypeError, "addStereizer expects a plKey");
        return nullptr;
    }
    self->fThis->addStereizer(*stereizer->fThis);
    Py_RETURN_NONE;
}

PY_METHOD_VA(LineFollowMod, delStereizer, "Params: idx")
{
    Py_ssize_t idx;
    if (!PyArg_ParseTuple(args, "n", &idx)) {
        PyErr_SetString(PyExc_TypeError, "delStereizer expects an int");
        return nullptr;
    }
    if ((size_t)idx < self->fThis->getStereizers().size()) {
        self->fThis->delStereizer(idx);
        Py_RETURN_NONE;
    } else {
        PyErr_SetNone(PyExc_IndexError);
        return nullptr;
    }
}

PY_METHOD_NOARGS(LineFollowMod, clearStereizers, "Removes all stereizers")
{
    self->fThis->clearStereizers();
    Py_RETURN_NONE;
}

static PyMethodDef pyLineFollowMod_Methods[] = {
    pyLineFollowMod_addStereizer_method,
    pyLineFollowMod_delStereizer_method,
    pyLineFollowMod_clearStereizers_method,
    PY_METHOD_TERMINATOR
};

PY_PROPERTY(plLineFollowMod::FollowMode, LineFollowMod, followMode, getFollowMode, setFollowMode)
PY_PROPERTY(unsigned short, LineFollowMod, followFlags, getFollowFlags, setFollowFlags)
PY_PROPERTY_CREATABLE(plAnimPath, AnimPath, LineFollowMod, path, getPath, setPath)
PY_PROPERTY(plKey, LineFollowMod, pathParent, getPathParent, setPathParent)
PY_PROPERTY(plKey, LineFollowMod, refObj, getRefObj, setRefObj)
PY_PROPERTY(float, LineFollowMod, offset, getOffset, setOffset)
PY_PROPERTY(float, LineFollowMod, offsetClamp, getOffsetClamp, setOffsetClamp)
PY_PROPERTY(float, LineFollowMod, speedClamp, getSpeedClamp, setOffsetClamp)

PY_GETSET_GETTER_DECL(LineFollowMod, stereizers)
{
    const std::vector<plKey>& stereizers = self->fThis->getStereizers();
    PyObject* tup = PyTuple_New(stereizers.size());
    for (size_t i = 0; i < stereizers.size(); ++i)
        PyTuple_SET_ITEM(tup, i, pyKey_FromKey(stereizers[i]));
    return tup;
}
PY_PROPERTY_SETTER_MSG(LineFollowMod, stereizers, "To add stereizers, use addStereizer()")
PY_PROPERTY_GETSET_DECL(LineFollowMod, stereizers)

static PyGetSetDef pyLineFollowMod_GetSet[] = {
    pyLineFollowMod_followMode_getset,
    pyLineFollowMod_followFlags_getset,
    pyLineFollowMod_path_getset,
    pyLineFollowMod_pathParent_getset,
    pyLineFollowMod_refObj_getset,
    pyLineFollowMod_stereizers_getset,
    pyLineFollowMod_offset_getset,
    pyLineFollowMod_offsetClamp_getset,
    pyLineFollowMod_speedClamp_getset,
    PY_GETSET_TERMINATOR
};

PY_PLASMA_TYPE(LineFollowMod, plLineFollowMod, "plLineFollowMod wrapper")

PY_PLASMA_TYPE_INIT(LineFollowMod)
{
    pyLineFollowMod_Type.tp_new = pyLineFollowMod_new;
    pyLineFollowMod_Type.tp_methods = pyLineFollowMod_Methods;
    pyLineFollowMod_Type.tp_getset = pyLineFollowMod_GetSet;
    pyLineFollowMod_Type.tp_base = &pyMultiModifier_Type;
    if (PyType_CheckAndReady(&pyLineFollowMod_Type) < 0)
        return nullptr;

    /* Konstants */
    PY_TYPE_ADD_CONST(LineFollowMod, "kFollowObject", plLineFollowMod::kFollowObject);
    PY_TYPE_ADD_CONST(LineFollowMod, "kFollowListener", plLineFollowMod::kFollowListener);
    PY_TYPE_ADD_CONST(LineFollowMod, "kFollowCamera", plLineFollowMod::kFollowCamera);
    PY_TYPE_ADD_CONST(LineFollowMod, "kFollowLocalAvatar", plLineFollowMod::kFollowLocalAvatar);

    PY_TYPE_ADD_CONST(LineFollowMod, "kNone", plLineFollowMod::kNone);
    PY_TYPE_ADD_CONST(LineFollowMod, "kFullMatrix", plLineFollowMod::kFullMatrix);
    PY_TYPE_ADD_CONST(LineFollowMod, "kOffsetFeet", plLineFollowMod::kOffsetFeet);
    PY_TYPE_ADD_CONST(LineFollowMod, "kOffsetAng", plLineFollowMod::kOffsetAng);
    PY_TYPE_ADD_CONST(LineFollowMod, "kOffset", plLineFollowMod::kOffset);
    PY_TYPE_ADD_CONST(LineFollowMod, "kOffsetClamp", plLineFollowMod::kOffsetClamp);
    PY_TYPE_ADD_CONST(LineFollowMod, "kForceToLine", plLineFollowMod::kForceToLine);
    PY_TYPE_ADD_CONST(LineFollowMod, "kSpeedClamp", plLineFollowMod::kSpeedClamp);
    PY_TYPE_ADD_CONST(LineFollowMod, "kSearchPopPos", plLineFollowMod::kSearchPopPos);

    Py_INCREF(&pyLineFollowMod_Type);
    return (PyObject*)&pyLineFollowMod_Type;
}

PY_PLASMA_IFC_METHODS(LineFollowMod, plLineFollowMod)

/* pyRailCameraMod */

PY_PLASMA_NEW(RailCameraMod, plRailCameraMod)

PY_PLASMA_TYPE(RailCameraMod, plRailCameraMod, "plRailCameraMod wrapper")

PY_PLASMA_TYPE_INIT(RailCameraMod)
{
    pyRailCameraMod_Type.tp_new = pyRailCameraMod_new;
    pyRailCameraMod_Type.tp_base = &pyLineFollowMod_Type;
    if (PyType_CheckAndReady(&pyRailCameraMod_Type) < 0)
        return nullptr;

    Py_INCREF(&pyRailCameraMod_Type);
    return (PyObject*)&pyRailCameraMod_Type;
}

PY_PLASMA_IFC_METHODS(RailCameraMod, plRailCameraMod)
